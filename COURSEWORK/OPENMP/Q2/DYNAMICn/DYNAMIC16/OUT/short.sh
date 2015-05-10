#! /bin/bash
cp ompbatch.pbs DYNAMIC16.pbs 
qsub -q long DYNAMIC16.pbs
#cp ompbatch.pbs Q16-Simple.pbs 
#qsub -q short Q16-Simple.pbs
 
