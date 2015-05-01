#! /bin/bash 
#echo 'Copying into Pbs' 
#cp ompbatch.pbs STATIC64.pbs
echo 'Send to queue' 
qsub -q long STATIC64.pbs
echo 'done'

