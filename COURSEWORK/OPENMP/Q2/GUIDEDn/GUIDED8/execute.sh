#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/GUIDED8 GUIDED8.c -O3 -lm 
cd OUT/
cp ompbatch.pbs GUIDED8.pbs
#qsub -q short GUIDED8.pbs
cd ..
