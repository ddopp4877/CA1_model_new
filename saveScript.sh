#!/bin/bash

echo "enter folder name"
read foldername

read -r -p "enter a description of the data:  " input_string


targetFolder="CA1Results/$foldername"

mkdir "$targetFolder"

touch "$targetFolder/README.txt"
echo "$input_string">"$targetFolder/README.txt"

cp -r "output" $targetFolder
cp -r "network" $targetFolder
cp -r "biophys_components" $targetFolder
cp "simulation_configLFP.json" $targetFolder

