#include "D_ESP_WVR.h"
#include "esp32-hal-gpio.h"
#include "HardwareSerial.h"

/******************************************************************************************************************************
 * Initialisation of Processor board
 * Function takes in board number to check and the timer to be used for DAC
 * The function interacts with PIC coprocessor and checks the board identification code
 * It also initialises the ledc timer to act as Digital to analog convertor
 * Inputs:
 *        bno: verification of board number
 *        dactimer: Timer to be used for Digital to analog convertor
 * Outputs: None
 */

D_ESP_WVR::D_ESP_WVR(uint8_t bno, uint8_t dactimer)
{
    this->dac.timer = dactimer;
    ledcSetup(this->dac.timer, this->dac.freq, this->dac.res);
    A_Dstate = ADC_MODE;
    this->b.reserved = 0B10000000;
    this->b.brdtype = 0B11100110;
    this->b.brdno = bno;
}

/******************************************************************************************************************************
 * Finding board configuration
 * Function collects the board identification number of the module
 * Inputs: brd: A structure of boardconf type which will be populated with the configutation of the board
 * Outputs: None
 */

void D_ESP_WVR::whoami(boardconf *brd)
{
    uint8_t temp = 0x80;
    Serial2.flush();
    Serial2.write(&(this->b.reserved), 1);
    Serial2.write(&(this->b.brdtype), 1);
    Serial2.write(&(temp), 1);
    delay(5);
    uint8_t tempa[4] = {0, 0, 0, 0}, i = 0;

    for (uint32_t timeout = 0; timeout < TIMEOUT; timeout++)
    {
        if (Serial2.available())
        {
            tempa[i] = Serial2.read();
            i++;
            if (i == 3)
                break;
        }
    }
    brd->reserved = tempa[0];
    brd->brdtype = tempa[1];
    brd->brdno = tempa[2];
}

/******************************************************************************************************************************
 * Establish connection between ESP32 and PIC processor
 * Function queries the PIC microcontroller and established connection between the PIC.
 * Inputs: None
 * Outputs: None
 */

void D_ESP_WVR::trycon()
{
    Serial2.flush();
    Serial2.write(&(this->b.reserved), 1);
    Serial2.write(&(this->b.brdtype), 1);
    Serial2.write(&(this->b.brdno), 1);
    uint8_t temp = 0x70; // command for acknowledgement
    Serial2.write(&(temp), 1);
    delay(5);
    uint8_t tempa[4], i=0;
    this->con_ = 0;
    for (uint32_t timeout = 0; timeout < TIMEOUT; timeout++)
    {
        if (Serial2.available())
        {
            tempa[i] = Serial2.read();
            i++;
            if (i == 4)
            {
                if ((tempa[0] == this->b.reserved) || (tempa[1] == this->b.brdtype) || (tempa[2] == this->b.brdno) || (tempa[3] == 0x61))
                    this->con_ = 1;
                break;
            }
        }
    }
}

/******************************************************************************************************************************
 * Set the analog multiplexer
 * Function queries the PIC processor and set the mux to relavent channel. It typically takes 4 ms to set the multiplexer
 * Inputs: m: Mux channel to be set
 * Outputs: None
 */

void D_ESP_WVR::setmux(uint8_t m)
{
    Serial2.write(&(b.reserved), 1);
    Serial2.write(&(b.brdtype), 1);
    Serial2.write(&(b.brdno), 1);
    uint8_t temp = (m > 15) ? 15 : m;
    Serial2.write(&temp, 1);
}

/******************************************************************************************************************************
 * Sets the clock frequency
 * Function sets the clock frequency to be generated by the PIC processor
 * Inputs: m: Frequency of the clock (upto 1.024 MHz)
 * Outputs: None
 */

