#!/bin/bash
cd "$(dirname "$0")/.."
echo "[INFO] Cleaning project..."

# Remove the generated directories if they exist
[ -d "build" ] && rm -rf build
[ -d "build_win" ] && rm -rf build_win
[ -d "bin" ] && rm -rf bin
[ -d "coverage" ] && rm -rf coverage
[ -d "deps" ] && rm -rf deps

echo "[SUCCESS] Workspace cleaned."
echo ""