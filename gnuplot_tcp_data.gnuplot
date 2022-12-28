set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "Packets_size.png"
set xlabel "Time (sec)"
set ylabel "Packets Size"

set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 2 \
    pointtype 7 pointsize 1.5
set style line 2 \
    linecolor rgb '#dd181f' \
    linetype 1 linewidth 2 \
    pointtype 5 pointsize 1.5


plot 'mmWave-tcp-data.dat' index 0 with linespoints linestyle 1, \
     ''                   index 1 with linespoints linestyle 2
