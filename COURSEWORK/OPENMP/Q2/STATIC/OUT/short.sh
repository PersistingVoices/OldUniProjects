#! /bin/bash
cp ompbatch.pbs STATIC.pbs 
qsub -q short STATIC.pbs
#cp ompbatch.pbs Q1-Simple.pbs 
#qsub -q short Q1-Simple.pbs
 
