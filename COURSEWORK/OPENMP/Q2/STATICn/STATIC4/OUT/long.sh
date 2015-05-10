#! /bin/bash 
#echo 'Copying into Pbs' 
#cp ompbatch.pbs STATIC4.pbs
echo 'Send to queue' 
qsub -q long STATIC4.pbs
echo 'done'

