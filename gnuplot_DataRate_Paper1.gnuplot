set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "DATARATE.png"
set xlabel "Distance (m)"
set ylabel "DATA"

plot 'NLOS_Results_Paper1/RxPacketTrace.txt' using 2:11 title "NLOS" with lines lw 2.5 lc 'blue', \
     'LOS_Results_Paper1/RxPacketTrace.txt'  using 2:11 title "LOS" with lines lw 1.5 lc 'red', 
