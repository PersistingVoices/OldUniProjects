#! /bin/bash
cp ompbatch.pbs AUTO.pbs 
qsub -q short AUTO.pbs
#cp ompbatch.pbs Q1-Simple.pbs 
#qsub -q short Q1-Simple.pbs
 
