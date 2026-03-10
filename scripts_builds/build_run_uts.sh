#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Navigate to the project root directory
cd "$(dirname "$0")/.."

# 1. Handle Clean Flag
if [ "$1" == "--clean" ]; then
    echo "[INFO] Flag --clean detected. Running clean script..."
    [ -f "./scripts_builds/clean.sh" ] && source "./scripts_builds/clean.sh"
    echo ""
fi

echo "[INFO] Configuring Project (App + Tests)..."
# Using Ninja to prevent generator conflicts with code_check.sh
cmake -S . -B build -G Ninja -DBUILD_TESTING=ON
echo ""

echo "[INFO] Building All Targets..."
cmake --build build --config Debug
echo ""

echo "[INFO] Running Unit Tests..."
# Running the binary
./build/bin/unit_tests
echo ""