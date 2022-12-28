set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "cwnd.png"
set xlabel "Time (sec)"
set ylabel "cwnd(Packets)"

plot 'mmWave-tcp-window.dat' title "Cwnd" with lines lw 1.5 lc 'blue', 
