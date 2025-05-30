#!/bin/bash

# Update Qt includes and references
find /home/v2/brrrfren-core/src/qt -type f \( -name "*.cpp" -o -name "*.h" \) \
    -exec sed -i 's/bitcoin:/poem:/g' {} \;

# Update icon references
find /home/v2/brrrfren-core/src/qt -type f \( -name "*.cpp" -o -name "*.h" \) \
    -exec sed -i 's/icons\/bitcoin/icons\/poem/g' {} \;

# Update desktop file references
find /home/v2/brrrfren-core/src/qt -type f \( -name "*.cpp" -o -name "*.h" \) \
    -exec sed -i 's/bitcoin\.desktop/poem.desktop/g' {} \;

# Update application name in GUI
find /home/v2/brrrfren-core/src/qt -type f \( -name "*.cpp" -o -name "*.h" \) \
    -exec sed -i 's/bitcoin-core/poem-core/g' {} \;
