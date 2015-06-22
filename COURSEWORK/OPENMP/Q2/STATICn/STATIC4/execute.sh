#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/STATIC4 STATIC4.c -O3 -lm 
cd OUT/
cp ompbatch.pbs STATIC4.pbs
#qsub -q short STATIC4.pbs
cd ..
