#! /bin/bash
for i in 1 2 4 8 16 32 64; do 
	cd GUIDED$i/OUT 
	rm G*
	cd Plots/ && rm *.*
	cd ../Data && rm *.*
	cd ../..
done 
