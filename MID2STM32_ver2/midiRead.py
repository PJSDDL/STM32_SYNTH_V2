import mido
import os
import wave
import numpy as np
import random
import librosa
import matplotlib.pyplot as plt

def MIDIRead(fs, channel, MIDIfilename):
    mid = mido.MidiFile(MIDIfilename)

    track = mid.tracks[channel]  
    ticks = mid.tracks[0][0].tempo/1000000
    beat = (mid.tracks[0][1].numerator)*(mid.tracks[0][1].denominator)
    beat = beat *(mid.tracks[0][1].clocks_per_click) 
    beat = beat/4.0

    return ticks/beat, track

#MID音符长度与毫秒时间转换
def MIDITime2SampleTime(NoteTime, fs, Timerate):
    SampleTime = NoteTime * 1000 * Timerate
    SampleTime = int(SampleTime)
    
    return SampleTime

if __name__=='__main__':
    print('Start')

    file_list = os.listdir("MIDI")
    SN_num = 1

    for file_name in file_list :
        fs = 44100
        Timerate, track = MIDIRead(fs, 1, "MIDI\\" + file_name)

        note = []
        timeSum = 0
        MIDI_index = 1

        delay_time = 0

        #print(track)

        for i in range (0, len(track)):
            try:
                #读取事件长度
                track[MIDI_index].note #跳过非音符事件
                SNoteTime = track[MIDI_index].time
                SNoteTime = MIDITime2SampleTime(SNoteTime, fs, Timerate)

                #处理音符音高，0代表音符停止
                if track[MIDI_index].type == 'note_on' :
                    note.append(track[MIDI_index].note)
                    delay_time = 0
                else :
                    note.append(0)
                    delay_time = -1

                #处理音符时间
                if SNoteTime == 0:
                    note.append(timeSum + 1)
                else:
                    #处理长度不为零的事件
                    note.append(timeSum + SNoteTime + delay_time)

                    timeSum = timeSum + SNoteTime;

                #处理音符力度
                note.append(track[MIDI_index].velocity)

                MIDI_index = MIDI_index + 1

            except:
                pass

        MID_str = ''

        print('const u32 MIDI' + str(SN_num) + '[' + str(int(len(note))) + '] = {')
        for i in range (0, len(note)):
            MID_str = MID_str + str(note[i]) + ','
            if i % 25 == 24 :
                MID_str = MID_str + '\n'

        print(MID_str)
        print('};')
        #print('const unsigned int MIDI_LENGEH = ', len(note), ';')

        SN_num += 1


