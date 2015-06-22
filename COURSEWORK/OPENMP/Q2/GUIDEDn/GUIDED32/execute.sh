#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/GUIDED32 GUIDED32.c -O3 -lm 
cd OUT/
cp ompbatch.pbs GUIDED32.pbs
#qsub -q short GUIDED32.pbs
cd ..
