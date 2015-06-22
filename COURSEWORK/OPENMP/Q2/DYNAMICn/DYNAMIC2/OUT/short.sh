#! /bin/bash
cp ompbatch.pbs DYNAMIC2.pbs 
qsub -q long DYNAMIC2.pbs
#cp ompbatch.pbs Q2-Simple.pbs 
#qsub -q short Q2-Simple.pbs
 
