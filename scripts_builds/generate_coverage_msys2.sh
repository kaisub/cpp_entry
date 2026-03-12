#!/bin/bash

# Stop script execution on any error
set -e

# Navigate to the project root
cd "$(dirname "$0")/.."

echo "[INFO] Configuring Project for Coverage Analysis..."
echo "[INFO] Requires build_run_uts.sh to be run first to generate .gcda files."
echo ""

# Create coverage output directory if it doesn't exist
mkdir -p coverage

# Generate HTML report using python module gcovr
echo "[INFO] Generating HTML report with gcovr..."

# Using 'python -m gcovr' and explicitly pointing to UCRT64 gcov.
# Added --exclude-lines-by-pattern to ignore C++ destructors ('~') which cause
# "ghost lines" in GCC coverage metrics due to D0/D1/D2 compiler generation.
/ucrt64/bin/python.exe -m gcovr \
    --decisions \
    -r . \
    --gcov-executable /ucrt64/bin/gcov.exe \
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

WIN_PATH=$(cygpath -w -a coverage/index.html)

echo "[SUCCESS] Coverage report generated in: $WIN_PATH"

# Convert POSIX path to Windows path for explorer
explorer.exe $WIN_PATH