#! /bin/bash
cp ompbatch.pbs DYNAMIC32.pbs 
qsub -q long DYNAMIC32.pbs
#cp ompbatch.pbs Q32-Simple.pbs 
#qsub -q short Q32-Simple.pbs
 
