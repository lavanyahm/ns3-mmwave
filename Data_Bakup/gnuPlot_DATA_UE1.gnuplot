set terminal pngcairo enhanced color lw 1.5 font 'Times Roman'
set output "DATA_VS_Distance_NLOS.png"
set xlabel "Distance (m)"
set ylabel "DATA(bits)"
#set yrange[80:1140]
#set samples 150
plot 'DATA_RxPacketTrace_UE1_UmiStreetCanyon_NLOS.dat' using 2:3 title "UmiStreetCanyon" with lines lw .5 lc 'blue', \
     'DATA_RxPacketTrace_UE1_ThreeGppUma_NLOS.dat' using 2:3 title "ThreeGppUma" with lines lw .5 lc 'red', \
     'DATA_RxPacketTrace_UE1_ThreeGppRma_NLOS.dat' using 2:3 title "ThreeGppRma" with lines lw .5 lc 'green'
