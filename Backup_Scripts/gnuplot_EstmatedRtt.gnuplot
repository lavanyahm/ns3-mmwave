set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "EstimatedRTT.png"
set xlabel "Time (sec)"
set ylabel "RTT(seconds)"

plot 'Estimated_RTT.dat' title "Drop tail" with lines lw 1.5 lc 'blue', 
