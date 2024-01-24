set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "SINR_VS_Distance_NLOS.png"
set xlabel "Distance (m)"
set ylabel "SINR(dB)"
set yrange[-10:60]
set samples 150
plot  'SINR_RxPacketTrace_NLOS_Ue1.dat' using 2:3 title "NLOS" with lines lw .5 lc 'blue'
