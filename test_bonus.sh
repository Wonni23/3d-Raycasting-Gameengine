#!/bin/bash
	GREEN='\033[0;32m'
	RED='\033[0;31m'
	NC='\033[0m' # No Color (reset)

	# Check if the cub3D executable exists and is executable.
	if [ ! -x "./cub3D_bonus" ]; then
		echo -e "${RED}Error: ./cub3D_bonus executable not found. Please compile it first.${NC}"
		exit 1
	fi

	echo -e "${GREEN}Testing good maps:${NC}"
	# Loop over all .cub files in the maps/good directory.
	for file in maps/good/*.cub; do
		echo -e "${GREEN}Running good map file: $file${NC}"
		valgrind --leak-check=full --show-leak-kinds=all ./cub3D_bonus "$file"
		ret=$?
		if [ $ret -eq 0 ]; then
			echo -e "${GREEN}Success: $file ran successfully without memory errors.${NC}"
		else
			echo -e "${RED}Error: $file did not run as expected (exit code: $ret).${NC}"
		fi
		echo -e "${GREEN}---------------------------------------${NC}"
	done

	echo -e "${GREEN}Testing bad maps:${NC}"
	# Loop over all .cub files in the maps/bad directory.
	for file in maps/bad/*; do
		echo -e "${GREEN}Running bad map file: $file${NC}"
		valgrind --leak-check=full --show-leak-kinds=all ./cub3D_bonus "$file"
		ret=$?
		if [ $ret -eq 0 ]; then
			echo -e "${RED}Unexpected success: $file should have failed, but it ran successfully without memory errors.${NC}"
		else
			echo -e "${GREEN}Correctly rejected: $file (exit code: $ret).${NC}"
		fi
		echo -e "${GREEN}---------------------------------------${NC}"
	done
