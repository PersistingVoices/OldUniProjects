#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/STATIC64 STATIC64.c -O3 -lm 
cd OUT/
cp ompbatch.pbs STATIC64.pbs
qsub -q serial STATIC64.pbs
cd ..
