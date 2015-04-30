#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/DYNAMIC2 DYNAMIC8.c -O3 -lm 
cd OUT/
cp ompbatch.pbs DYNAMIC8.pbs
qsub -q short DYNAMIC8.pbs
cd ..
