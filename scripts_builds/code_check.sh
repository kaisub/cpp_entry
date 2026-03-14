#!/bin/bash

# Exit immediately if any command exits with a non-zero status
set -e

cd "$(dirname "$0")/.."

# Handle manual clean flag
if [ "$1" == "--clean" ]; then
    echo "[INFO] Flag --clean detected. Running clean script..."
    ./scripts_builds/clean.sh
    echo ""
fi

echo "[INFO] Configuring Project for Static Analysis..."
# Generate compile_commands.json using the Ninja generator
cmake -S . -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

echo "[INFO] Running Cppcheck..."
# Run Cppcheck directly to mirror Jenkins CI behavior exactly
# Ignores tests, uses the suppressions list from .jenkins, and fails on error
cppcheck --project=build/compile_commands.json \
    -i tests \
    -i build \
    --enable=all \
    --inconclusive \
    --suppressions-list=.jenkins/cppcheck_suppressions.txt \
    --error-exitcode=1

echo "[INFO] Running Clang-Tidy..."
# Run Clang-Tidy via CMake target
cmake --build build --target run_tidy

echo "[SUCCESS] Static Analysis completed without issues!"