clc
close all

%程序用于生成采样表与波表

%简单波形
% x = 127*sin(2*3.1415926*[1:1000]/1000);
% x = 255 * rand(1, 1000) - 127;
% x = 256 * exp(-3.1415926*[1:1000]/1000)
% x = 126*cos(2*3.1415926*[1:1000]/1000);


% %乐器采样
% [x_s, fs] = wavread('Tambourine2.wav');
% x = resample(x_s(:,1),20000,44100);
% x = fix(x);
% x = x(1:15000)
% x = 128 * (x / max(x));


%乐器单周期采样，制成波表
[x_s, fs] = wavread('trumpt.wav');
subplot(2,1,1)
plot(x_s)
x = x_s(15550:15630);  %截取所选音频的几个周期
x_len = size(x);
x = resample(x, 1000, x_len(2)-2);
x = x(1:1000);  %切掉边缘振荡
x = 128 * (x / max(abs(x)));
x = fix(x);
subplot(2,1,2)
plot(x)
%播放波表,试听效果
x_ = [];
for i = 1:100
    x_ = [x_, x];
end
sound(x_, 480000)  



fileID = fopen('table.txt', 'w');
fprintf(fileID, ',%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n', x);
fclose(fileID);

