#!/bin/sh

# From project root
mkdir -p build
cd build

# Configure the project
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build everything
cmake --build .

# Install into install/ directory
cmake --install . --prefix ../install
