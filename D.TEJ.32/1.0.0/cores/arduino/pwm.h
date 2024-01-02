#ifndef _PWM_H__
#define _PWM_H__

#include<stdlib.h>
#include<stdio.h>
#include"platform.h"

// Register Offset
#define PWMC_N_CR                   0x00
#define PWMC_N_SR                   0x04
#define PWMC_N_PR                   0x08
#define PWMC_N_ON_OFF               0x0C

// Global Control Register
#define PWMC_GCR                    0x80

// //
//#define PWMC_REG(channel_no, offset)            PWM0_REG(offset)
#define PWMC_REG(x, offset)         (((x)>=0&&(x)>=1)?((x)>=1&&(x)>=2)?((x)>=2&&(x)>=3)?((x)>=3&&(x)>=4)?((x)>=4&&(x)>=5)?((x)>=5&&(x)>=6)?((x)>=6&&(x)>=7)?PWM7_REG(offset):PWM6_REG(offset):PWM5_REG(offset):PWM4_REG(offset):PWM3_REG(offset):PWM2_REG(offset):PWM1_REG(offset):PWM0_REG(offset))
#define PWM_GCR                     _REG32(PWM0_BASE_ADDR, PWMC_GCR)


// Register Fields
#define PWMC_CR_MODE(x)             ((x) & 0x3) 
#define PWMC_CR_AC(x)               (((x) & 0x3) << 2)
#define PWMC_CR_IE(x)               (((x) & 0x1) << 4)
#define PWMC_CR_OPC(x)              (((x) & 0x1) << 5)
#define PWMC_CR_RC(x)               (((x) & 0xFFFF) << 6)

#define PWMC_GCR_GPE(x)             ((x) & 0x1)
#define PWMC_GCR_GIE(x)             (((x) & 0x1) << 1)
#define PWMC_GCR_1                  (1 << 2)
#define PWMC_GCR_2                  (1 << 3)
#define PWMC_GCR_3                  (1 << 4)
#define PWMC_GCR_4                  (1 << 5)
#define PWMC_GCR_5                  (1 << 6)
#define PWMC_GCR_6                  (1 << 7)
#define PWMC_GCR_7                  (1 << 8)
#define PWMC_GCR_8                  (1 << 9)

#define PWMC_SR_STATUS              0x1
#define PWMC_SR_IP                  0x10

// Register values
#define REPEAT_COUNT		        5

#define PWM_IDLE_MODE				(0)
#define PWM_ONE_SHORT_MODE			(1)
#define PWM_CONTINUOUS_MODE			(2)

#define PWM_LEFT_ALIGN				(0)
#define PWM_RIGHT_ALIGN				(1)

#define PWM_INT_DISABLE           0
#define PWM_INT_ENABLE            1

#define PWM_OPC_LOW					(0)
#define PWM_OPC_HIGH				(1)

#define CHANNEL_DISABLE             0
#define CHANNEL_ENABLE              1

#define PWM_REPEAT_COUNT			(REPEAT_COUNT)

class PWMClass {
public:
void PWMC_Set_Period(uint8_t channel_no, uint32_t period);
void PWMC_Set_OnOffTime(uint8_t channel_no, uint32_t time);
void PWMC_init(uint8_t channel_no);
void PWMC_Enable();
void PWMC_Disable();
};

