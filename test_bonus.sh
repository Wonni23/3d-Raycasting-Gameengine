#!/bin/bash

	if [ ! -x "./cub3D_bonus" ]; then
		echo "Error: ./cub3D_bonus executable not found. Please compile it first."
		exit 1
	fi

	echo "Testing good maps:"
	for file in maps/good/*.cub; do
		echo "Running good map file: $file"
		./cub3D_bonus "$file"
		ret=$?
		if [ $ret -eq 0 ]; then
			echo "Success: $file ran successfully."
		else
			echo "Error: $file did not run as expected (exit code: $ret)."
		fi
		echo "---------------------------------------"
	done

	echo "Testing bad maps:"
	for file in maps/bad/*; do
		echo "Running bad map file: $file"
		./cub3D_bonus "$file"
		ret=$?
		if [ $ret -eq 0 ]; then
			echo "Unexpected success: $file should have failed."
		else
			echo "Correctly rejected: $file (exit code: $ret)."
		fi
		echo "---------------------------------------"
	done
