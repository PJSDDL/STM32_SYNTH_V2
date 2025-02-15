#define u8 unsigned char
#define u32 unsigned int
#define s8 signed char

struct SampleCTRL
{
    u8 trig;
    u32 index;
    u32 max_len;
};

struct VCO
{
    char VCO_wavetype;
    short phase;
    short idx;
    short VCO_freq;
    short VCO_Out;
};

struct ADSR
{
    u8 ADSR_enable;
    u8 ADSR_statu;
    u32 ADSR_count;

    u32 A_time;
    u32 D_time;
    u32 R_time;
    u32 A_speed;
    u32 D_speed;
    u32 R_speed;

    u32 velocity;

    u8 ADSR_in;  //ADSR输入触发信号，为1时产生ADSR波形，为0时不产生波形
    u32 ADSR_out_temp;
    u32 ADSR_out;

};

//初始化参数
//void SYNTH_INIT()

//播放采样音频
s8 Sample(const s8 table[], struct SampleCTRL *SampleCTRL);

//VCO
void VCO_gen(struct VCO *VCO_1);
//ADSR
void ADSR(struct ADSR *ADSR_1);

void SaCtInit(struct SampleCTRL SampleCTRL[], u32 len);
