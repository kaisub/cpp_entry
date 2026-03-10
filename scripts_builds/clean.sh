#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Navigate to the project root directory
cd "$(dirname "$0")/.."

echo "[INFO] ================================================="
echo "[INFO] Running Clean (Preserving dependencies)..."
echo "[INFO] ================================================="
echo ""

# Function to clean a specific build directory while keeping _deps
smart_clean_dir() {
    local DIR_NAME=$1
    if [ -d "$DIR_NAME" ]; then
        echo "[INFO] Cleaning '$DIR_NAME' directory..."
        # Find all items directly inside the directory, exclude '_deps', and remove them
        find "$DIR_NAME" -mindepth 1 -maxdepth 1 ! -name '_deps' -exec rm -rf {} +
        echo "[INFO] '$DIR_NAME' cleaned. Downloaded dependencies in '_deps' are safe."
    else
        echo "[INFO] Directory '$DIR_NAME' does not exist. Skipping."
    fi
}

# Clean standard Linux build directory
smart_clean_dir "build"

# Clean Windows cross-compilation build directory
smart_clean_dir "build_win"

# Remove the generated directories if they exist
[ -d "coverage" ] && rm -rf coverage

echo ""
echo "[SUCCESS] Clean completed!"