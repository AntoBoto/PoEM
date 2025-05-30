#!/bin/bash

# Rename test files
mv /home/v2/brrrfren-core/src/test/test_bitcoin.h /home/v2/brrrfren-core/src/test/test_poem.h
mv /home/v2/brrrfren-core/src/test/test_bitcoin.cpp /home/v2/brrrfren-core/src/test/test_poem.cpp
mv /home/v2/brrrfren-core/src/test/test_bitcoin_fuzzy.h /home/v2/brrrfren-core/src/test/test_poem_fuzzy.h
mv /home/v2/brrrfren-core/src/test/test_bitcoin_fuzzy.cpp /home/v2/brrrfren-core/src/test/test_poem_fuzzy.cpp
mv /home/v2/brrrfren-core/src/test/test_bitcoin_main.cpp /home/v2/brrrfren-core/src/test/test_poem_main.cpp

# Update includes in test files
find /home/v2/brrrfren-core/src/test -type f -name "*.cpp" -exec sed -i 's/test_bitcoin\.h/test_poem.h/g' {} \;
find /home/v2/brrrfren-core/src/test -type f -name "*.h" -exec sed -i 's/test_bitcoin\.h/test_poem.h/g' {} \;
