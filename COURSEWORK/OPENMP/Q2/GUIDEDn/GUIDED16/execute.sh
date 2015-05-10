#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/GUIDED16 GUIDED16.c -O3 -lm 
cd OUT/
cp ompbatch.pbs GUIDED16.pbs
#qsub -q short GUIDED16.pbs
cd ..
