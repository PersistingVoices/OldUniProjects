#! /bin/bash

for i in 1 2 4 8 16 32 64; do
	cd DYNAMIC$i
	./execute.sh
	cd OUT/
	echo 'Gone to OUT/'
	#qsub -q short DYNAMIC$i.pbs 
	cd ..
	cd ..
done

