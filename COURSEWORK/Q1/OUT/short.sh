#! /bin/bash
cp ompbatch.pbs Q1-Paralell.pbs 
qsub -q short Q1-Paralell.pbs
cp ompbatch.pbs Q1-Simple.pbs 
qsub -q short Q1-Simple.pbs
 
