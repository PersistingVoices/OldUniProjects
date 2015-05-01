#! /bin/bash

for i in  2 4 8 16 32 64; do 
	#cp ompbatch.pbs GUIDED$i
	#cp GUIDED1.c GUIDED$i
	#cp GUIDED1/execute.sh GUIDED$i/
	cp long.sh GUIDED$i/OUT/
	echo 'copied both to $i'
done
 
