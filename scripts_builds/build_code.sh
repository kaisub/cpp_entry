#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Navigate to the project root directory
cd "$(dirname "$0")/.."

# 1. Handle Clean Flag
if [ "$1" == "--clean" ]; then
    echo "[INFO] Flag --clean detected. Running clean script..."
    [ -f "./scripts_builds/clean.sh" ] && source "./scripts_builds/clean.sh"
fi

echo "[INFO] Starting build (Application only)..."

# 1. Configuration with Testing DISABLED using Ninja generator
cmake -S . -B build -G Ninja -DBUILD_TESTING=OFF

# 2. Building targets
cmake --build build --config Debug

echo "[SUCCESS] Build finished! Binaries are in the /build/bin folder."