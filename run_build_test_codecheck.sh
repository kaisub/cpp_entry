#!/bin/bash

# Zatrzymuje skrypt natychmiast, jeśli jakiekolwiek polecenie zwróci błąd
set -e

# Przejście do katalogu głównego projektu
cd "$(dirname "$0")"

echo "[INFO] ================================================="
echo "[INFO] Starting Local CI Pipeline (Linux/Bash)..."
echo "[INFO] ================================================="
echo ""

# --- Step 1: Build and Tests ---
echo "[INFO] Step 1: Building and running unit tests (--clean)"
# Assuming the script handles --clean
./scripts_builds/build_run_uts.sh --clean

echo ""
echo "[INFO] ================================================="
# --- Step 2: Static Analysis ---
echo "[INFO] Step 2: Running Static Analysis (Cppcheck & Clang-Tidy)"
./scripts_builds/code_check.sh

echo ""
echo "[INFO] ================================================="
echo "[SUCCESS] All pipeline steps completed successfully!"
echo "[INFO] ================================================="