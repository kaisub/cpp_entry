#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

cd "$(dirname "$0")/.."

if [ "$1" == "--clean" ]; then
    echo "[INFO] Cleaning old build directory..."
    [ -f "./scripts_builds/clean.sh" ] && source "./scripts_builds/clean.sh"
fi

echo "[INFO] Starting full build (Application + Tests)..."

# Configure using Ninja generator to prevent cache collisions
cmake -S . -B build -G Ninja -DBUILD_TESTING=ON
cmake --build build --config Debug

echo "[SUCCESS] Build completed successfully!"