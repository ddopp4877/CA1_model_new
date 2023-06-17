#!/bin/bash
echo "running"
echo "running" | sendmail dpd4k4@umsystem.edu

mpirun -np 60 nrniv -mpi -python run_network.py > out.txt &>/dev/null &

echo "Ca1 is done in $(($SECONDS/60)) minutes and $(($SECONDS - $SECONDS/60 *60)) seconds" | sendmail dpd4k4@umsystem.edu
