#! /bin/bash 
#echo 'Copying into Pbs' 
#cp ompbatch.pbs STATIC4.pbs
echo 'Send to queue' 
qsub -q long STATIC8.pbs
echo 'done'

