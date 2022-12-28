set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "SINR_Dist_2Ues.png"
set xlabel "Distance (m)"
set ylabel "SINR(dB)"

plot 'SINR_RxPacketTrace_NLOS_Ue1.dat' using 2:3 title "Ue1-NLOS" with lines lw 2.5 lc 'blue', \
     'SINR_RxPacketTrace_NLOS_Ue2.dat'  using 2:3 title "Ue2-NLOS" with lines lw 1.5 lc 'red', \
     'SINR_RxPacketTrace_LOS_Ue1.dat'  using 2:3 title "Ue1-LOS" with lines lw 1.5 lc 'green', \
     'SINR_RxPacketTrace_LOS_Ue2.dat'  using 2:3 title "Ue2-LOS" with lines lw 1.5 lc 'yellow', 
