// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The PoEM Core developers
// Copyright (c) 2022-2025 The BrrrFren Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>
#include <limits>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

/*
 * ---------------------------------------------------------------------------
 *  Genesis‑block helper that lets us inject a premine output.
 * ---------------------------------------------------------------------------
 */
static CBlock CreateGenesisBlock(const char *pszTimestamp,
                                 const CScript &genesisOutputScript,
                                 uint32_t nTime,
                                 uint32_t nNonce,
                                 uint32_t nBits,
                                 int32_t nVersion,
                                 const CAmount &genesisReward) {
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);

    // ----- premine output --------------------------------------------------
    txNew.vout[0].nValue        = genesisReward;      // 3.57 M BRRR
    txNew.vout[0].scriptPubKey  = genesisOutputScript; // pay‑to‑premine‑pubkey

    // Coinbase input has timestamp message
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4)
        << std::vector<unsigned char>((const unsigned char *)pszTimestamp,
                                      (const unsigned char *)pszTimestamp +
                                      strlen(pszTimestamp));

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/* =======================================================================
 *
 *                       MAIN‑NETWORK PARAMETERS
 *
 * ======================================================================= */
class CMainParams : public CChainParams {
private:
    Consensus::Params digishieldConsensus;
    Consensus::Params auxpowConsensus;

    /* Helper to build premine CScript */
    CScript PremineCScript() const {
        // 33‑byte compressed pubkey (yours):
        static const std::string kPreminePubKeyHex =
            "02b720d7bccf7f6d2d855e161ad598a3b13c9cfa6b1f059a3bad960fa34f5e01ad";
        return CScript() << ParseHex(kPreminePubKeyHex) << OP_CHECKSIG;
    }

public:
    CMainParams() {
        strNetworkID = "main";

        /* ---- consensus baseline (copied from Doge then tweaked) -------- */
        consensus.nSubsidyHalvingInterval      = 100000;  // unused (inflation)
        consensus.nMajorityEnforceBlockUpgrade = 1500;
        consensus.nMajorityRejectBlockOutdated = 1900;
        consensus.nMajorityWindow              = 2000;
        consensus.BIP34Height                  = 1034383; // placeholder
        consensus.BIP34Hash                    = uint256();
        consensus.BIP65Height                  = 3464751;
        consensus.BIP66Height                  = 1034383;
        consensus.powLimit                     = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan           = 4 * 60 * 60; // 4 h
        consensus.nPowTargetSpacing            = 60;          // 1 min
        consensus.fDigishieldDifficultyCalculation = false;
        consensus.nCoinbaseMaturity            = 30;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting            = false;
        consensus.nRuleChangeActivationThreshold = 9576; // 95 %
        consensus.nMinerConfirmationWindow     = 10080; // 1 week

        // No SegWit / CSV for launch
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit       = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout   = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT]        = consensus.vDeployments[Consensus::DEPLOYMENT_CSV];

        // Work & validity assumptions (placeholder until chain grows)
        consensus.nMinimumChainWork   = uint256();
        consensus.defaultAssumeValid  = uint256();

        // Disable Aux‑PoW - we don't need nAuxPowStartHeight, using fAllowLegacyBlocks instead
        consensus.nAuxpowChainId     = 0x0062;
        consensus.fStrictChainId     = true;
        consensus.fAllowLegacyBlocks = true;
        consensus.nHeightEffective   = 0;

        // digishield / auxpow forks kept but unused initially
        digishieldConsensus = consensus;
        digishieldConsensus.nHeightEffective = 145000;
        digishieldConsensus.fDigishieldDifficultyCalculation = true;
        digishieldConsensus.nPowTargetTimespan = 60; // 1 min
        digishieldConsensus.fSimplifiedRewards = true;
        digishieldConsensus.nCoinbaseMaturity  = 240;

        auxpowConsensus = digishieldConsensus;
        auxpowConsensus.nHeightEffective = 371337;
        auxpowConsensus.fAllowLegacyBlocks = true; // Keep legacy blocks to disable AuxPoW

        pConsensusRoot = &digishieldConsensus;
        digishieldConsensus.pLeft  = &consensus;
        digishieldConsensus.pRight = &auxpowConsensus;

