#! /bin/bash 
#echo 'Copying into Pbs' 
#cp ompbatch.pbs STATIC1.pbs
echo 'Send to queue' 
qsub -q long STATIC.pbs
echo 'done'

