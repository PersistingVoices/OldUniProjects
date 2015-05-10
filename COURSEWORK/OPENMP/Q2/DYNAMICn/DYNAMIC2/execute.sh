#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/DYNAMIC2 DYNAMIC2.c -O3 -lm 
cd OUT/
cp ompbatch.pbs DYNAMIC2.pbs
#qsub -q course2 DYNAMIC2.pbs