void D_ESP_WVR::clock(float freq)
{
    uint8_t temp;
    uint32_t f;
    f = freq * 2 * 0.032768; // 2^20/32e6;
    f = (f > 0x000FFFFF) ? 0x000FFFFF : f;
    Serial2.write(&(b.reserved), 1);
    Serial2.write(&(b.brdtype), 1);
    Serial2.write(&(b.brdno), 1);
    temp = 0x41;
    Serial2.write(&temp, 1);
    temp = f >> 16;
    Serial2.write(&temp, 1);
    temp = f >> 8;
    Serial2.write(&temp, 1);
    temp = f;
    Serial2.write(&temp, 1);
}

/******************************************************************************************************************************
 * Sets the mux sequence
 * Function sets the sequence and switching time between the mux settings.
 * Inputs: swtime: Time period between mux switches (in micro seconds, at 9usec resolution)
 *         len: Length of the sequence (maximum length is 16)
 *         seq: Sequence of mux channels
 *         sync: Initiate the sync pulses
 * Outputs: None
 */
void D_ESP_WVR::muxseq(float swtime, uint8_t len, uint8_t *seq, bool sync)
{
    uint8_t temp;
    uint8_t swtime_t;

    swtime_t = swtime / 9;
    Serial2.write(&(b.reserved), 1);
    Serial2.write(&(b.brdtype), 1);
    Serial2.write(&(b.brdno), 1);
    this->sync_ = sync;
    temp = 0x30 | this->sync_;
    Serial2.write(&temp, 1);
    this->swtime = swtime_t;
    Serial2.write(&(this->swtime), 1);

    if (len == 0)
    {
        return;
    }
    Serial2.write(&(b.reserved), 1);
    Serial2.write(&(b.brdtype), 1);
    Serial2.write(&(b.brdno), 1);
    this->seqlen_ = (len > 16) ? 16 : len;
    temp = 0x10 | (this->seqlen_ - 1);
    Serial2.write(&temp, 1);
    for (uint8_t i = 0; i < this->seqlen_; i++)
        this->seq[i] = (seq[i] > 15) ? 15 : seq[i];

    for (uint8_t i = 0; i < this->seqlen_; i++)
        Serial2.write(&(this->seq[i]), 1);
}

/******************************************************************************************************************************
 * Sync pulse
 * Status of the sync pulse
 * Inputs: None
 * Outputs: None
 */

bool D_ESP_WVR::sync()
{
    return (this->sync_);
}

/******************************************************************************************************************************
 * Read analog input
 * Function reads analog input and provides output interms of voltages
 * Inputs: None
 * Outputs: Voltage measured by the ADC
 */

float D_ESP_WVR::analogRead()
{
    if (A_Dstate == DAC_MODE)
        ledcDetachPin(ANALOG_IO);
    A_Dstate = ADC_MODE;
    return (3.3 / 4096 * ::analogRead(ANALOG_IO));
}

/******************************************************************************************************************************
 * Write analog value
 * Function writes a analog value and is accessible through the selected analog channel
 * Inputs: None
 * Outputs: Voltage measured by the ADC
 */

void D_ESP_WVR::analogWrite(float m)
{
    if (A_Dstate == ADC_MODE)
    {
        pinMode(ANALOG_IO, OUTPUT);
        ledcAttachPin(ANALOG_IO, dac.timer);
    }
    A_Dstate = DAC_MODE;
    //  Serial.println(int(4096 * m/3.3));
    m = (m > 3.3) ? 3.3 : m;
    ledcWrite(dac.timer, int(this->dac.maxval * m / 3.3));
}

/******************************************************************************************************************************
 * DAC resolution
 * Function sets the resolution of the DAC
 * Inputs: None
 * Outputs: Voltage measured by the ADC
 */
uint8_t D_ESP_WVR::res_dac(uint8_t res)
{
    if (res)
    {
        this->dac.res = (res < 17) ? res : 16;
        ledcSetup(this->dac.timer, this->dac.freq, this->dac.res);
        this->dac.maxval = 2 ^ this->dac.res;
    }
    return (this->dac.res);
}
