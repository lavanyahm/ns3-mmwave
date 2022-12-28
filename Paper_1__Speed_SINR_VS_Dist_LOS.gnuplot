set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "Speed_SINR_VS_Distance_LOS.png"
set xlabel "Distance (m)"
set ylabel "SINR(dB)"

plot 'Table4_SINR_RxPacketTrace_LOS_Ue1.dat' using 2:3 title "Speed_20ms" with lines lw 2.5 lc 'blue', \
     'Table3_SINR_RxPacketTrace_LOS_Ue1.dat' using 2:3 title "Speed_15ms" with lines lw 2.5 lc 'red', \
     'Table2_SINR_RxPacketTrace_LOS_Ue1.dat' using 2:3 title "Speed_10ms" with lines lw 2.5 lc 'green', \
     'Table1_SINR_RxPacketTrace_LOS_Ue1.dat' using 2:3 title "Speed_5ms" with lines lw 2.5 lc 'yellow', \
