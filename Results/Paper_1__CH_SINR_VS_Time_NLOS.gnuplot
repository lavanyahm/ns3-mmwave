set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "CH_SINR_VS_Time_NLOS.png"
set xlabel "Time (S)"
set ylabel "SINR Rate(Mbps)"

plot 'CH1_SINR_RxPacketTrace_NLOS_Ue1.dat' using 1:3 title  "Umi" with lines lw 2.5 lc 'blue', \
     'CH3_SINR_RxPacketTrace_NLOS_Ue1.dat' using 1:3 title "Uma" with lines lw 2.5 lc 'green', \
     'CH4_SINR_RxPacketTrace_NLOS_Ue1.dat' using 1:3 title "IndoorOff" with lines lw 2.5 lc 'yellow', \
