set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "SINR_VS_Distance.png"
set xlabel "Distance (m)"
set ylabel "SINR(dB)"

plot 'SINR_RxPacketTrace_LOS.dat' using 1:2 title "LOS" with lines lw 2.5 lc 'blue', \
     'SINR_RxPacketTrace_NLOS.dat'  using 1:2 title "NLOS" with lines lw 1.5 lc 'red', 
