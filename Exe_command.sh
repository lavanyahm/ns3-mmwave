./waf --run "scratch/mymmwave-example.cc  --channel_condition=l"
head -n -13094 RxPacketTrace.txt > temp.txt; mv temp.txt RxPacketTrace.txt
cp RxPacketTrace.txt RxPacketTrace_LOS.dat
python3 Paper_1_RxPacketTrace_LOS_data_SINR.py
sleep 6

./waf --run "scratch/mymmwave-example.cc  --channel_condition=n"
head -n -13094 RxPacketTrace.txt > temp.txt; mv temp.txt RxPacketTrace.txt
cp RxPacketTrace.txt RxPacketTrace_NLOS.dat
python3 Paper_1_RxPacketTrace_NLOS_data_SINR.py
sleep 6
gnuplot Paper_1_gnuplot_SINR.gnuplot
gnuplot Paper_1_gnuplot_Data.gnuplot

#mv Data_RxPacketTrace_LOS_Ue1.dat  Results/
#mv Data_RxPacketTrace_NLOS_Ue1.dat Results/
#mv SINR_RxPacketTrace_LOS_Ue1.dat  Results/
#mv SINR_RxPacketTrace_NLOS_Ue1.dat Results/
#mv SINR_VS_Distance.png  Results/
#mv Data_Distance.png  Results/

