#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/DYNAMIC1 DYNAMIC1.c -O3 -lm 
cd OUT/
cp ompbatch.pbs DYNAMIC1.pbs
#qsub -q course1 DYNAMIC1.pbs
