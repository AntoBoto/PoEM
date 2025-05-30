#!/bin/bash

# Update includes in source files
find /home/v2/brrrfren-core/src -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/#include \(["<]config\/\)bitcoin-config\.h\([>\"]\)/\1poem-config.h\2/g' {} \;

# Update includes in crypto directory
find /home/v2/brrrfren-core/src/crypto -type f \( -name "*.cpp" -o -name "*.h" \) -exec sed -i 's/#include "bitcoin-config\.h"/#include "config\/poem-config.h"/g' {} \;

# Update test includes
find /home/v2/brrrfren-core/src/test -type f -name "*.cpp" -exec sed -i 's/test_bitcoin/test_poem/g' {} \;
find /home/v2/brrrfren-core/src/wallet/test -type f -name "*.cpp" -exec sed -i 's/test_bitcoin/test_poem/g' {} \;
find /home/v2/brrrfren-core/src/wallet/test -type f -name "*.h" -exec sed -i 's/test_bitcoin/test_poem/g' {} \;
