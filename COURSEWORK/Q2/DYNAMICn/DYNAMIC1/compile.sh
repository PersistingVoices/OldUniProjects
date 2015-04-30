#! /bin/bash
#export OMP_NUM_THREADS=6
ADDR1 = "/work/y14/y14/ss6g11/OMP-exercises/C/C-and-Cython/COURSEWORK/Q2/DYNAMICn/DYNAMIC1"
ADDR2 = "/work/y14/y14/ss6g11/OMP-exercises/C/C-and-Cython/COURSEWORK/Q2/DYNAMICn/DYNAMIC2"
ADDR4 = "/work/y14/y14/ss6g11/OMP-exercises/C/C-and-Cython/COURSEWORK/Q2/DYNAMICn/DYNAMIC4"
ADDR8 = "/work/y14/y14/ss6g11/OMP-exercises/C/C-and-Cython/COURSEWORK/Q2/DYNAMICn/DYNAMIC8"
ADDR16 = "/work/y14/y14/ss6g11/OMP-exercises/C/C-and-Cython/COURSEWORK/Q2/DYNAMICn/DYNAMIC16"
ADDR32 = "/work/y14/y14/ss6g11/OMP-exercises/C/C-and-Cython/COURSEWORK/Q2/DYNAMICn/DYNAMIC32"
ADDR64 = "/work/y14/y14/ss6g11/OMP-exercises/C/C-and-Cython/COURSEWORK/Q2/DYNAMICn/DYNAMIC64"

for i in 1 2 4 8 16 32 64; do  
	cd ADDR$i
	pwd
done
#cp ompbatch.pbs DYNAMIC1.pbs
#qsub -q course1 DYNAMIC1.pbs


