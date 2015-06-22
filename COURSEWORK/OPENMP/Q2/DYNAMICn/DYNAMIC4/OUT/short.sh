#! /bin/bash
cp ompbatch.pbs DYNAMIC4.pbs 
qsub -q long DYNAMIC4.pbs
#cp ompbatch.pbs Q4-Simple.pbs 
#qsub -q short Q4-Simple.pbs
 
