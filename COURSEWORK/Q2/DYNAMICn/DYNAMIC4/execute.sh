#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/DYNAMIC4 DYNAMIC4.c -O3 -lm 
cd OUT/
cp ompbatch.pbs DYNAMIC4.pbs
#qsub -q course4 DYNAMIC4.pbs
