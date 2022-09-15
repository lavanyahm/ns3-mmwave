set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "CH_Data_VS_Distnace_LOS.png"
set xlabel "Distance(m)"
set ylabel "Data Rate(Mbps)"

plot 'CH1_Data_RxPacketTrace_LOS_Ue1.dat' using 2:3 title  "Umi" with lines lw 2.5 lc 'blue', \
     'CH3_Data_RxPacketTrace_LOS_Ue1.dat' using 2:3 title "Uma" with lines lw 2.5 lc 'green', \
     'CH4_Data_RxPacketTrace_LOS_Ue1.dat' using 2:3 title "IndoorOff" with lines lw 2.5 lc 'yellow', \
