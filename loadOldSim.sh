#!/bin/bash

echo "choose folder with sim data: "
read folderName
echo "deleting folder biophys_components"
rm -rf "biophys_components"
cp -r "CA1Results/$folderName/biophys_components" .
cp "CA1Results/$folderName/simulation_configLFP.json" .
