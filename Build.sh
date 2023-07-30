#!/bin/bash

OUTPUT_DIR="bin"

SRC_DIR="src"
SRC_FILES=(
    "${SRC_DIR}/15_puzzle.c"
    "${SRC_DIR}/main.c"
)

mkdir -p "${OUTPUT_DIR}"

gcc ${SRC_FILES[*]} -o "${OUTPUT_DIR}/15_puzzle" -lraylib -lm

if [ $? -eq 0 ]; then
    echo "Build successful. Executable created in ${OUTPUT_DIR}/15_puzzle"
else
    echo "Build failed."
fi
