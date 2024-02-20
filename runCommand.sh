./ns3 run "scratch/mymmwave-example.cc  --channel_condition=n --numberOfUeNodes=1"
mv RxPacketTrace.txt Data_Bakup/RxPacketTrace_NLOS.dat
sleep 20
./ns3 run "scratch/mymmwave-example.cc  --channel_condition=l --numberOfUeNodes=1"
mv RxPacketTrace.txt Data_Bakup/RxPacketTrace_LOS.dat
