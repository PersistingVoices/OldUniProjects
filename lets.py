import numpy as np
import sys
import math as m
from pprint import pprint as pp

# EX= int(raw_input('Enter EX: '))
EX = 54000000000.0
# EY= int(raw_input('Enter EY: '))
EY = 18000000000.0
# GXY= int(raw_input('Enter GXY: '))
GXY = 6000000000
# VXY= float(raw_input('Enter VXY: '))
VXY = 0.28 
# VYX= float(raw_input('Enter VYX (enter 0 if only VXY): '))
VYX = 0

Q   = np.array([[0.0,0.0,0.0],
              [0.0,0.0,0.0],
              [0.0,0.0,0.0]])

Q_inv = np.array([[0.0,0.0,0.0],
                  [0.0,0.0,0.0],
                  [0.0,0.0,0.0]])

A = np.array([[0.0,0.0,0.0],
              [0.0,0.0,0.0],
              [0.0,0.0,0.0]])

B = np.array([[0.0,0.0,0.0],
              [0.0,0.0,0.0],
              [0.0,0.0,0.0]])

D = np.array([[0.0,0.0,0.0],
              [0.0,0.0,0.0],
              [0.0,0.0,0.0]])

if(VYX!=0):
	Q[0][0] = EX/(1-(VXY*VYX))
	Q[1][1] = EY/(1-(VXY*VYX))
	Q[0][1] = (VXY*EY)/(1-(VXY*VYX))
	Q[1][0] = Q[0][1]
else:
	Q[0][0] = EX/(1-(VXY**2))
	Q[1][1] = EY/(1-(VXY**2))
	Q[0][1] = (VXY*EX)/(1-(VXY**2))
	Q[1][0] = Q[0][1]

Q[2][2] = GXY

print("\nQ is set up\n")
print(Q)

angles= [-m.pi/4,m.pi/4,m.pi/2,0,m.pi/2,0,0,m.pi/2,0,m.pi/2,m.pi/4,-m.pi/4]
counter=0

np.set_printoptions(precision=4, suppress=True)
t_k = 0.005
h_k = [i*t_k for i in xrange(-(len(angles)+1)/2+1,(len(angles)+1)/2+1)]
#h_k = h_k+ [(i*t_k for i in xrange(0,]
h_k_1 = [i-t_k for i in h_k if (i!=0)]
z_k = [(i+j)/2 for i,j in zip(h_k, h_k_1)]

print '\nThis is h_k\n'
pp(h_k)

print '\nThis is h_k_1\n'
pp(h_k_1)

print '\nThis is z_k\n'
pp(z_k)
# for al in angles: #loop begins
# 
# 	counter=counter+1
# 
# 	Q_inv[0][0] = Q[0][0]*pow(m.cos(al),4) + 2*(Q[0][1] + 2*Q[2][2])*pow(m.cos(al),2)*pow(m.sin(al),2) + Q[1][1]*pow(m.sin(al),4)
# 
# 	Q_inv[0][1] = (Q[0][0] + Q[1][1] - 4*Q[2][2])*pow(m.cos(al),2)*pow(m.sin(al),2) + Q[0][1]*(pow(m.cos(al),4) + pow(m.sin(al),4))
# 
# 	Q_inv[1][1] = Q[0][0]*pow(m.sin(al),4) + 2*(Q[0][1] + 2*Q[2][2])*pow(m.cos(al),2)*pow(m.sin(al),2) + Q[1][1]*pow(m.cos(al),4)
# 
# 	Q_inv[0][2] = (Q[0][0] - Q[0][1] - 2*Q[2][2])*pow(m.cos(al),3)*m.sin(al) + (Q[0][1] - Q[1][1] + 2*Q[2][2])*m.cos(al)*pow(m.sin(al),3)
# 
# 	Q_inv[1][2] = (Q[0][0] - Q[0][1] - 2*Q[2][2])*pow(m.sin(al),3)*m.cos(al) + (Q[0][1] - Q[1][1] + 2*Q[2][2])*m.sin(al)*pow(m.cos(al),3)
# 
# 	Q_inv[2][2] = (Q[0][0] + Q[1][1] - 2*Q[0][1] - 2*Q[2][2])*pow(m.sin(al),2)*pow(m.cos(al),2)+ Q[2][2]*(pow(m.cos(al),4)+pow(m.sin(al),4))
# 
# 	Q_inv[1][0] = Q_inv[0][1]
# 
# 	for i,j in zip([1,0,0,1,0,1,2],[0,0,1,1,2,2,2]): #2nd loop begins
# 
# 		A[i][j]= A[i][j]+  Q_inv[i][j]*0.005
# 		D[i][j]= D[i][j] + Q_inv[i][j]*(pow(0.005,3)/12 + (0.005)*pow(0.0025,2))
# 		if(counter<7):
# 			B[i][j]= B[i][j] + Q_inv[i][j]
# 		else:
# 			B[i][j]= B[i][j] - Q_inv[i][j]
# 	#second loops ends
# 
# #loop ends
# print '\nQ_inv for each iteration should not be printed (Cause there are 12).\nBut it has been been computed.'
# 
# np.set_printoptions(precision=4, suppress=True)
# print '\nA:\n'
# print(A)
# 
# print '\nB:\n'
# print(B)
# 
# np.set_printoptions(precision=4, suppress=False)
# print '\nD:\n'
# print(D) 
# print '\n'
