clc
clear all
[y,Fs] = audioread('tiger.mp3');
player = audioplayer(y,Fs);
player.TimerPeriod=0.025;

player.play;
p = 0;
num_of_bars = 5;
bars = zeros(1, num_of_bars + 2);
cell_arr = mat2cell([jet(num_of_bars); 0 0 0; 1 1 1], ones(num_of_bars + 2, 1));
while(player.isplaying)
   [p,bars]= currentfftv4(player,y,Fs, p, num_of_bars, cell_arr,bars);
   drawnow limitrate
end