
#Run For LOS
./waf --run "scratch/mymmwave-example.cc  --channel_condition=l"
head -n -13094 RxPacketTrace.txt > temp.txt; mv temp.txt RxPacketTrace.txt
cp RxPacketTrace.txt RxPacketTrace_LOS.dat
cp RxPacketTrace.txt CH2_RxPacketTrace_LOS_Ch1.dat
sleep 6

#Run for NLOS
./waf --run "scratch/mymmwave-example.cc  --channel_condition=n"
head -n -13094 RxPacketTrace.txt > temp.txt; mv temp.txt RxPacketTrace.txt
cp RxPacketTrace.txt RxPacketTrace_NLOS.dat
cp RxPacketTrace.txt CH2_RxPacketTrace_NLOS.dat
sleep 6

python3 Paper_1_RxPacketTrace_data_SINR.py

NoOfUe=1


if [ $NoOfUe -eq 1 ]
then
        
	echo "No of Ue is 1."
	gnuplot Paper_1_gnuplot_SINR.gnuplot
	gnuplot Paper_1_gnuplot_Data.gnuplot

	mv Data_RxPacketTrace_LOS_Ue1.dat  Results/CH2_Data_RxPacketTrace_LOS_Ue1.dat
	mv Data_RxPacketTrace_NLOS_Ue1.dat Results/CH2_Data_RxPacketTrace_NLOS_Ue1.dat
	mv SINR_RxPacketTrace_LOS_Ue1.dat  Results/CH2_SINR_RxPacketTrace_LOS_Ue1.dat
	mv SINR_RxPacketTrace_NLOS_Ue1.dat Results/CH2_SINR_RxPacketTrace_NLOS_Ue1.dat
	mv Data_Vs_Distance.png  Results/Table1_Data_Vs_Distance.png
	mv SINR_VS_Distance.png  Results/Table1_SINR_VS_Distance.png

else

	echo "No of Ue are 2."
        gnuplot  Paper_1_SINR_2Ue.gnuplot
        gnuplot  Paper_1_DATA_2Ue.gnuplot

        mv Data_RxPacketTrace_LOS_Ue1.dat  Results/Table1_Data_RxPacketTrace_LOS_Ue1.dat
        mv Data_RxPacketTrace_NLOS_Ue1.dat Results/Table1_Data_RxPacketTrace_NLOS_Ue1.dat
        mv SINR_RxPacketTrace_LOS_Ue1.dat  Results/Table1_SINR_RxPacketTrace_LOS_Ue1.dat
        mv SINR_RxPacketTrace_NLOS_Ue1.dat Results/Table1_SINR_RxPacketTrace_NLOS_Ue1.dat
        mv Data_RxPacketTrace_LOS_Ue2.dat  Results/Table1_Data_RxPacketTrace_LOS_Ue2.dat
        mv Data_RxPacketTrace_NLOS_Ue2.dat Results/Table1_Data_RxPacketTrace_NLOS_Ue2.dat
        mv SINR_RxPacketTrace_LOS_Ue2.dat  Results/Table1_SINR_RxPacketTrace_LOS_Ue2.dat
        mv SINR_RxPacketTrace_NLOS_Ue2.dat Results/Table1_SINR_RxPacketTrace_NLOS_Ue2.dat
        mv SINR_Dist_2Ues.png  Results/Table1_SINR_Vs_Distance.png.png
        mv Data_Vs_Distance.png  Results/Table1_Data_Vs_Distance.png

fi


