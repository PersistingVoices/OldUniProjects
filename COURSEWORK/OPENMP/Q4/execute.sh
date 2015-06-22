#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/FL FL.c -O3 -lm 
cd OUT/
cp ompbatch.pbs FL.pbs
#qsub -q short FL.pbs
cd ..
