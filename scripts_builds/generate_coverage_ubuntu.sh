#!/bin/bash

# Stop script execution on any error
set -e

# Navigate to the project root
cd "$(dirname "$0")/.."

echo "[INFO] Configuring Project for Coverage Analysis..."
echo "[INFO] Requires build_run_uts.sh to be run first to generate .gcda files."

echo "[INFO] Generating HTML report with gcovr..."
mkdir -p coverage

# Expanded branch exclusion pattern to filter out STL allocator/stream AST branches.
gcovr \
    --decisions \
    -r . \
    --filter src/ \
    --filter inc/ \
    --object-directory build/ \
    --exclude-throw-branches \
    --exclude-unreachable-branches \
    --exclude-lines-by-pattern '.*~.*' \
    --exclude-branches-by-pattern '.*(make_unique|make_shared|new |std::format|cout|data_buffer|std::string|std::vector).*' \
    --exclude-function '.*(_GLOBAL__sub_I_|_static_initialization_and_destruction_0).*' \
    --exclude-noncode-lines \
    --html --html-details \
    -o coverage/index.html

echo "[SUCCESS] Coverage report generated in: coverage/index.html"