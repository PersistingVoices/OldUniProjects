#! /bin/bash 
#echo 'Copying into Pbs' 
#cp ompbatch.pbs STATIC32.pbs
echo 'Send to queue' 
qsub -q long STATIC32.pbs
echo 'done'

