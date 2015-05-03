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


def average(path):

    Loop_1_av = []
    Loop_1_all = []

    Loop_2_av = []
    Loop_2_all = []
    
    for i in ('1','2'):
        Loop_Data  = np.loadtxt(path+'file'+i+'.dat')
    
        if i=='1':
             Loop_1_av = np.average(Loop_Data[...,2])
             info_1 = (Loop_1_av, path)
             Loop_1_all.append(info_1) 
        else:
             Loop_2_av = np.average(Loop_Data[...,2])
             info_2 = (Loop_2_av, path)
             Loop_2_all.append(info_2) 
    
    max_1 = 0  
    for i in range(0,len(Loop_1_all)):
        if (Loop_1_all[i]>max_1):
             max_1 = Loop_1_all[i]

    print '\n\nLoop_1_all', Loop_1_all
    print 'Loop_2_all', Loop_2_all
    print 'max_1' , max_1, '\n\n'

for path in paths:
    average(path)
