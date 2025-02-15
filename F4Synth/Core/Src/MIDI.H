#define u8 unsigned char
#define u32 unsigned int
#define s8 signed char

struct MIDI_CTRL
{
    u8 clk_div;
    u32 mid_cnt;
    u32 mid_index;
    u32 mid_freq;	//����Ƶ��
    u8 mid_vec;		//��������
    s8 note_shift;    //�Ƶ�
};

void MIDI_Control(struct MIDI_CTRL *ctrl, const u32 MIDI_list[], u8 *trig);
void MIDI_CTRL_INIT(struct MIDI_CTRL ctrl[], u32 len);
