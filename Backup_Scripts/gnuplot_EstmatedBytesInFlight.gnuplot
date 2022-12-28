set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "BytesInFligt.png"
set xlabel "Time (sec)"
set ylabel "byest in Flight (Bytes)"

plot 'Estimated_BytesInFlight.dat' title "Cwnd" with lines lw 1.5 lc 'blue', 
