#!/bin/bash
set -e # Exit on any error

BUILD_DIR="./build"
MAIN_EXE="$BUILD_DIR/src/main" # Corrected from 'main' to 'queue_app'
TESTS_EXE="$BUILD_DIR/tests/tests"

# -S contains path to CMakeLists.txt
# -B is the build directory, will be automatically created
cmake -S. -B./build -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_COMPILER=clang++
# -DCMAKE_CXX_CLANG_TIDY=clang-tidy #

cmake --build ./build --clean-first

if [ ! -L "./compile_commands.json" ] && [ -f "$BUILD_DIR/compile_commands.json" ]; then
  ln -s "$BUILD_DIR/compile_commands.json" .
fi

# if [ -f "$MAIN_EXE" ]; then
#   "$MAIN_EXE" || echo -e "Main executable ran but exited with non-zero code."
# else
#   exit 1
# fi

if [ -f "$TESTS_EXE" ]; then
  "$TESTS_EXE" || echo -e "Tests ran but some may have failed."
else
  exit 1
fi
