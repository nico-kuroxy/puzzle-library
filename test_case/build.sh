#!/bin/sh

# From project root
mkdir -p build
cd build

# Configure the project
cmake ..

# Build everything
cmake --build .

# Install into install/ directory
cmake --install . --prefix ../install
