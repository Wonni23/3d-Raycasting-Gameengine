#!/bin/bash
	# Check if the cub3D executable exists and is executable.
	if [ ! -x "./cub3D" ]; then
		echo "Error: ./cub3D executable not found. Please compile it first."
		exit 1
	fi
	echo "Testing good maps:"
	# Loop over all .cub files in the maps/good directory.
	for file in maps/good/*.cub; do
		echo "Running good map file: $file"
		valgrind --leak-check=full --show-leak-kinds=all ./cub3D "$file"
		ret=$?
		if [ $ret -eq 0 ]; then
			echo "Success: $file ran successfully without memory errors."
		else
			echo "Error: $file did not run as expected (exit code: $ret)."
		fi
		echo "---------------------------------------"
	done
	echo "Testing bad maps:"
	# Loop over all .cub files in the maps/bad directory.
	for file in maps/bad/*; do
		echo "Running bad map file: $file"
		valgrind --leak-check=full --show-leak-kinds=all ./cub3D "$file"
		ret=$?
		if [ $ret -eq 0 ]; then
			echo "Unexpected success: $file should have failed, but it ran successfully without memory errors."
		else
			echo "Correctly rejected: $file (exit code: $ret)."
		fi
		echo "---------------------------------------"
	done