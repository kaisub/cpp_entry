#!/bin/bash
set -e

# Navigate to project root
cd "$(dirname "$0")/.."

echo "[INFO] ================================================="
echo "[INFO] Running DEEP Clean (Preserving downloaded source)..."
echo "[INFO] ================================================="
echo ""

deep_clean() {
    local TGT=$1
    if [ -d "$TGT" ]; then
        echo "[INFO] Cleaning '$TGT'..."
        
        # 1. Delete everything EXCEPT _deps
        find "$TGT" -mindepth 1 -maxdepth 1 ! -name '_deps' -exec rm -rf {} +
        
        # 2. CRITICAL: Go INSIDE _deps and delete subbuilds/builds (the generator conflict source)
        if [ -d "$TGT/_deps" ]; then
            find "$TGT/_deps" -mindepth 1 -maxdepth 1 -type d \( -name "*-subbuild" -o -name "*-build" \) -exec rm -rf {} +
        fi
        
        echo "[INFO] '$TGT' cleaned. Downloaded source in _deps is safe."
    fi
}

deep_clean "build"
deep_clean "build_win"

echo ""
echo "[SUCCESS] Deep Clean completed!"