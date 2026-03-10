#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

cd "$(dirname "$0")/.."

echo "[INFO] Starting Cross-Compilation for Windows..."

# Configure using the toolchain file and Ninja
cmake -S . -B build_win -G Ninja -DCMAKE_TOOLCHAIN_FILE=.jenkins/mingw-w64-toolchain.cmake -DBUILD_TESTING=OFF

# Build the targets
cmake --build build_win

echo "[SUCCESS] Windows binary created in the main /build_win/bin folder!"