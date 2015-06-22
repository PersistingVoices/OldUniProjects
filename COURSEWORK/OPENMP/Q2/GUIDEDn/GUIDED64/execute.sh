#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/GUIDED64 GUIDED64.c -O3 -lm 
cd OUT/
cp ompbatch.pbs GUIDED64.pbs
#qsub -q short GUIDED64.pbs
cd ..
