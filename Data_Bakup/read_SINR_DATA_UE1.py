import io
import os
import array

Ue1_IsMobile = 'T'
Ue2_IsMobile = 'F'

Ue1_iniPosi = 40.0
Ue2_iniPosi = 60.0
Ue1_movement = 0.002572687 
Ue2_movement = 0.002572687
Ue_1_data_array = []
Ue_2_data_array = []
Ue_1_SINR_array = []
Ue_2_SINR_array = []



if ( Ue1_IsMobile == 'F'):
        Ue1_movement = 0 


if ( Ue2_IsMobile == 'F'):
        Ue2_movement = 0 


with open("RxPacketTrace_NLOS.dat")as f1:
    for  line1 in f1:
        if (line1.split('\t')[8]) == '1':
            Ue_1_data_array.append(line1.split('\t')[1] )
            Ue_1_data_array.append('\t')
            Ue_1_data_array.append(Ue1_iniPosi)
            Ue_1_data_array.append('\t')
            Ue_1_data_array.append(line1.split('\t')[10])
            Ue_1_data_array.append('\n')

            Ue_1_SINR_array.append(line1.split('\t')[1] )
            Ue_1_SINR_array.append('\t')
            Ue_1_SINR_array.append(Ue1_iniPosi) 
            Ue_1_SINR_array.append('\t')
            Ue_1_SINR_array.append(line1.split('\t')[13])
            Ue_1_SINR_array.append('\n')
            Ue1_iniPosi = Ue1_iniPosi + Ue1_movement
        else:
            Ue_2_data_array.append(line1.split('\t')[1])
            Ue_2_data_array.append('\t')
            Ue_2_data_array.append(Ue2_iniPosi)
            Ue_2_data_array.append('\t')
            Ue_2_data_array.append(line1.split('\t')[10])
            Ue_2_data_array.append('\n')

            Ue_2_SINR_array.append(line1.split('\t')[1] )
            Ue_2_SINR_array.append('\t')
            Ue_2_SINR_array.append(Ue2_iniPosi) 
            Ue_2_SINR_array.append('\t')
            Ue_2_SINR_array.append(line1.split('\t')[13])
            Ue_2_SINR_array.append('\n')
            Ue2_iniPosi = Ue2_iniPosi + Ue2_movement
f1.close()        
with open("Data_RxPacketTrace_NLOS_Ue1.dat","w") as fileh:
    for item in Ue_1_data_array:
        fileh.write('%s' %item)
fileh.close()            
with open("Data_RxPacketTrace_NLOS_Ue2.dat","w") as fileh:
    for item in Ue_2_data_array:
        fileh.write('%s' %item)
fileh.close()  
with open("SINR_RxPacketTrace_NLOS_Ue1.dat","w") as fileh:
    for item in Ue_1_SINR_array:
        fileh.write('%s' %item)
fileh.close()            
with open("SINR_RxPacketTrace_NLOS_Ue2.dat","w") as fileh:
    for item in Ue_2_SINR_array:
        fileh.write('%s' %item)
fileh.close()            

#Opening file in LOS 
Ue_1_data_array_LOS = []
Ue_2_data_array_LOS = []
Ue_1_SINR_array_LOS = []
Ue_2_SINR_array_LOS = []

Ue1_iniPosi = 40.0
Ue2_iniPosi = 60.0



with open("RxPacketTrace_LOS.dat")as f1:
    for  line1 in f1:
        if (line1.split('\t')[8]) == '1':
            Ue_1_data_array_LOS.append(line1.split('\t')[1] )
            Ue_1_data_array_LOS.append('\t')
            Ue_1_data_array_LOS.append(Ue1_iniPosi)
            Ue_1_data_array_LOS.append('\t')
            Ue_1_data_array_LOS.append(line1.split('\t')[10])
            Ue_1_data_array_LOS.append('\n')

            Ue_1_SINR_array_LOS.append(line1.split('\t')[1] )
            Ue_1_SINR_array_LOS.append('\t')
            Ue_1_SINR_array_LOS.append(Ue1_iniPosi) 
            Ue_1_SINR_array_LOS.append('\t')
            Ue_1_SINR_array_LOS.append(line1.split('\t')[13])
            Ue_1_SINR_array_LOS.append('\n')
            Ue1_iniPosi = Ue1_iniPosi + Ue1_movement
        else:
            Ue_2_data_array_LOS.append(line1.split('\t')[1])
            Ue_2_data_array_LOS.append('\t')
            Ue_2_data_array_LOS.append(Ue2_iniPosi)
            Ue_2_data_array_LOS.append('\t')
            Ue_2_data_array_LOS.append(line1.split('\t')[10])
            Ue_2_data_array_LOS.append('\n')

            Ue_2_SINR_array_LOS.append(line1.split('\t')[1] )
            Ue_2_SINR_array_LOS.append('\t')
            Ue_2_SINR_array_LOS.append(Ue2_iniPosi) 
            Ue_2_SINR_array_LOS.append('\t')
            Ue_2_SINR_array_LOS.append(line1.split('\t')[13])
            Ue_2_SINR_array_LOS.append('\n')
            Ue2_iniPosi = Ue2_iniPosi + Ue2_movement
f1.close()        
with open("Data_RxPacketTrace_LOS_Ue1.dat","w") as fileh:
    for item in Ue_1_data_array_LOS:
        fileh.write('%s' %item)
fileh.close()            
with open("Data_RxPacketTrace_LOS_Ue2.dat","w") as fileh:
    for item in Ue_2_data_array_LOS:
        fileh.write('%s' %item)
fileh.close()  
with open("SINR_RxPacketTrace_LOS_Ue1.dat","w") as fileh:
    for item in Ue_1_SINR_array_LOS:
        fileh.write('%s' %item)
fileh.close()            
with open("SINR_RxPacketTrace_LOS_Ue2.dat","w") as fileh:
    for item in Ue_2_SINR_array_LOS:
        fileh.write('%s' %item)
fileh.close() 
