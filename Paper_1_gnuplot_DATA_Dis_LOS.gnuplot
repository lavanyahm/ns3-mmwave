set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "DATA_VS_Distance_LOS.png"
set xlabel "Distance (m)"
set ylabel "data(bits)"
#set yrange[80:1140]
#set samples 150
plot 'Data_RxPacketTrace_LOS_Ue1.dat' using 2:3 title "LOS" with lines lw .5 lc 'blue'
