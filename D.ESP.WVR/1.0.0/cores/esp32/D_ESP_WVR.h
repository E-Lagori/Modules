#ifdef D_ESP_WVR_H
#define D_ESP_WVR_H

#ifndef BOARDCONF
struct boardconf
{
    uint8_t reserved;
    uint8_t brdtype;
    uint8_t brdno;
};
#define BOARDCONF
#endif

class D_ESP_WVR
{
    bool phCinuse[16], A_Dstate;
    boardconf b;
    uint8_t swtime, seqlen_, seq[16];
    bool con_, sync_;
    struct
    {
        uint8_t timer = 6;
        uint freq = 5000;
        uint res = 12;
        int maxval = 4096;
    } dac;

public:
    D_ESP_WVR(uint8_t bno = 0x81, uint8_t dactimer = 6);
    void whoami(boardconf *);
    bool con() { return this->con_; };
    void trycon();
    void setmux(uint8_t);
    void muxseq(float swtime, uint8_t len, uint8_t *seq, bool sync);
    void clock(float freq);
    bool sync();
    float analogRead();
    void initmuxseqacq(uint8_t syncch);
    void analogWrite(float);
    uint8_t res_dac(uint8_t res = 0);
};

#endif