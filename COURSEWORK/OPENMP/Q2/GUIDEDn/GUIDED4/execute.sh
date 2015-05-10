#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/GUIDED4 GUIDED4.c -O3 -lm 
cd OUT/
cp ompbatch.pbs GUIDED4.pbs
#qsub -q short GUIDED4.pbs
cd ..
