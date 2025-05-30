#!/bin/bash

# Update remaining bitcoin references in source files
find /home/v2/brrrfren-core/src -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.md" -o -name "*.py" \) \
    -exec sed -i 's/bitcoin\.conf/poem.conf/g' {} \;

# Update test framework references
find /home/v2/brrrfren-core/src/test -type f -name "*.cpp" -exec sed -i 's/test_bitcoin/test_poem/g' {} \;
find /home/v2/brrrfren-core/src/wallet/test -type f -name "*.cpp" -exec sed -i 's/test_bitcoin/test_poem/g' {} \;
find /home/v2/brrrfren-core/src/wallet/test -type f -name "*.h" -exec sed -i 's/test_bitcoin/test_poem/g' {} \;

# Update data directory references
find /home/v2/brrrfren-core/src -type f \( -name "*.cpp" -o -name "*.h" \) \
    -exec sed -i 's/\.bitcoin\>/.poem/g' {} \;

# Update URL references
find /home/v2/brrrfren-core/src -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.md" \) \
    -exec sed -i 's/bitcoin\.org/poem.technology/g' {} \;

# Update email addresses
find /home/v2/brrrfren-core -type f \( -name "*.md" -o -name "*.h" -o -name "*.cpp" \) \
    -exec sed -i 's/info@bitcoin\.org/info@poem.technology/g' {} \;

# Update copyright notices
find /home/v2/brrrfren-core -type f \( -name "*.h" -o -name "*.cpp" -o -name "*.md" \) \
    -exec sed -i 's/Bitcoin Core/PoEM Core/g' {} \;

# Update remaining Bitcoin references (case-sensitive)
find /home/v2/brrrfren-core -type f \( -name "*.h" -o -name "*.cpp" -o -name "*.md" \) \
    -exec sed -i 's/Bitcoin/PoEM/g' {} \;
