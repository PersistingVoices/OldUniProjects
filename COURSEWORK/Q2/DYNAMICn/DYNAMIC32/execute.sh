#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/DYNAMIC32 DYNAMIC32.c -O3 -lm 
cd OUT/
cp ompbatch.pbs DYNAMIC32.pbs
qsub -q short DYNAMIC32.pbs
cd ..

