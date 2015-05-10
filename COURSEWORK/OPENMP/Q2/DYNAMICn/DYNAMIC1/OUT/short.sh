#! /bin/bash
cp ompbatch.pbs DYNAMIC1.pbs 
qsub -q long DYNAMIC1.pbs
#cp ompbatch.pbs Q1-Simple.pbs 
#qsub -q short Q1-Simple.pbs
 
