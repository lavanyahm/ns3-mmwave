set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "DATA_VS_Distance_NLOS.png"
set xlabel "Distance (m)"
set ylabel "data(bits)"
#set yrange[80:1140]
#set samples 150
plot 'Data_RxPacketTrace_NLOS_Ue1.dat' using 2:3 title "NLOS" with lines lw .5 lc 'blue'
