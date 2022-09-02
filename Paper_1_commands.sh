head -n -13094 RxPacketTrace.txt > temp.txt; mv temp.txt RxPacketTrace.txt
cp RxPacketTrace.txt RxPacketTrace_LOS.dat
python3 Paper_1_RxPacketTrace_LOS_SINR.py
python3 Paper_1_RxPacketTrace_LOS_data.py
/waf --run scratch/mymmwave-example.cc with Los
#cp RxPacketTrace.txt RxPacketTrace_NLOS.dat
#python3 Paper_1_RxPacketTrace_LOS_SINR.py
gnuplot final_gnuplot_data_Paper1.gnuplot


python3  final_RxPacketTrace_NLOS.py
python3  final_RxPacketTrace_LOS.py
final_gnuplot_SINR_Paper1.gnuplot

