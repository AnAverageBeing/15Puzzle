#!/bin/bash

# Set the output directory
OUTPUT_DIR="bin"

# Source files
SRC_DIR="src"
SRC_FILES=(
    "${SRC_DIR}/15_puzzle.c"
    "${SRC_DIR}/main.c"
)

# Create the output directory if it doesn't exist
mkdir -p "${OUTPUT_DIR}"

# Compile the source files and link dynamically to raylib
gcc ${SRC_FILES[*]} -o "${OUTPUT_DIR}/15_puzzle" -lraylib -lm

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Build successful. Executable created in ${OUTPUT_DIR}/15_puzzle"
else
    echo "Build failed."
fi
