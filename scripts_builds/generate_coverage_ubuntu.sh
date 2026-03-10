#!/bin/bash
cd "$(dirname "$0")/.."

echo "[INFO] Configuring Project for Coverage Analysis..."
echo "Requires build_run_uts.sh to be run first to generate .gcda files."

echo "[INFO] Generating HTML report with gcovr..."
mkdir -p coverage

# Generate report based on existing .gcda files in the build directory
gcovr -r . --filter src/ --filter inc/ --object-directory build/ --html --html-details -o coverage/index.html

if [ $? -eq 0 ]; then
    echo "[SUCCESS] Coverage report generated in: coverage/index.html"
else
    echo "[ERROR] gcovr failed to generate report. Did you run the tests first?"
    exit 1
fi