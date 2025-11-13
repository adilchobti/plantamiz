#!/bin/bash
# Build script for Plantamitz

echo "Building Plantamitz..."

# Clean previous build
make clean

# Build main executable
if make; then
    echo ""
    echo "✓ Build successful!"
    echo "  Executable: ./plantamitz"
    echo ""
    echo "Run with: ./plantamitz"
    echo "Run tests with: make tests"
else
    echo ""
    echo "✗ Build failed!"
    exit 1
fi
