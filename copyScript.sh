#!bin/bash

source_folder="/home/dpd4k4/CA1_model/"
destination_folder="/home/shared/CA1_model/"
excluded_folders=("CA1Results","CA1_model_env",".ipynb_checkpoints")

exclude_options=""
for folder in "${excluded_folders[@]}"; do
	exclude_options+="--exclude='$folder' "
done

rsync -av --progress $exclude_options "$source_folder/" "$destination_folder/"



