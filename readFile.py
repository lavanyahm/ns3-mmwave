import io
import os
import array
Dist_array = []
with open("distance_time.csv", "r") as f1, open("RxPacketTrace.dat")as f2:
    for  line1,line2 in zip(f1,f2):
        ls = (line1.split(',')[17])
        Dist_array.append(ls.strip())
        Dist_array.append('\t')
        Dist_array.append(line2.split('\t')[13])
        Dist_array.append('\n')
print (Dist_array)
with open("SINR_data_LOS.dat","w") as fileh:
    for item in Dist_array:
        fileh.write('%s' %item)
            
print ('aaray export')
