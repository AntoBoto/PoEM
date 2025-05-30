#!/bin/bash

# Exit on error
set -e

echo "🐳 Building Docker image..."
sudo docker build -t poem-build .

echo "🚀 Running build in Docker container..."
sudo docker run --rm -v "$(pwd):/build" poem-build

echo "✅ Build process completed!"
echo "Check the output above for any errors."
echo "If successful, you should find the compiled binaries in the current directory."
