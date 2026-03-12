#!/bin/bash

# Stop script execution on any error
set -e

# Navigate to the project root
cd "$(dirname "$0")/.."

echo "[INFO] Configuring Project for Coverage Analysis..."
echo "[INFO] Requires build_run_uts.sh to be run first to generate .gcda files."

echo "[INFO] Generating HTML report with gcovr..."
mkdir -p coverage

# Ulepszone wywołanie gcovr (zsynchronizowane z MSYS2)
gcovr \
    --decisions \
    -r . \
    --filter src/ \
    --filter inc/ \
    --object-directory build/ \
    --exclude-throw-branches \
    --exclude-unreachable-branches \
    --exclude-lines-by-pattern '.*~.*' \
    --exclude-branches-by-pattern '.*(make_unique|make_shared|new |std::format).*' \
    --exclude-noncode-lines \
    --html --html-details \
    -o coverage/index.html

echo "[SUCCESS] Coverage report generated in: coverage/index.html"