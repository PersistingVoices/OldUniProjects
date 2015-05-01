#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/STATIC32 STATIC32.c -O3 -lm 
cd OUT/
cp ompbatch.pbs STATIC32.pbs
qsub -q serial STATIC32.pbs
cd ..
