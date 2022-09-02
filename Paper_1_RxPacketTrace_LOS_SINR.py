import io
import os
import array
print('Mapping SINR with Ue distance')
UeInitialDist = 40.00
Dist_array = []
with open("RxPacketTrace_LOS.dat")as f1:
    for  line1 in f1:
        Dist_array.append(UeDist)
        Dist_array.append('\t')
        Dist_array.append(line1.split('\t')[13])
        Dist_array.append('\n')
        UeInitialDist = UeInitialDist + 0.002572687 
f1.close()        
print (Dist_array)
with open("SINR_RxPacketTrace_LOS.dat","w") as fileh:
    for item in Dist_array:
        fileh.write('%s' %item)
fileh.close()            
print ('aaray export')
