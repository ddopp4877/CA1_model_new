#!/bin/bash



if [ -d "output" ]; then
	echo "remove output"
	rm -rf output
	mkdir output
fi


time mpiexec -np 50 nrniv -mpi -python run_network.py