        /* ---- network‑ID bytes ----------------------------------------- */
        pchMessageStart[0] = 0xbf;
        pchMessageStart[1] = 0xae;
        pchMessageStart[2] = 0xb9;
        pchMessageStart[3] = 0xfe;
        nDefaultPort       = 17333;
        nPruneAfterHeight  = 100000;

        /* ---- create genesis ------------------------------------------- */
        genesis = CreateGenesisBlock(
            "May 2025 – BrrrFren brings the chill 🧊", // timestamp
            PremineCScript(),                          // premine CScript
            1747693169,                                // nTime - UPDATED
            882501,                                    // nNonce - UPDATED
            0x1e0ffff0,                                // nBits  (Dogecoin start)
            1,                                         // nVersion
            3570000 * COIN);                           // premine amount

        consensus.hashGenesisBlock = genesis.GetHash();
        digishieldConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        auxpowConsensus.hashGenesisBlock     = consensus.hashGenesisBlock;

        // Updated genesis hash and merkle root based on actual values
        
        assert(consensus.hashGenesisBlock == uint256S("0xfec14e972cb2f08722ff1133e0632916ab2e7a628c1838039c8c0b84c1c4d7cf"));
        assert(genesis.hashMerkleRoot == uint256S("0xdc296141be0c20adf978df36a1dc72a3b470c680137a6eb8a3df136537379465"));

       
        // ---- DNS seeds (empty for launch) ------------------------------
        vSeeds.clear();

        /* ---- address prefixes (same as Doge base58 for now) ----------- */
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 22);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 158);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0xfa)(0xca)(0xfd).convert_to_container<std::vector<unsigned char>>();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0xfa)(0xc3)(0x98).convert_to_container<std::vector<unsigned char>>();

        vFixedSeeds.clear();

        fMiningRequiresPeers      = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard         = true;
        fMineBlocksOnDemand       = false;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0xfec14e972cb2f08722ff1133e0632916ab2e7a628c1838039c8c0b84c1c4d7cf"))
        };
        
        chainTxData = ChainTxData{
            1747693169, // Genesis block timestamp - UPDATED
            0,          // 0 transactions
            0           // 0 transactions per second
        };
    }
};
static CMainParams mainParams;

/* =======================================================================
 *                    TESTNET & REGTEST (trimmed for brevity)
 *   => For initial bring‑up you can copy CMainParams and tweak ports.
 * ======================================================================= */
class CTestNetParams : public CChainParams {
private:
    Consensus::Params digishieldConsensus;
    Consensus::Params auxpowConsensus;
    Consensus::Params minDifficultyConsensus;
    
    /* Helper to build premine CScript - same as main */
    CScript PremineCScript() const {
        // 33‑byte compressed pubkey (yours):
        static const std::string kPreminePubKeyHex =
            "02b720d7bccf7f6d2d855e161ad598a3b13c9cfa6b1f059a3bad960fa34f5e01ad";
        return CScript() << ParseHex(kPreminePubKeyHex) << OP_CHECKSIG;
    }
    
public:
    CTestNetParams() {
        strNetworkID = "test";
        
        // Initialize parameters similar to mainnet but don't use direct assignment
        consensus.nSubsidyHalvingInterval = 100000;
        consensus.nMajorityEnforceBlockUpgrade = 501;
        consensus.nMajorityRejectBlockOutdated = 750;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 708658;
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1854705;
        consensus.BIP66Height = 708658;
        consensus.powLimit = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 4 * 60 * 60;
        consensus.nPowTargetSpacing = 60;
        consensus.fDigishieldDifficultyCalculation = false;
        consensus.nCoinbaseMaturity = 30;
        consensus.fPowAllowMinDifficultyBlocks = true; // Different from mainnet
        consensus.fPowAllowDigishieldMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 2880; // Different from mainnet
        consensus.nMinerConfirmationWindow = 10080;
        consensus.nHeightEffective = 0;
        
        // CSV/SegWit params
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT] = consensus.vDeployments[Consensus::DEPLOYMENT_CSV];
        
