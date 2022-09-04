import io
import os
import array
Ue1_iniPosi = 40.0
Ue2_iniPosi = 60.0
Ue_1_data_array = []
Ue_2_data_array = []
Ue_1_SINR_array = []
Ue_2_SINR_array = []
with open("RxPacketTrace_LOS.dat")as f1:
    for  line1 in f1:
        if (line1.split('\t')[8]) == '1':
            print(line1.split('\t')[8])
            Ue_1_data_array.append(Ue1_iniPosi)
            Ue_1_data_array.append('\t')
            Ue_1_data_array.append(line1.split('\t')[10])
            Ue_1_data_array.append('\n')
            Ue_1_SINR_array.append(Ue1_iniPosi) 
            Ue_1_SINR_array.append('\t')
            Ue_1_SINR_array.append(line1.split('\t')[13])
            Ue_1_SINR_array.append('\n')
            Ue1_iniPosi = Ue1_iniPosi + 0.002572687 
        else:
            print(line1.split('\t')[8])
            Ue_2_data_array.append(Ue2_iniPosi)
            Ue_2_data_array.append('\t')
            Ue_2_data_array.append(line1.split('\t')[10])
            Ue_2_data_array.append('\n')
            Ue_2_SINR_array.append(Ue1_iniPosi) 
            Ue_2_SINR_array.append('\t')
            Ue_2_SINR_array.append(line1.split('\t')[13])
            Ue_2_SINR_array.append('\n')
            Ue2_iniPosi = Ue2_iniPosi + 0.002572687 
f1.close()        
with open("Data_RxPacketTrace_LOS_Ue1.dat","w") as fileh:
    for item in Ue_1_data_array:
        fileh.write('%s' %item)
fileh.close()            
with open("Data_RxPacketTrace_LOS_Ue2.dat","w") as fileh:
    for item in Ue_2_data_array:
        fileh.write('%s' %item)
fileh.close()  
with open("SINR_RxPacketTrace_LOS_Ue1.dat","w") as fileh:
    for item in Ue_1_SINR_array:
        fileh.write('%s' %item)
fileh.close()            
with open("SINR_RxPacketTrace_LOS_Ue2.dat","w") as fileh:
    for item in Ue_2_SINR_array:
        fileh.write('%s' %item)
fileh.close()            



