#! /bin/bash

for i in  2 4 8 16 32 64; do 
	cp -R OUT/ STATIC$i
	#cp STATIC1.c STATIC$i
	#cp execute.sh STATIC$i
	echo 'made'$i
done
 
