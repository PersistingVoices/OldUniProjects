#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/STATIC1 STATIC1.c -O3 -lm 
cd OUT/
cp ompbatch.pbs STATIC1.pbs
qsub -q serial STATIC1.pbs
cd ..
