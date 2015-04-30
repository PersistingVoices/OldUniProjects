#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/DYNAMIC64 DYNAMIC64.c -O3 -lm 
cd OUT/
cp ompbatch.pbs DYNAMIC64.pbs
qsub -q short DYNAMIC64.pbs
cd ..
