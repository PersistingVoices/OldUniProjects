#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/DYNAMIC2 DYNAMIC16.c -O3 -lm 
cd OUT/
cp ompbatch.pbs DYNAMIC16.pbs
qsub -q short DYNAMIC16.pbs
cd ..
