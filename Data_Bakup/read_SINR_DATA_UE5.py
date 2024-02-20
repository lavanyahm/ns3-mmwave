import io
import os
import array

Ue1_IsMobile = 'T'
Ue2_IsMobile = 'T'
Ue3_IsMobile = 'T'
Ue4_IsMobile = 'T'
Ue5_IsMobile = 'T'

Ue1_iniPosi = 20.0
Ue2_iniPosi = 25.0
Ue3_iniPosi = 30.0
Ue4_iniPosi = 35.0
Ue5_iniPosi = 40.0


Ue1_movement = 0.002572687 
Ue2_movement = 0.002572687
Ue3_movement = 0.002572687 
Ue4_movement = 0.002572687 
Ue5_movement = 0.002572687 



Ue_1_data_array = []
Ue_2_data_array = []
Ue_3_data_array = []
Ue_4_data_array = []
Ue_5_data_array = []


Ue_1_SINR_array = []
Ue_2_SINR_array = []
Ue_3_SINR_array = []
Ue_4_SINR_array = []
Ue_5_SINR_array = []


if ( Ue1_IsMobile == 'F'):
        Ue1_movement = 0 


if ( Ue2_IsMobile == 'F'):
        Ue2_movement = 0 

if ( Ue3_IsMobile == 'F'):
        Ue1_movement = 0 


if ( Ue4_IsMobile == 'F'):
        Ue2_movement = 0 


if ( Ue5_IsMobile == 'F'):
        Ue1_movement = 0 

# 8th clou7mn is Rnti value which says ue number
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
        
        elif (line1.split('\t')[8]) == '2':
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


        elif (line1.split('\t')[8]) == '3':
            Ue_3_data_array.append(line1.split('\t')[1])
            Ue_3_data_array.append('\t')
            Ue_3_data_array.append(Ue2_iniPosi)
            Ue_3_data_array.append('\t')
            Ue_3_data_array.append(line1.split('\t')[10])
            Ue_3_data_array.append('\n')

            Ue_3_SINR_array.append(line1.split('\t')[1] )
            Ue_3_SINR_array.append('\t')
            Ue_3_SINR_array.append(Ue2_iniPosi) 
            Ue_3_SINR_array.append('\t')
            Ue_3_SINR_array.append(line1.split('\t')[13])
            Ue_3_SINR_array.append('\n')
            Ue3_iniPosi = Ue3_iniPosi + Ue3_movement


        elif (line1.split('\t')[8]) == '4':
            Ue_4_data_array.append(line1.split('\t')[1])
            Ue_4_data_array.append('\t')
            Ue_4_data_array.append(Ue2_iniPosi)
            Ue_4_data_array.append('\t')
            Ue_4_data_array.append(line1.split('\t')[10])
            Ue_4_data_array.append('\n')

            Ue_4_SINR_array.append(line1.split('\t')[1] )
            Ue_4_SINR_array.append('\t')
            Ue_4_SINR_array.append(Ue2_iniPosi) 
            Ue_4_SINR_array.append('\t')
            Ue_4_SINR_array.append(line1.split('\t')[13])
            Ue_4_SINR_array.append('\n')
            Ue4_iniPosi = Ue4_iniPosi + Ue4_movement


        elif (line1.split('\t')[8]) == '5':
            Ue_5_data_array.append(line1.split('\t')[1])
            Ue_5_data_array.append('\t')
            Ue_5_data_array.append(Ue2_iniPosi)
            Ue_5_data_array.append('\t')
            Ue_5_data_array.append(line1.split('\t')[10])
            Ue_5_data_array.append('\n')

            Ue_5_SINR_array.append(line1.split('\t')[1] )
            Ue_5_SINR_array.append('\t')
            Ue_5_SINR_array.append(Ue2_iniPosi) 
            Ue_5_SINR_array.append('\t')
            Ue_5_SINR_array.append(line1.split('\t')[13])
            Ue_5_SINR_array.append('\n')
            Ue5_iniPosi = Ue5_iniPosi + Ue5_movement

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


with open("Data_RxPacketTrace_NLOS_Ue3.dat","w") as fileh:
    for item in Ue_3_data_array:
        fileh.write('%s' %item)
fileh.close()            
with open("Data_RxPacketTrace_NLOS_Ue4.dat","w") as fileh:
    for item in Ue_4_data_array:
        fileh.write('%s' %item)
fileh.close()  
with open("SINR_RxPacketTrace_NLOS_Ue3.dat","w") as fileh:
    for item in Ue_3_SINR_array:
        fileh.write('%s' %item)
fileh.close()            
with open("SINR_RxPacketTrace_NLOS_Ue4.dat","w") as fileh:
    for item in Ue_4_SINR_array:
        fileh.write('%s' %item)
fileh.close()            



with open("Data_RxPacketTrace_NLOS_Ue5.dat","w") as fileh:
    for item in Ue_5_data_array:
        fileh.write('%s' %item)
