#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/GUIDED1 GUIDED1.c -O3 -lm 
cd OUT/
cp ompbatch.pbs GUIDED1.pbs
#qsub -q short GUIDED1.pbs
cd ..
