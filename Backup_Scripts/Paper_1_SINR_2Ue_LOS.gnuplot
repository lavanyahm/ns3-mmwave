set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "SINR_Dist_2Ue_LOS.png"
set xlabel "Distance (m)"
set ylabel "SINR(dB)"

plot 'SINR_RxPacketTrace_LOS_Ue1.dat' using 1:2 title "Ue1" with lines lw 2.5 lc 'blue', \
     'SINR_RxPacketTrace_LOS_Ue2.dat'  using 1:2 title "Ue2" with lines lw 1.5 lc 'red', 
