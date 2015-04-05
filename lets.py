import numpy as np
import sys
import math as m


# EX= int(raw_input('Enter EX: '))
EX = 20010000.0
# EY= int(raw_input('Enter EY: '))
EY = 1301000.0
# GXY= int(raw_input('Enter GXY: '))
GXY = 1001000.0
# VXY= float(raw_input('Enter VXY: '))
VXY = 0.3
# VYX= float(raw_input('Enter VYX (enter 0 if only VXY): '))
VYX = 0.02

Q = np.array([[0.0,0.0,0.0],[0.0,0.0,0.0],[0.0,0.0,0.0]])
Q_inv = np.array([[0.0,0.0,0.0],[0.0,0.0,0.0],[0.0,0.0,0.0]])

Q_MAJ = list()
A = np.array([[0.0,0.0,0.0],[0.0,0.0,0.0],[0.0,0.0,0.0]])
B = np.array([[0.0,0.0,0.0],[0.0,0.0,0.0],[0.0,0.0,0.0]])
D = np.array([[0.0,0.0,0.0],[0.0,0.0,0.0],[0.0,0.0,0.0]])

if(VYX!=0):
	Q[0][0] = EX/(1-(VXY*VYX))
	Q[1][1] = EY/(1-(VXY*VYX))
	Q[0][1] = (VXY*EY)/(1-(VXY*VYX))
	Q[1][0] = Q[0][1]
else:
	Q[0][0] = EX/(1-(VXY^2))
	Q[1][1] = EY/(1-(VXY^2))
	Q[0][1] = (VXY*E1)/(1-(VXY^2))
	Q[1][0] = Q[0][1]

Q[2][2] = GXY
print("Q is now set up")
print(Q)
angles= [-m.pi/4,m.pi/4,m.pi/2,0,m.pi/2,0,0,m.pi/2,0,m.pi/2,m.pi/4,-m.pi/4]
counter=0
Br = list()
for al in angles:
	counter=counter+1
	# print counter
	Q_inv[0][0] = Q[0][0]*pow(m.cos(al),4) + 2*(Q[0][1] + 2*Q[2][2])*pow(m.cos(al),2)*pow(m.sin(al),2) + Q[1][1]*pow(m.sin(al),4)

	Q_inv[0][1] = (Q[0][0] + Q[1][1] - 4*Q[2][2])*pow(m.cos(al),2)*pow(m.sin(al),2) + Q[0][1]*(pow(m.cos(al),4) + pow(m.sin(al),4))

	Q_inv[1][1] = Q[0][0]*pow(m.sin(al),4) + 2*(Q[0][1] + 2*Q[2][2])*pow(m.cos(al),2)*pow(m.sin(al),2) + Q[1][1]*pow(m.cos(al),4)

	Q_inv[0][2] = (Q[0][0] - Q[0][1] - 2*Q[2][2])*pow(m.cos(al),3)*m.sin(al) + (Q[0][1] - Q[1][1] + 2*Q[2][2])*m.cos(al)*pow(m.sin(al),3)

	Q_inv[1][2] = (Q[0][0] - Q[0][1] - 2*Q[2][2])*pow(m.sin(al),3)*m.cos(al) + (Q[0][1] - Q[1][1] + 2*Q[2][2])*m.sin(al)*pow(m.cos(al),3)

	Q_inv[2][2] = (Q[0][0] + Q[1][1] - 2*Q[0][1] - 2*Q[2][2])*pow(m.sin(al),2)*pow(m.cos(al),2)+ Q[2][2]*(pow(m.cos(al),4)+pow(m.sin(al),4))

	Q_inv[1][0] = Q_inv[0][1]


	# print '\nQ_inv is now set up, and for al=',al,'it is:\n' 
	# print(Q_inv)

	for i,j in zip([1,0,0,1,0,1,2],[0,0,1,1,2,2,2]):
		A[i][j]= A[i][j]+  Q_inv[i][j]*0.005
		D[i][j]= D[i][j] + Q_inv[i][j]*(pow(0.005,3)/12 + (0.005)*pow(0.0025,2))
		if(counter<7):
			B[i][j]= B[i][j] + Q_inv[i][j]
		else:
			B[i][j]= B[i][j] - Q_inv[i][j]
		# print 'B:', B ,'\n'
	# Br.append(B[0][0])

	# 	print '\nA[',i,'][',j,']','=','A[',i,'][',j,'] +', 'Q_inv[',i,'][',j,']'
	# print '\nA for ply',al,'is set up\n'
	# print A ,'\n'
			
	# raw_input()
# print 'Br: \n'
# print Br
np.set_printoptions(precision=4, suppress=True)
print 'A:\n'
print(A)

print 'B:\n'
print(B)

np.set_printoptions(precision=4, suppress=False)
print 'D:\n'
print(D)
