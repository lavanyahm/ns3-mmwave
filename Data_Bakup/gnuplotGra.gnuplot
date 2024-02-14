  2 set output "SINR_VS.png"
  3 set xlabel "Distance (m)"
  4 set ylabel "SINR(dB)"
  5 
  6 plot 'SINR_RxPacketTrace_LOS_Ue1.dat' using 1:13 title "LOS" with lines lw 2.5 lc 'blue', \
  7      'SINR_RxPacketTrace_NLOS_Ue1.dat'  using 1:13 title "NLOS" with lines lw 1.5 lc 'red',
