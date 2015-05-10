#! /bin/bash 
#echo 'Copying into Pbs' 
#cp ompbatch.pbs STATIC2.pbs
echo 'Send to queue' 
qsub -q long STATIC2.pbs
echo 'done'

