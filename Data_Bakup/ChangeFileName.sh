python3 read_SINR_DATA_UE1.py
sleep 10
#mv Data_RxPacketTrace_LOS_Ue1.dat   DATA_RxPacketTrace_UE1_UmiStreetCanyon_LOS.dat 
#mv Data_RxPacketTrace_NLOS_Ue1.dat  DATA_RxPacketTrace_UE1_UmiStreetCanyon_NLOS.dat
#mv SINR_RxPacketTrace_LOS_Ue1.dat   SINR_RxPacketTrace_UE1_UmiStreetCanyon_LOS.dat
#mv SINR_RxPacketTrace_NLOS_Ue1.dat  SINR_RxPacketTrace_UE1_UmiStreetCanyon_NLOS.dat 

mv Data_RxPacketTrace_LOS_Ue1.dat   DATA_RxPacketTrace_UE1_ThreeGppRma_LOS.dat 
mv Data_RxPacketTrace_NLOS_Ue1.dat  DATA_RxPacketTrace_UE1_ThreeGppRma_NLOS.dat
mv SINR_RxPacketTrace_LOS_Ue1.dat   SINR_RxPacketTrace_UE1_ThreeGppRma_LOS.dat
mv SINR_RxPacketTrace_NLOS_Ue1.dat  SINR_RxPacketTrace_UE1_ThreeGppRma_NLOS.dat 

rm SINR_RxPacketTrace_LOS_Ue2.dat
rm SINR_RxPacketTrace_NLOS_Ue2.dat
rm Data_RxPacketTrace_LOS_Ue2.dat
rm Data_RxPacketTrace_NLOS_Ue2.dat