        // AuxPoW params
        consensus.nAuxpowChainId = 0x0000; // Change for regtest to disable auxpow
        consensus.fStrictChainId = false; // Different from mainnet
        consensus.fAllowLegacyBlocks = true;
        
        // Work validity assumptions
        consensus.nMinimumChainWork = uint256();
        consensus.defaultAssumeValid = uint256();
        
        // Blocks 145000 - 157499 are Digishield without minimum difficulty on all blocks
        digishieldConsensus = consensus;
        digishieldConsensus.nHeightEffective = 145000;
        digishieldConsensus.nPowTargetTimespan = 60; // post-digishield: 1 minute
        digishieldConsensus.fDigishieldDifficultyCalculation = true;
        digishieldConsensus.fSimplifiedRewards = true;
        digishieldConsensus.fPowAllowMinDifficultyBlocks = false;
        digishieldConsensus.nCoinbaseMaturity = 240;

        // Blocks 157500 - 158099 are Digishield with minimum difficulty on all blocks
        minDifficultyConsensus = digishieldConsensus;
        minDifficultyConsensus.nHeightEffective = 157500;
        minDifficultyConsensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        minDifficultyConsensus.fPowAllowMinDifficultyBlocks = true;

        // Blocks 158100+ - keeping legacy blocks allowed to disable AuxPoW
        auxpowConsensus = minDifficultyConsensus;
        auxpowConsensus.nHeightEffective = 158100;
        auxpowConsensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        auxpowConsensus.fAllowLegacyBlocks = true; // Keep legacy blocks to disable AuxPoW

        // Assemble the binary search tree of parameters
        pConsensusRoot = &digishieldConsensus;
        digishieldConsensus.pLeft = &consensus;
        digishieldConsensus.pRight = &minDifficultyConsensus;
        minDifficultyConsensus.pRight = &auxpowConsensus;
        
        // Network parameters
        pchMessageStart[0] = 0xca;
        pchMessageStart[1] = 0xfe;
        pchMessageStart[2] = 0xba;
        pchMessageStart[3] = 0xbe;
        nDefaultPort = 28333;
        nPruneAfterHeight = 1000;
        
        // Create genesis with the updated parameters
        genesis = CreateGenesisBlock(
            "May 2025 – BrrrFren brings the chill 🧊",
            PremineCScript(),
            1747689314,                               // nTime
            2036163,                                  // nNonce
            0x1e0ffff0,                               // nBits
            1,                                        // nVersion
            3570000 * COIN
        );
        
        consensus.hashGenesisBlock = genesis.GetHash();
        digishieldConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        minDifficultyConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        auxpowConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        
        // Updated genesis hash and merkle root based on actual values
        assert(consensus.hashGenesisBlock == uint256S("0x594a620b1b6fbc20d7cf6e390c60b5ac23ae9f43b907874a77f2db70bfd1a899"));
        assert(genesis.hashMerkleRoot == uint256S("0xdc296141be0c20adf978df36a1dc72a3b470c680137a6eb8a3df136537379465"));
        
        vSeeds.clear();
        
        // Same address prefixes as mainnet
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 113); // Different from mainnet
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196); // Different from mainnet
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 241); // Different from mainnet
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xcf).convert_to_container<std::vector<unsigned char>>();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char>>();
        
        vFixedSeeds.clear();
        
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = true; // easy testing
        
        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (0, uint256S("0x594a620b1b6fbc20d7cf6e390c60b5ac23ae9f43b907874a77f2db70bfd1a899"))
        };
        
        chainTxData = ChainTxData{
            1747689314, // Genesis block timestamp
            0,          // 0 transactions
            0           // 0 transactions per second
        };
    }
};
static CTestNetParams testNetParams;

class CRegTestParams : public CChainParams {
private:
    Consensus::Params digishieldConsensus;
    Consensus::Params auxpowConsensus;
    
