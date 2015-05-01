#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/STATIC8 STATIC8.c -O3 -lm 
cd OUT/
cp ompbatch.pbs STATIC8.pbs
qsub -q serial STATIC8.pbs
cd ..
