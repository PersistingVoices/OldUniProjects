#! /bin/bash

for i in  2 4 8 16 32 64; do 
	#cp ompbatch.pbs GUIDED$i
	#cp GUIDED1.c GUIDED$i
	rm -R STATIC$i
	#cp execute.sh GUIDED$i
	echo 'removed'$i
done
 
