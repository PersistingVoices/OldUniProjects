#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/GUIDED2 GUIDED2.c -O3 -lm 
cd OUT/
cp ompbatch.pbs GUIDED2.pbs
#qsub -q short GUIDED2.pbs
cd ..
