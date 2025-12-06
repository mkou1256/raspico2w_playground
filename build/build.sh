#!/bin/bash

set -e

INFO()  { echo -e "\e[36m[INFO]\e[0m  $1"; }
WARN()  { echo -e "\e[33m[WARN]\e[0m  $1"; }
ERROR() { echo -e "\e[31m[ERROR]\e[0m $1"; }
START() {
    echo ""
    echo "========================================================"
    echo ">> START: $1"
    echo "========================================================"
}
DONE() {
    echo "<< DONE:  $1"
    echo "--------------------------------------------------------"
    echo ""
}

BUILD_DIR="$(cd "$(dirname "$0")" && pwd)"
OUT_DIR="$BUILD_DIR/out"
PROJECT_ROOT_DIR="$BUILD_DIR/.."

if [ -d "$OUT_DIR" ]; then
    INFO "Clean up old out directory..."
    rm -rf "$OUT_DIR"
fi
mkdir -p "$OUT_DIR"
cd "$OUT_DIR"
INFO "output dir: $OUT_DIR"

SDK_PATH="$PROJECT_ROOT_DIR/pico-sdk"
BOARD_TYPE="pico2_w"
INFO "set PICO_SDK_PATH: $SDK_PATH"
INFO "set PICO_BOARD   : $BOARD_TYPE"

START "Running CMake configuration"
cmake -DPICO_SDK_PATH="$SDK_PATH" -DPICO_BOARD="$BOARD_TYPE" ..
DONE "CMake configuration complete"

START "Compiling project"
make -j$(nproc)
DONE "Build completed successfully"