    /* Helper to build premine CScript - same as main */
    CScript PremineCScript() const {
        // 33‑byte compressed pubkey (yours):
        static const std::string kPreminePubKeyHex =
            "02b720d7bccf7f6d2d855e161ad598a3b13c9cfa6b1f059a3bad960fa34f5e01ad";
        return CScript() << ParseHex(kPreminePubKeyHex) << OP_CHECKSIG;
    }
    
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        
        // Initialize parameters for regtest
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 100000000;
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351;
        consensus.BIP66Height = 1251;
        consensus.powLimit = uint256S("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 4 * 60 * 60;
        consensus.nPowTargetSpacing = 1; // 1-sec blocks
        consensus.fDigishieldDifficultyCalculation = false;
        consensus.nCoinbaseMaturity = 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 540;
        consensus.nMinerConfirmationWindow = 720;
        consensus.nHeightEffective = 0;
        
        // CSV/SegWit params
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT] = consensus.vDeployments[Consensus::DEPLOYMENT_CSV];
        
        // AuxPoW params
        consensus.nAuxpowChainId = 0x0062;
        consensus.fStrictChainId = true;
        consensus.fAllowLegacyBlocks = true;
        
        // Work validity assumptions
        consensus.nMinimumChainWork = uint256S("0x00");
        consensus.defaultAssumeValid = uint256S("0x00");

        digishieldConsensus = consensus;
        digishieldConsensus.nHeightEffective = 10;
        digishieldConsensus.nPowTargetTimespan = 1; // regtest: also retarget every second in digishield mode
        digishieldConsensus.fDigishieldDifficultyCalculation = true;

        auxpowConsensus = digishieldConsensus;
        auxpowConsensus.fAllowLegacyBlocks = true; // Keep legacy blocks to disable AuxPoW
        auxpowConsensus.nHeightEffective = 10000;

        // Assemble the binary search tree of parameters
        digishieldConsensus.pLeft = &consensus;
        digishieldConsensus.pRight = &auxpowConsensus;
        pConsensusRoot = &digishieldConsensus;
        
        // Network parameters
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 18444;
        
        // Create genesis with the updated parameters
        genesis = CreateGenesisBlock(
            "May 2025 – BrrrFren brings the chill 🧊",
            PremineCScript(),
            1747689314,                              // nTime
            5,                                       // nNonce
            0x207fffff,                              // nBits
            1,                                       // nVersion
            3570000 * COIN
        );
        
        consensus.hashGenesisBlock = genesis.GetHash();
        digishieldConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        auxpowConsensus.hashGenesisBlock = consensus.hashGenesisBlock;
        
        // Updated genesis hash and merkle root based on actual values
        assert(consensus.hashGenesisBlock == uint256S("0x90cdb37348e4256e2f33525bc9cbb7cc4b29f42765a004a7cfd5d234c2b4ec69"));
        assert(genesis.hashMerkleRoot == uint256S("0xdc296141be0c20adf978df36a1dc72a3b470c680137a6eb8a3df136537379465"));
        
        vSeeds.clear();
        
        // Different address prefixes for regtest
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char>>();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char>>();
        
        vFixedSeeds.clear();
        
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        
        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            (0, uint256S("0x90cdb37348e4256e2f33525bc9cbb7cc4b29f42765a004a7cfd5d234c2b4ec69"))
        };
        
        chainTxData = ChainTxData{
            1747689314, // Genesis block timestamp
            0,          // 0 transactions
            0           // 0 transactions per second
        };
    }
    
    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

/* --------------------------------------------------------------------- */
static CChainParams *pCurrentParams = nullptr;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

// Critical missing function that was causing linker errors
const Consensus::Params *Consensus::Params::GetConsensus(uint32_t nTargetHeight) const {
    if (nTargetHeight < this->nHeightEffective && this->pLeft != NULL) {
        return this->pLeft->GetConsensus(nTargetHeight);
    } else if (nTargetHeight > this->nHeightEffective && this->pRight != NULL) {
        const Consensus::Params *pCandidate = this->pRight->GetConsensus(nTargetHeight);
        if (pCandidate->nHeightEffective <= nTargetHeight) {
            return pCandidate;
        }
    }

    // No better match below the target height
    return this;
}

CChainParams &Params(const std::string &chain) {
    if (chain == CBaseChainParams::MAIN)
        return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
        return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
        return regTestParams;
    throw std::runtime_error(strprintf("%s: Unknown chain %s", __func__, chain));
}

void SelectParams(const std::string &network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

// Missing function that was causing the second linker error
void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
