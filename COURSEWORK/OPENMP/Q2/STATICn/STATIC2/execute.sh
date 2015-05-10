#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/STATIC2 STATIC2.c -O3 -lm 
cd OUT/
cp ompbatch.pbs STATIC2.pbs
#qsub -q short STATIC2.pbs
cd ..
