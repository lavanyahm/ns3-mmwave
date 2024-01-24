set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "SINR_VS_Distance_LOS.png"
set xlabel "Distance (m)"
set ylabel "SINR(dB)"
set yrange[-10:60]
set samples 150
plot  'SINR_RxPacketTrace_LOS_Ue1.dat' using 2:3 title "LOS" with lines lw .5 lc 'blue'
