#!/bin/bash
set -e

# Create ccache directory with proper permissions
echo "Setting up ccache directory..."
if [ ! -d "/ccache" ]; then
    sudo mkdir -p /ccache
    sudo chmod -R 777 /ccache
    echo "Created /ccache directory."
else
    sudo chmod -R 777 /ccache
    echo "/ccache directory already exists, permissions set."
fi

# Clean up previous Docker container if it exists
echo "Cleaning up previous Docker container (if any)..."
docker rm -f poem-builder-container || true

# Build the Docker image (which now includes build_inside_container.sh)
echo "Building Docker image poem-builder..."
docker build -t poem-builder -f Dockerfile.ci .

# Run the build inside the container by executing the script
echo "Starting the build process inside the container..."
docker run --rm --name poem-builder-container \
    -v "/ccache:/ccache" \
    -v "$(pwd):/home/builder/poem" \
    --user builder \
    -w /home/builder/poem \
    poem-builder \
    /usr/local/bin/build_inside_container.sh

echo "Build script finished."