set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "Data_Vs_Distance.png"
set xlabel "Distance (m)"
set ylabel "Data rate(Gbs)"

plot 'Data_RxPacketTrace_LOS_Ue1.dat' using 1:2 title "Ue1-LOS" with lines lw 2.5 lc 'blue', \
     'Data_RxPacketTrace_LOS_Ue2.dat'  using 1:2 title "Ue2-LOS" with lines lw 1.5 lc 'red', \
     'Data_RxPacketTrace_NLOS_Ue1.dat'  using 1:2 title "Ue1-NLOS" with lines lw 1.5 lc 'green', \
     'Data_RxPacketTrace_NLOS_Ue2.dat'  using 1:2 title "Ue2-NLOS" with lines lw 1.5 lc 'yellow', 
