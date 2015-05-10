#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/DYNAMIC16 DYNAMIC16.c -O3 -lm 
cd OUT/
cp ompbatch.pbs DYNAMIC16.pbs
#qsub -q course16 DYNAMIC16.pbs
