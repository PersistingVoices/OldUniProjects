#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/STATIC16 STATIC16.c -O3 -lm 
cd OUT/
cp ompbatch.pbs STATIC16.pbs
#qsub -q short STATIC16.pbs
cd ..
