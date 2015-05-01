#! /bin/bash
cp ompbatch.pbs DYNAMIC8.pbs 
qsub -q long DYNAMIC8.pbs
#cp ompbatch.pbs Q8-Simple.pbs 
#qsub -q short Q8-Simple.pbs
 