fileh.close()       
with open("SINR_RxPacketTrace_NLOS_Ue5.dat","w") as fileh:
    for item in Ue_5_SINR_array:
        fileh.write('%s' %item)
fileh.close()            



Ue1_iniPosi = 20.0
Ue2_iniPosi = 25.0
Ue3_iniPosi = 30.0
Ue4_iniPosi = 35.0
Ue5_iniPosi = 40.0



Ue_1_data_array_LOS = []
Ue_2_data_array_LOS = []
Ue_3_data_array_LOS = []
Ue_4_data_array_LOS = []
Ue_5_data_array_LOS = []


Ue_1_SINR_array_LOS = []
Ue_2_SINR_array_LOS = []
Ue_3_SINR_array_LOS = []
Ue_4_SINR_array_LOS = []
Ue_5_SINR_array_LOS = []



# 8th clou7mn is Rnti value which says ue number
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
        
        elif (line1.split('\t')[8]) == '2':
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


        elif (line1.split('\t')[8]) == '3':
            Ue_3_data_array_LOS.append(line1.split('\t')[1])
            Ue_3_data_array_LOS.append('\t')
            Ue_3_data_array_LOS.append(Ue2_iniPosi)
            Ue_3_data_array_LOS.append('\t')
            Ue_3_data_array_LOS.append(line1.split('\t')[10])
            Ue_3_data_array_LOS.append('\n')

            Ue_3_SINR_array_LOS.append(line1.split('\t')[1] )
            Ue_3_SINR_array_LOS.append('\t')
            Ue_3_SINR_array_LOS.append(Ue2_iniPosi) 
            Ue_3_SINR_array_LOS.append('\t')
            Ue_3_SINR_array_LOS.append(line1.split('\t')[13])
            Ue_3_SINR_array_LOS.append('\n')
            Ue3_iniPosi = Ue3_iniPosi + Ue3_movement


        elif (line1.split('\t')[8]) == '4':
            Ue_4_data_array_LOS.append(line1.split('\t')[1])
            Ue_4_data_array_LOS.append('\t')
            Ue_4_data_array_LOS.append(Ue2_iniPosi)
            Ue_4_data_array_LOS.append('\t')
            Ue_4_data_array_LOS.append(line1.split('\t')[10])
            Ue_4_data_array_LOS.append('\n')

            Ue_4_SINR_array_LOS.append(line1.split('\t')[1] )
            Ue_4_SINR_array_LOS.append('\t')
            Ue_4_SINR_array_LOS.append(Ue2_iniPosi) 
            Ue_4_SINR_array_LOS.append('\t')
            Ue_4_SINR_array_LOS.append(line1.split('\t')[13])
            Ue_4_SINR_array_LOS.append('\n')
            Ue4_iniPosi = Ue4_iniPosi + Ue4_movement


        elif (line1.split('\t')[8]) == '5':
            Ue_5_data_array_LOS.append(line1.split('\t')[1])
            Ue_5_data_array_LOS.append('\t')
            Ue_5_data_array_LOS.append(Ue2_iniPosi)
            Ue_5_data_array_LOS.append('\t')
            Ue_5_data_array_LOS.append(line1.split('\t')[10])
            Ue_5_data_array_LOS.append('\n')

            Ue_5_SINR_array_LOS.append(line1.split('\t')[1] )
            Ue_5_SINR_array_LOS.append('\t')
            Ue_5_SINR_array_LOS.append(Ue2_iniPosi) 
            Ue_5_SINR_array_LOS.append('\t')
            Ue_5_SINR_array_LOS.append(line1.split('\t')[13])
            Ue_5_SINR_array_LOS.append('\n')
            Ue5_iniPosi = Ue5_iniPosi + Ue5_movement

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


with open("Data_RxPacketTrace_LOS_Ue3.dat","w") as fileh:
    for item in Ue_3_data_array_LOS:
        fileh.write('%s' %item)
fileh.close()            
with open("Data_RxPacketTrace_LOS_Ue4.dat","w") as fileh:
    for item in Ue_4_data_array_LOS:
        fileh.write('%s' %item)
fileh.close()  
with open("SINR_RxPacketTrace_LOS_Ue3.dat","w") as fileh:
    for item in Ue_3_SINR_array_LOS:
        fileh.write('%s' %item)
fileh.close()            
with open("SINR_RxPacketTrace_LOS_Ue4.dat","w") as fileh:
    for item in Ue_4_SINR_array_LOS:
        fileh.write('%s' %item)
fileh.close()            



with open("Data_RxPacketTrace_LOS_Ue5.dat","w") as fileh:
    for item in Ue_5_data_array_LOS:
        fileh.write('%s' %item)
fileh.close()       
with open("SINR_RxPacketTrace_LOS_Ue5.dat","w") as fileh:
    for item in Ue_5_SINR_array_LOS:
        fileh.write('%s' %item)
fileh.close()            




