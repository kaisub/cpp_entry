#!/bin/bash

# Navigate to the project root
cd "$(dirname "$0")/.."

echo "[INFO] Configuring Project for Coverage Analysis..."
echo "[INFO] Requires build_run_uts.sh to be run first to generate .gcda files."
echo ""

# Create coverage output directory if it doesn't exist
mkdir -p coverage

# Generate HTML report using python module gcovr
echo "[INFO] Generating HTML report with gcovr..."

# Using 'python -m gcovr' and explicitly pointing to UCRT64 gcov
/ucrt64/bin/python.exe -m gcovr \
    -r . \
    --gcov-executable /ucrt64/bin/gcov.exe \
    --filter src/ \
    --filter inc/ \
    --object-directory build/ \
    --html --html-details \
    -o coverage/index.html

if [ $? -eq 0 ]; then
    echo "[SUCCESS] Coverage report generated in: coverage/index.html"
    # Convert POSIX path to Windows path for explorer
    explorer.exe $(cygpath -w coverage/index.html)
else
    echo "[ERROR] gcovr failed to generate report. Did you run the tests first?"
    exit 1
fi