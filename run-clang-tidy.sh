#!/bin/bash

set -euo pipefail

# This script runs clang-tidy on the project source files managed by CMake.

# Generate compile_commands.json if it doesn't exist
if [ ! -f build/compile_commands.json ]; then
    echo "Generating compile_commands.json..."
    cmake -D CMAKE_EXPORT_COMPILE_COMMANDS=ON -B build -S src
fi

# Run clang-tidy
echo "Running clang-tidy with the checks defined in .clang-tidy..."
find src \( -name '*.cpp' -o -name '*.hpp' \) -exec clang-tidy -p build {} +
