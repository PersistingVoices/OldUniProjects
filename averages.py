import numpy as np 

paths = [
       #"Q1_Data/HS-Q1-"
       #"Q1_Data/HS-Q1-",

        "Q2_Data/Auto_Data/AUTO-",
        "Q2_Data/Affinity_Data/",

        "Q2_Data/Guided-n_Data/G/G1Data/GUIDED-n-",
        "Q2_Data/Guided-n_Data/G/G2Data/GUIDED-n-",
        "Q2_Data/Guided-n_Data/G/G4Data/GUIDED-n-",
        "Q2_Data/Guided-n_Data/G/G8Data/GUIDED-n-",
        "Q2_Data/Guided-n_Data/G/G16Data/GUIDED-n-",
        "Q2_Data/Guided-n_Data/G/G32Data/GUIDED-n-",
        "Q2_Data/Guided-n_Data/G/G64Data/GUIDED-n-",
       
        "Q2_Data/STATIC_Data/STATIC-"
        ]


def average(path, num):
    Loop_Data  = np.loadtxt(path+'file'+str(num)+'.dat')
    return np.average(Loop_Data[...,2])


average_1 = [average(path, 1) for path in paths]
average_2 = [average(path, 2) for path in paths]

print 'average_1' , average_1
print 'average_2' , average_2

max_1 =  max(average_1)
max_2 =  max(average_2)

ratio_1 = [average_1[i]/max_1 for i in range(0,len(average_1))]
ratio_2 = [average_2[i]/max_2 for i in range(0,len(average_2))]

print 'ratio_1', ratio_1
print 'ratio_2', ratio_2
