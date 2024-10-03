工程说明：本工程是基于STM32F407的波表、采样合成器，使用Keil+CUBEMX、MATLAB、PYTHON开发

烧录后，用示波器观察PA4引脚波形，若要播放音乐，请在PA4口接一个功放

WaveTable用于生成波表
MID2STM32用于将MID文件转为数组，MID文件应是单旋律的，不应有复音
F4Synth是STM32代码

如何播放你自己的MIDI文件：
使用MID2STM32中的PY脚本生成MID数组后，将数组保存在MIDI.C中，然后使用MAIN.C中的Synth_GM与Synth_SA即可生成音频