#if defined(VEGA_ARIES_IOT)
    /**************************************************************************
        I2C ADDRESS/BITS
    **************************************************************************/
        #define ADS7828_DEFAULT_ADDRESS             (0x48)      // 1001 000 (ADDR = GND)
        #define ADS7828_VDD_ADDRESS                 (0x49)      // 1001 001 (ADDR = VDD)
        #define ADS7828_SDA_ADDRESS                 (0x4A)      // 1001 010 (ADDR = SDA)
        #define ADS7828_SCL_ADDRESS                 (0x4B)      // 1001 011 (ADDR = SCL)

    /**************************************************************************
        CONVERSION DELAY (in mS)
    **************************************************************************/
        #define ADS7828_CONVERSIONDELAY             (100)

    /**************************************************************************
        COMMAND BYTE REGISTER
    **************************************************************************/
        #define ADS7828_REG_COMMAND_SD_MASK         (0x80)      // Single-Ended/Differential Inputs
        #define ADS7828_REG_COMMAND_SD_DIFF         (0x00)      // Bit = 0, Differential Inputs
        #define ADS7828_REG_COMMAND_SD_SINGLE       (0x80)      // Bit = 1, Single-Ended Inputs

        #define ADS7828_REG_COMMAND_CH_MASK         (0x70)      // Input multiplexer COMMANDuration
        #define ADS7828_REG_COMMAND_CH_DIFF_0_1     (0x00)      // Differential P = CH0, N = CH1
        #define ADS7828_REG_COMMAND_CH_DIFF_2_3     (0x10)      // Differential P = CH2, N = CH3
        #define ADS7828_REG_COMMAND_CH_DIFF_4_5     (0x20)      // Differential P = CH4, N = CH5
        #define ADS7828_REG_COMMAND_CH_DIFF_6_7     (0x30)      // Differential P = CH6, N = CH7
        #define ADS7828_REG_COMMAND_CH_DIFF_1_0     (0x40)      // Differential P = CH1, N = CH0
        #define ADS7828_REG_COMMAND_CH_DIFF_3_2     (0x50)      // Differential P = CH3, N = CH2
        #define ADS7828_REG_COMMAND_CH_DIFF_5_4     (0x60)      // Differential P = CH5, N = CH4
        #define ADS7828_REG_COMMAND_CH_DIFF_7_6     (0x70)      // Differential P = CH7, N = CH6
        #define ADS7828_REG_COMMAND_CH_SINGLE_0     (0x00)      // Single-ended P = CH0, N = COM
        #define ADS7828_REG_COMMAND_CH_SINGLE_1     (0x40)      // Single-ended P = CH1, N = COM //0x40
        #define ADS7828_REG_COMMAND_CH_SINGLE_2     (0x10)      // Single-ended P = CH2, N = COM //0x10
        #define ADS7828_REG_COMMAND_CH_SINGLE_3     (0x50)      // Single-ended P = CH3, N = COM //0x50
        #define ADS7828_REG_COMMAND_CH_SINGLE_4     (0x20)      // Single-ended P = CH4, N = COM //0x20
        #define ADS7828_REG_COMMAND_CH_SINGLE_5     (0x60)      // Single-ended P = CH5, N = COM //0x60
        #define ADS7828_REG_COMMAND_CH_SINGLE_6     (0x30)      // Single-ended P = CH6, N = COM // A6 not working
        #define ADS7828_REG_COMMAND_CH_SINGLE_7     (0x70)      // Single-ended P = CH7, N = COM // Not available

        #define ADS7828_REG_COMMAND_PD_MASK         (0x0C)      // Power-Down Selection
        #define ADS7828_REG_COMMAND_PD_PDADCONV     (0x00)      // Power Down Between A/D Converter Conversions
        #define ADS7828_REG_COMMAND_PD_IROFF_ADON   (0x04)      // Internal Reference OFF and A/D Converter ON
        #define ADS7828_REG_COMMAND_PD_IRON_ADOFF   (0x08)      // Internal Reference ON and A/D Converter OFF
        #define ADS7828_REG_COMMAND_PD_IRON_ADON    (0x0C)      // Internal Reference ON and A/D Converter ON

    typedef enum
    {
        SDMODE_DIFF     = ADS7828_REG_COMMAND_SD_DIFF,
        SDMODE_SINGLE   = ADS7828_REG_COMMAND_SD_SINGLE
    } adsSDMode_t;

    typedef enum
    {
        PDADCONV        = ADS7828_REG_COMMAND_PD_PDADCONV,
        PDIROFF_ADON    = ADS7828_REG_COMMAND_PD_IROFF_ADON,
        PDIRON_ADOFF    = ADS7828_REG_COMMAND_PD_IRON_ADOFF,
        PDIRON_ADON     = ADS7828_REG_COMMAND_PD_IRON_ADON
    } adsPDMode_t;

    class ADS7828
    {
        protected:
            // Instance-specific properties
            uint8_t ads_i2cAddress;
            uint8_t ads_conversionDelay;
            adsSDMode_t ads_sdmode;
            adsPDMode_t ads_pdmode;


        public:
            void getAddr_ADS7828(uint8_t i2cAddress);
            void begin(void);
            uint16_t Measure_SingleEnded(uint8_t channel);
            int16_t Measure_Differential(uint8_t channel);
            void setSDMode(adsSDMode_t sdmode);
            adsSDMode_t getSDMode(void);
            void setPDMode(adsPDMode_t pdmode);
            adsPDMode_t getPDMode(void);

        private:
    };

#endif // VEGA_ARIES_IOT

extern PWMClass PWM;

#endif
