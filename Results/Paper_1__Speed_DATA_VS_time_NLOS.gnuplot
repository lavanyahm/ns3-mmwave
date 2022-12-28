set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "Speed_Data_VS_Time_NLOS.png"
set xlabel "Time (S)"
set ylabel "Data Rate(Mbps)"

plot 'Table4_Data_RxPacketTrace_NLOS_Ue1.dat' using 1:3 title "Speed=20ms" with lines lw 2.5 lc 'blue', \
     'Table3_Data_RxPacketTrace_NLOS_Ue1.dat' using 1:3 title "Speed=15ms" with lines lw 2.5 lc 'red', \
     'Table2_Data_RxPacketTrace_NLOS_Ue1.dat' using 1:3 title "Speed=10ms" with lines lw 2.5 lc 'green', \
     'Table1_Data_RxPacketTrace_NLOS_Ue1.dat' using 1:3 title "Speed=5ms" with lines lw 2.5 lc 'yellow', \
