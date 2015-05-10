#! /bin/bash
cp ompbatch.pbs DYNAMIC64.pbs 
qsub -q long DYNAMIC64.pbs
#cp ompbatch.pbs Q64-Simple.pbs 
#qsub -q short Q64-Simple.pbs
 
