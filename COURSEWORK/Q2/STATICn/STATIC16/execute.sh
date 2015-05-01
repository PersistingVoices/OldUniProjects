#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/STATIC16 STATIC16.c -O3 -lm 
cd OUT/
cp ompbatch.pbs STATIC16.pbs
qsub -q serial STATIC16.pbs
cd ..
