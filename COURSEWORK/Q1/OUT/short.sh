#! /bin/bash
cp ompbatch.pbs Q1-Paralell.pbs 
qsub -q long Q1-Paralell.pbs
cp ompbatch.pbs Q1-Simple.pbs 
qsub -q long Q1-Simple.pbs
 
