set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "Test.png"
set xlabel "Distance (m)"
set ylabel "SINR(dB)"

plot  'Table1_SINR_RxPacketTrace_LOS_Ue1.dat' using 2:3 title "LOS" with lines lw 2.5 lc 'blue', \
     'Table1_SINR_RxPacketTrace_NLOS_Ue1.dat'  using 2:3 title "NLOS" with lines lw 1.5 lc 'red', 
