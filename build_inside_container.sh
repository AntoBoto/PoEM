#!/bin/bash
set -ex pipefail

# Show compiler and ccache info
echo "Running as: $(whoami)"
cd /home/builder/poem

echo "Initial PWD: $(pwd)"
ls -la

g++ --version
ccache --version
ccache --show-stats

# Initialize and update submodules
echo "Initializing submodules..."
git submodule update --init --recursive

# Set standard compiler flags with C++11 support
export CXXFLAGS="${CXXFLAGS:-O2 -pipe -std=c++11}"
export CFLAGS="${CFLAGS:-O2 -pipe}"
export CPPFLAGS="${CPPFLAGS:-}"

# Run autogen.sh to generate configure script
echo "Running autogen.sh..."
./autogen.sh

echo "Running configure..."

# Properly set Boost detection variables
export BOOST_ROOT=/usr
export BOOST_INCLUDEDIR=/usr/include
export BOOST_LIBRARYDIR=/usr/lib/x86_64-linux-gnu

# Set library paths and linking flags
export LDFLAGS="-L/usr/lib/x86_64-linux-gnu"
export PKG_CONFIG_PATH="/usr/lib/x86_64-linux-gnu/pkgconfig:/usr/share/pkgconfig"

# Check if Boost libraries are present
echo "Checking Boost libraries:"
ls -la /usr/lib/x86_64-linux-gnu/libboost_system*
ls -la /usr/lib/x86_64-linux-gnu/libboost_thread*
ls -la /usr/lib/x86_64-linux-gnu/libboost_filesystem*

./configure \
    --prefix="$PWD/depends/x86_64-linux-gnu" \
    --with-boost-libdir=/usr/lib/x86_64-linux-gnu \
    --with-boost=/usr \
    --disable-tests \
    --disable-bench \
    --without-gui \
    --disable-asm \
    --disable-zmq \
    --disable-wallet \
    --disable-bip70 \
    --disable-man

# Build the project
echo "Building project (make)..."
make -j$(nproc)

# Show ccache stats after build
echo "Final ccache stats:"
ccache --show-stats

echo "Build completed successfully!"
