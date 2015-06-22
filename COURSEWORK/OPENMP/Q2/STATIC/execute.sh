#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/STATIC STATIC.c -O3 -lm 
cd OUT/
cp ompbatch.pbs STATIC.pbs
#qsub -q short STATIC.pbs
cd ..
