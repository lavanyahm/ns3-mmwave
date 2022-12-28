import io
import os
import array
UeDist = 40.0
Dist_array = []
with open("RxPacketTrace_LOS.dat")as f1:
    for  line1 in f1:
        Dist_array.append(UeDist)
        Dist_array.append('\t')
        Dist_array.append(line1.split('\t')[10])
        Dist_array.append('\n')
        UeDist = UeDist + 0.002572687 
f1.close()        
print (Dist_array)
with open("Data_RxPacketTrace_LOS.dat","w") as fileh:
    for item in Dist_array:
        fileh.write('%s' %item)
fileh.close()            
print ('aaray export')
