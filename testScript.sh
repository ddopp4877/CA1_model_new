#!bin/bash

echo "running"

for ((i=0;i<15000000;i++))
do
	i=$(($i+ 10))
done

echo "done in $(($SECONDS/60)) minutes and $(($SECONDS - $SECONDS/60 *60)) seconds" | mail dpd4k4@umsystem.edu
