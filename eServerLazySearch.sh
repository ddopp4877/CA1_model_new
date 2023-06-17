#!bin/bash

for ((i=1; i<=13; i++))
do
	bash eServerBuild.sh
	bash eServerRun.sh
	python3 lazySearch.py
done
