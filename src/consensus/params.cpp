// Copyright (c) 2009-2016 The PoEM Core developers
// Copyright (c) 2022-2023 The BrrrFren Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "params.h"
#include "chainparams.h"

namespace Consensus {

const Consensus::Params* Params::GetConsensus(uint32_t nTargetHeight) const {
    // Simple implementation that returns the current params regardless of height
    // This can be extended if you need different params at different heights
    return this;
}

} // namespace Consensus

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, long nStartTime, long nTimeout) {
    SelectParams(CBaseChainParams::REGTEST);
    // Use the Params() function instead of directly accessing globalChainParams
    const_cast<CChainParams&>(Params()).UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
