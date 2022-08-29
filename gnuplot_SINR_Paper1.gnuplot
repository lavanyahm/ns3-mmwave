set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "SINR_Dis.png"
set xlabel "Distance (m)"
set ylabel "SINR(dB)"

plot 'LOS_Results_Paper1/SINR_data_LOS.dat' using 1:2 title "LOS" with lines lw 2.5 lc 'blue', \
     'NLOS_Results_Paper1/SINR_data_NLOS.dat'  using 1:2 title "NLOS" with lines lw 1.5 lc 'red', 
