#! /bin/bash 
#echo 'Copying into Pbs' 
#cp ompbatch.pbs GUIDED1.pbs
echo 'Send to queue' 
qsub -q short GUIDED16.pbs
echo 'done'

