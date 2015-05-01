#! /bin/bash

for i in 1 2 4 8 16 32 64; do 
	#cp -R OUT/ STATIC$i
	#cp -R STATIC1 STATIC$i
	#cp execute.sh STATIC$i
	cp ompbatch.pbs STATIC$i/OUT
	echo 'made'$i
done
 
