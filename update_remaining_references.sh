#!/bin/bash

# Update remaining bitcoin references in source files
find /home/v2/brrrfren-core/src -type f \( -name "*.cpp" -o -name "*.h" \) \
    -exec sed -i 's/bitcoind/poemd/g' {} \;

# Update CLI references
find /home/v2/brrrfren-core/src -type f \( -name "*.cpp" -o -name "*.h" \) \
    -exec sed -i 's/bitcoin-cli/poem-cli/g' {} \;

# Update TX references
find /home/v2/brrrfren-core/src -type f \( -name "*.cpp" -o -name "*.h" \) \
    -exec sed -i 's/bitcoin-tx/poem-tx/g' {} \;

# Update QT references
find /home/v2/brrrfren-core/src -type f \( -name "*.cpp" -o -name "*.h" \) \
    -exec sed -i 's/bitcoin-qt/poem-qt/g' {} \;
