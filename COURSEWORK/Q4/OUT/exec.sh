echo 'Copying into pbs'
cp ompbatch.pbs FL.pbs
echo 'submitting to queue'
qsub -q short FL.pbs
qstat -u ss6g11

