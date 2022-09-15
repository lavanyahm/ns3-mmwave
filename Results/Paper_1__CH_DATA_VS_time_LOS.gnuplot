set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "CH_Data_VS_Time_LOS.png"
set xlabel "Time (S)"
set ylabel "Data Rate(Mbps)"

plot 'CH1_Data_RxPacketTrace_LOS_Ue1.dat' using 1:3 title  "Umi" with lines lw 2.5 lc 'blue', \
     'CH3_Data_RxPacketTrace_LOS_Ue1.dat' using 1:3 title "Uma" with lines lw 2.5 lc 'green', \
     'CH4_Data_RxPacketTrace_LOS_Ue1.dat' using 1:3 title "IndoorOff" with lines lw 2.5 lc 'yellow', \
