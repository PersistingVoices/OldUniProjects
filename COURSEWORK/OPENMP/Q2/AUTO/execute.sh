#! /bin/bash
export OMP_NUM_THREADS=6
cc -o OUT/AUTO AUTO.c -O3 -lm 
cd OUT/
cp ompbatch.pbs AUTO.pbs
#qsub -q course1 AUTO.pbs
