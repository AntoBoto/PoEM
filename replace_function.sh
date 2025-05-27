#!/bin/bash
# Find the start line of the function
START_LINE=$(grep -n "CAmount GetBlockSubsidy(int nHeight, const Consensus::Params& params)" src/validation.cpp | cut -d':' -f1)

# Calculate the end line (assumes function ends with a single closing brace on its own line)
END_LINE=$(tail -n +$START_LINE src/validation.cpp | grep -n "^}" | head -1 | cut -d':' -f1)
END_LINE=$((START_LINE + END_LINE - 1))

# Create the new function content
NEW_FUNCTION='CAmount GetBlockSubsidy(int nHeight, const Consensus::Params& params)
{
    // Access the previous block hash if available
    CBlockIndex* pindexPrev = chainActive.Tip();
    uint256 prevHash = pindexPrev ? pindexPrev->GetBlockHash() : uint256();

    // Call the BrrrFren subsidy function
    return GetBrrrFrenBlockSubsidy(nHeight, params, prevHash);
}'

# Replace the function
sed -i "${START_LINE},${END_LINE}c\\${NEW_FUNCTION}" src/validation.cpp
