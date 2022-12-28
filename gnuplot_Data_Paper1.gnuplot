set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "DATARATE.png"
set xlabel "Distance (m)"
set ylabel "DATA"

plot 'DlRlcStats.txt' using 1:3 title "LOS" with lines lw 2.5 lc 'blue', \
     ''  using 1:2 title "NLOS" with lines lw 1.5 lc 'red', 
