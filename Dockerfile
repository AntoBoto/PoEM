FROM ubuntu:20.04

# Avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install essential build tools and dependencies
RUN apt-get update && apt-get install -y \
    automake \
    autotools-dev \
    build-essential \
    curl \
    g++ \
    gcc-8 \
    g++-8 \
    git \
    libtool \
    make \
    pkg-config \
    python3 \
    wget \
    # Boost 1.71.0 (Ubuntu 20.04 default)
    libboost-all-dev \
    # Other dependencies
    libdb-dev \
    libdb++-dev \
    libevent-dev \
    libminiupnpc-dev \
    libzmq3-dev \
    libqt5gui5 \
    libqt5core5a \
    libqt5dbus5 \
    qttools5-dev \
    qttools5-dev-tools \
    libqrencode-dev \
    libssl-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set the default compiler to GCC-8
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 100

# Create build directory
WORKDIR /build

# Copy the source code
COPY . .

# Default command
CMD ["/bin/bash", "-c", "echo 'Starting build process...' && ./autogen.sh && echo 'Running configure with ABI compatibility flag...' && CXXFLAGS='-D_GLIBCXX_USE_CXX11_ABI=0' ./configure --disable-wallet --without-gui --without-miniupnpc --disable-tests --disable-bench && echo 'Running make...' && make -j$(nproc) && echo 'Build completed. Check for any errors above.'"]
