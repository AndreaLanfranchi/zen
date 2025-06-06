// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2018-2023 Zen Blockchain Foundation
// Copyright (c) 2023-2024 The Horizen Foundation
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "main.h"
#include "crypto/equihash.h"

#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "base58.h"

using namespace std;

#include "chainparamsseeds.h"

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        strCurrencyUnits = "ZEN";
        consensus.nSubsidySlowStartInterval = 2;
        consensus.nSubsidyHalvingInterval = 840000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 4000;
        consensus.powLimit = uint256S("0007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowAveragingWindow = 17;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 32; // 32% adjustment down
        consensus.nPowMaxAdjustUp = 16; // 16% adjustment up
        consensus.nPowTargetSpacing = 2.5 * 60;
//        consensus.fPowAllowMinDifficultyBlocks = false;

        /**
         * ZEN Network Magic Start Value
         */
        pchMessageStart[0] = 0x63;
        pchMessageStart[1] = 0x61;
        pchMessageStart[2] = 0x73;
        pchMessageStart[3] = 0x68;
        nDefaultPort = 9033;
//       nMinerThreads = 0;
        nMaxTipAge = 24 * 60 * 60;
        nPruneAfterHeight = 100000;
        const size_t N = 200, K = 9;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        nEquihashN = N;
        nEquihashK = K;

        /**
         * Build the genesis block. Note that the output of its generation
         * transaction cannot be spent since it did not originally exist in the
         * database (and is in any case of zero value).
         *
         * >>> from pyblake2 import blake2s
         * >>> 'Zcash' + blake2s(b'The Economist 2016-10-29 Known unknown: Another crypto-currency is born. BTC#436254 0000000000000000044f321997f336d2908cf8c8d6893e88dbf067e2d949487d ETH#2521903 483039a6b6bd8bd05f0584f9a078d075e454925eb71c1f13eaff59b405a721bb DJIA close on 27 Oct 2016: 18,169.68').hexdigest()
         */
        const char* pszTimestamp = "Zclassic860413afe207aa173afee4fcfa9166dc745651c754a41ea8f155646f5aa828ac";
        CMutableTransaction txNew;
        txNew.nVersion = 1;
        txNew.vin.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>(reinterpret_cast<const unsigned char*>(pszTimestamp), reinterpret_cast<const unsigned char*>(pszTimestamp) + strlen(pszTimestamp));
        txNew.addOut(CTxOut());
        txNew.getOut(0).nValue = 0;
        txNew.getOut(0).scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock.SetNull();
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 4;
        genesis.nTime    = 1478403829;
        genesis.nBits    = 0x1f07ffff;
        genesis.nNonce   = uint256S("0x000000000000000000000000000000000000000000000000000000000000021d");
        genesis.nSolution = ParseHex("009aaa951ca873376788d3002918d956e371bdf03c1afcfd8eea17867b5480d2e59a2a4dd52ed0d091af0c0909aa66ce2da97266926a9ea69b9ccca389bc120d9c4dbbae727ab9d6dfd1cd847df0ef0cc9bc989f11bdd6522429c15957daa3c5a2612522ded69857c148c0638611a19287599b47683c714b5774d0fcb1341cf4fc3a546a2441a19f02a55c6f9775749e57783b2abd5b25d41753d2f60892bbb4c3173d7787dbf5e50267324db218a14dd65f71bb02cf2566d3201800f866701db8c221424b75c639de58e7e40705157ae7d10da708ec2b9e71b9bc1ad34854a7bdf58d93766b6e291d3b545fa1f785a1a9829eccd525d16856f4317f0449d5c3516736f1e564f17690f13d3c939ad5516f1db70194902c20afd939168037fa404ec962dfbe752f79ac87a2cc3fd07bcd94d1975b1849cc739c0bc144ae4e75eda1bbed5b5ef8f65966257ec7b1fc6bb600e12e1c65c8c13a505f35dd363e07b6238211a0e502e36db5a620310b544360dd9b4a6cedabc34eeb530139daad50d4a5b6eaf4d50be4ba10e970ce984fb705376a3b0b4bf3f3778600f14e739e04406106f707085ab87ca70598c032b6717a54a9fd8ef72fdd78fb41fa9d45ad685caf77e0fc42e8e644634c24bc972f3ab0e3f0345854eda624045feb6bc9d20b5b1fc6903ebc64026e51da598c0d8711c452131a8fd2bbe01403af20e5db88afcd53b6107f001dae78b548d6a1581baca15359de83e54e75d8fc6374ca1edec17a9f4b06931162f9952575c5c3fb5dfc70a0f793049e781926daaafd4f4d330cf7d5635af1541f0d29e709a37c088d6d2e7aa09d15dfb9c2ae6c1ce661e85e9d89772eb47cfea00c621b66faf8a48cfa970b898dbd77b14e7bf44b742c00f76d2435f949f027132adb1e974551488f988e9fe379a0f86538ee59e26637a3d50bf400c7f52aa9457d77c3eb426628bb17909b26a6820d0772d4c6f74472f635e4c6e72272ce01fc475df69e10371457c55e0fbdf3a392850b9924da9c9a55792325c4318562593f0df8d39559065be03a22b1b6c21206aa1958a0d33257d89b74dea42a11aabf8eddbfe6136ab649744b704eb3e3d473654b588927dd9f486c1cd02639cf656ccbf2c4869c2ed1f2ba4ec55e69a42d5af6b3605a0cdf987734727c6fc1c1489870fb300139328c4d12eb6f5e8309cc09f5f3c29ab0957374113931ec9a56e7579446f12faacda9bd50899a17bd0f78e89ed70a723fdadfb1f4bc3317c8caa32757901604fb79ae48e22251c3b1691125ec5a99fabdf62b015bc817e1c30c06565a7071510b014058a77856a150bf86ab0c565b8bbbed159e2fb862c6215752bf3f0563e2bbbf23b0dbfb2de21b366b7e4cda212d69502643ca1f13ce362eef7435d60530b9999027dd39cd01fd8e064f1ccf6b748a2739707c9f76a041f82d3e046a9c184d83396f1f15b5a11eddb2baff40fc7b410f0c43e36ac7d8ff0204219abe4610825191fbb2be15a508c839259bfd6a4c5204c779fad6c23bbd37f90709654a5b93c6f93b4c844be12cd6cd2200afbf600b2ae9b6c133d8cdb3a85312a6d9948213c656db4d076d2bacd10577d7624be0c684bd1e5464bb39006a524d971cd2223ae9e23dea12366355b3cc4c9f6b8104df6abd23029ac4179f718e3a51eba69e4ebeec511312c423e0755b53f72ac18ef1fb445d7ab83b0894435a4b1a9cd1b473792e0628fd40bef624b4fb6ba457494cd1137a4da9e44956143068af9db98135e6890ef589726f4f5fbd45a713a24736acf150b5fb7a4c3448465322dccd7f3458c49cf2d0ef6dd7dd2ed1f1147f4a00af28ae39a73c827a38309f59faf8970448436fbb14766a3247aac4d5c610db9a662b8cb5b3e2");

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0007104ccda289427919efc39dc9e4d499804b7bebc22df55f8b834301260602"));
        assert(genesis.hashMerkleRoot == uint256S("0x19612bcf00ea7611d315d7f43554fa983c6e8c30cba17e52c679e0e80abf7d42"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("dnsseed.horizen.global", "dnsseed.horizen.global")); // dns seeder
        vSeeds.push_back(CDNSSeedData("dnsseed.zensystem.io", "dnsseed.zensystem.io")); // dns seeder
        vSeeds.push_back(CDNSSeedData("mainnet.horizen.global", "mainnet.horizen.global")); // fixed seed
        vSeeds.push_back(CDNSSeedData("mainnet.zensystem.io", "mainnet.zensystem.io")); // fixed seed
        vSeeds.push_back(CDNSSeedData("node1.zenchain.info", "node1.zenchain.info")); // fixed seed

        // guarantees the first 2 characters, when base58 encoded, are "zn"
        // guarantees the first 2 characters, when base58 encoded, are "t1"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x20,0x89};
        base58Prefixes[PUBKEY_ADDRESS_OLD]     = {0x1C,0xB8};
        // guarantees the first 2 characters, when base58 encoded, are "zs"
        // guarantees the first 2 characters, when base58 encoded, are "t3"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x20,0x96};
        base58Prefixes[SCRIPT_ADDRESS_OLD]     = {0x1C,0xBD};
        // the first character, when base58 encoded, is "5" or "K" or "L" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0x80};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x88,0xB2,0x1E};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x88,0xAD,0xE4};
        // guarantees the first 2 characters, when base58 encoded, are "zc"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0x9A};
        // guarantees the first 2 characters, when base58 encoded, are "SK"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAB,0x36};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nCbhMinimumAge = 99;
        nCbhSafeDepth = 52596;
        nScCoinsMaturity = 10;
        nScNumBlocksForScFeeCheck = 200;
        nScMinWithdrawalEpochLength = 100;
        nScMaxWithdrawalEpochLength = 4032; // one week at 1 block/2.5 min rate
        nScMaxNumberOfCswInputsInMempool = 100;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            (       0, consensus.hashGenesisBlock)
            (   30000, uint256S("0x000000005c2ad200c3c7c8e627f67b306659efca1268c9bb014335fdadc0c392"))
            (   96577, uint256S("0x0000000177751545bd1af3ccf276ec2920d258453ab01f3d2f8f7fcc5f3a37b8"))
            (  110000, uint256S("0x000000003f5d6ba1385c6cd2d4f836dfc5adf7f98834309ad67e26faef462454"))
            (  139200, uint256S("0x00000001ea53c09a45e3f097ba8f48a4c117b5b368031c4eb2fa02cb5a84c99e"))
            (  294072, uint256S("0x000000005f9ceecc87d9e5eaab2cf548c787231829ad6f609975fadd10fff5be"))
            (  429014, uint256S("0x000000000dc4f58375d9fa6dc4cb1bfc4b0afefbf4f7e1ee2cc755d6ca3b40b0"))
            (  491000, uint256S("0x0000000018d0b189de58bcd8ff5048d2e4d1c652b98912ff002c8f07c6f81b8c"))
            (  543000, uint256S("0x00000000111469e247ecb152e57c371147775b56173260950075dcb471614fed"))
            (  596000, uint256S("0x000000000656846513b2d3faf3a70f59dc22fffcb8e14401ec5a17eec8994410"))
            (  671000, uint256S("0x00000000097174dacaf850075917d1a24145fce88a800881ece709bb8f8746cf"))
            (  724100, uint256S("0x000000000ab34fd9c61be9f10a11a97f63a0f26c8f530e67a6397fb9934709dc"))
            (  812000, uint256S("0x0000000000bccf70e0d2caa0473279decddb798f456d5a4bb399898e00eb4ce9"))
            (  902500, uint256S("0x0000000001258f2009278d042ed42dfd825de9a2bc31e410c0463bc8d6371ee4"))
            ( 1014400, uint256S("0x00000000001564ef09ddc49728c4c44701fd348c418ced0ee9f656660cc08e3a"))
            ( 1035000, uint256S("0x0000000002cadc8f4c43ab96406211c489318c2e56b8e7d1e4e4b9fa5dffeea5"))
            ( 1107000, uint256S("0x000000000184d804ea3b77864616d5af5bb2dbe1953a805a47c427e9dceeca7b"))
            ( 1218500, uint256S("0x000000000335a5c54143d3fc6e143baeeb9a11e5e2250487b578f370114cd879"))
            ( 1286500, uint256S("0x0000000002b9240e8e1ce741102c0d873148665e2aa45e5122fabf478b5c2fc2"))
            ( 1301500, uint256S("0x0000000003bafe8331f9753bc374f9c27539d640a1f86cbd25477e5732d1ff8c"))
            ( 1318100, uint256S("0x0000000000ad43247472917f4385eb168ea56e43d36c10443cca624331d06720"))
            ( 1348100, uint256S("0x00000000035196fb7f9896df5e3efcb7ea75223368958ed616131636cf03568a"))
            ( 1410300, uint256S("0x000000000025414cc58c41f92172421a1521b949a6c1bd42908c11ce424b9209"))
            ( 1450700, uint256S("0x00000000010fee71b2d54776c151199806e10125143f0ccf58b93e4240d42129"))
            ( 1491300, uint256S("0x0000000000c9ad17d7a620c85232d65947b47bfc8978da96d24064d22044b1aa"))
            ( 1511300, uint256S("0x00000000023fd9742aa11f6b62a3c8f2ae4884130de24d691b0566e9d62c517d"))
            ( 1536300, uint256S("0x000000000280a09437552d0fda2bc6473988e3254222f326c32875c8e43c5d2f"))
            ( 1569500, uint256S("0x00000000007901da2a6050d0ad7e2a6598ca6c7409209ab2b3b5e881f5c4f9b1"))
            ( 1614500, uint256S("0x000000000424fddeb3ae90a4decf180eaceb61397cd1b0a0a24adde538cd6f67"))
            ( 1668200, uint256S("0x00000000026f923e8714b7107c88d0a7cbaad2acf87d9fe089f2bd4d2a9b4b4f"))
            ( 1722000, uint256S("0x000000000115d51aa796fd210da73dc2b999308d73fd17ab4e95e924f8b38ec8")),
            1740377016,     // * UNIX timestamp of last checkpoint block
            38459408,       // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
            12864           // * estimated number of transactions per day after checkpoint
                            //   total number of tx / (checkpoint block height / (24 * 24))
        };

//  commented out - seems to make no sense but kept around for reference just in case
//        assert(vCommunityFundAddress.size() <= consensus.GetLastCommunityRewardBlockHeight());
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        strCurrencyUnits = "ZNT";
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 400;
        consensus.powLimit = uint256S("07ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
//        consensus.fPowAllowMinDifficultyBlocks = true;

        pchMessageStart[0] = 0xbf;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xcd;
        pchMessageStart[3] = 0xe6;
        nDefaultPort = 19033;
//        nMinerThreads = 0;
        nPruneAfterHeight = 1000;

        genesis.nTime = 1479443947;
        genesis.nBits = 0x2007ffff;
        genesis.nNonce = uint256S("0x0000000000000000000000000000000000000000000000000000000000000013");
        genesis.nSolution = ParseHex("002b24e10a5d2ab32b053a20ca6ebed779be1d935b1500eeea5c87aec684c6f934196fdfca6539de0cf1141544bffc5c0d1d4bab815fb5d8c2b195ccdf0755599ee492b9d98e3b79a178949f45485ad80dba38ec0461102adaa369b757ebb2bf8d75b5f67a341d666406d862a102c69800f20a7075be360a7eb2d315d78e4ce32c741f3baf7bf3e1e651976f734f367b1f126f62503b34d06d6e99b3659b2a47f5cfcf71c87e24e5023151d4af87454e7638a19b846350dd5fbc53e4ce1cce2597992b36cbcae0c24717e412c8df9ddca3e90c7629bd8c157c66d8906486943cf78e24d55dd4152f45eff49acf9fb9fddef81f2ee55892b38db940c404eaacf819588b83f0f761f1ba5b31a0ea1f8f4c5210638bbb59a2d8ddff9535f546b42a7eac5f3ee87616a075bddc3118b7f2c041f4b1e8dbcd11eea95835403066b5bb50cd23122dcb12166d75aafcfc1ca8f30580b4d48a5aa305657a06b4b650ed4633f2fa496235082feff65f70e19871f41b70632b53e57ddf38c207d631e5a56fa50bb71150f99427f73d82a439a5f70dfc7d8bbfc39d330ca7924527a5deb8950b9fa7020cfde5e07b84546e96764519ef6dd3fdc3a974abd342bdc7e4ee76bc11d5519541015afba1a0517fd347196aa326b0905a5916b83515c16f8f13105479c29f1eff3bc024ddbb07dcc672247cedc0d4ba32332ead0f13c58f50170642e16e076c34f5e75e3e8f5ac7f5238d67564fd385efecf972b0abf939a99bc7ef8f3a21cac21d2168706bbad3f4af66bb01cf61cfbc352a23797b62dcb5480bf2b7b277af233f5ce42a144d47119a89e1d114fa0bec2f13475b6b1df907bc3a429f1771afa3857bf16bfca3f76a5df14da62dc157fff4225bda73c3cfefa989edc24673bf932a024593da4c38b1a4628dd77ad919f4f7b7fb76976e696db69c89016ab30d9aa2d509f78d913d00ca9ac881aa759fc019b8c5e3eac6fddb4e0f044595e10d4997e29c79800f77cf1d97583d534db0f2726cba3739e7371eeffa2aca12b0d290ac45f44973f32f7675a5b49c94c4b608da2926555d16b7eb3670e12345a63f88797e5a5e21252c2c9463d7896001031a81bac0354336b35c5a10c93d9ae3054f6f6e4492f7c1f09a9d75034d5d0b220a9bb231e583659d5b6923a4e879326194de5c9805a02cb648508a8f9b6cd26dc17d322a478c1c599e1ec3adf2da6ce7a7e3a073b55cf30cf6b124f7700409abe14af8c60ab178579623916f165dbfd26f37056bf33c34f3af30939e1277376e4c5cba339f36381a05ef6481db033fb4c07a19e8655f8b12f9ab3c602e127b4ab1ee48e1c6a91382b54ed36ef9bb21b3bfa80a9107864dcb594dcad250e402b312607e648639631a3d1aeb17cfe3370202720ca8a46db15af92e8b46062b5bd035b24c35a592e5620d632faf1bf19a86df179fe52dd4cdbecd3cb7a336ca7489e4d1dc9433f1163c89d88c5eac36fc562496dc7583fe67c559c9a71cf89e9a0a59d5a14764926852d44a88d2ddb361d612ec06f9de874473eaf1d36b3a41911ac072b7826e6acea3d8425dc271833dba2ec17d1a270e49becbf21330ba2f0edc4b05f4df01623f3c82246ae23ea2c022434ef09611aa19ba35c3ecbad965af3ad9bc6c9b0d3b059c239ffbf9272d0150c151b4510d659cbd0e4a9c32945c612681b70ee4dcbeefeacde630b127115fd9af16cef4afefe611c9dfcc63e6833bf4dab79a7e1ae3f70321429557ab9da48bf93647830b5eb5780f23476d3d4d06a39ae532da5b2f30f151587eb5df19ec1acf099e1ac506e071eb52c3c3cc88ccf6622b2913acf07f1b772b5012e39173211e51773f3eb42d667fff1d902c5c87bd507837b3fd993e70ac9706a0");
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x03e1c4bb705c871bf9bfda3e74b7f8f86bff267993c215a89d5795e3708e5e1f"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("dnsseed.testnet.horizen.global", "dnsseed.testnet.horizen.global")); // dns seeder
        vSeeds.push_back(CDNSSeedData("dnsseed.testnet.zensystem.io", "dnsseed.testnet.zensystem.io")); // dns seeder
        vSeeds.push_back(CDNSSeedData("testnet.horizen.global", "testnet.horizen.global")); // fixed seed
        vSeeds.push_back(CDNSSeedData("testnet.zensystem.io", "testnet.zensystem.io")); // fixed seed
        vSeeds.push_back(CDNSSeedData("node1.zenchain.info", "node1.zenchain.info")); // fixed seed

        // guarantees the first 2 characters, when base58 encoded, are "zt"
        // guarantees the first 2 characters, when base58 encoded, are "tm"
        base58Prefixes[PUBKEY_ADDRESS]     = {0x20,0x98};
        base58Prefixes[PUBKEY_ADDRESS_OLD]     = {0x1D,0x25};
        // guarantees the first 2 characters, when base58 encoded, are "zr"
        // guarantees the first 2 characters, when base58 encoded, are "t2"
        base58Prefixes[SCRIPT_ADDRESS]     = {0x20,0x92};
        base58Prefixes[SCRIPT_ADDRESS_OLD]     = {0x1C,0xBA};
        // the first character, when base58 encoded, is "9" or "c" (as in Bitcoin)
        base58Prefixes[SECRET_KEY]         = {0xEF};
        // do not rely on these BIP32 prefixes; they are not specified and may change
        base58Prefixes[EXT_PUBLIC_KEY]     = {0x04,0x35,0x87,0xCF};
        base58Prefixes[EXT_SECRET_KEY]     = {0x04,0x35,0x83,0x94};
        // guarantees the first 2 characters, when base58 encoded, are "zt"
        base58Prefixes[ZCPAYMENT_ADDRRESS] = {0x16,0xB6};
        // guarantees the first 4 characters, when base58 encoded, are "ZiVt"
        base58Prefixes[ZCVIEWING_KEY]      = {0xA8,0xAC,0x0C};
        // guarantees the first 2 characters, when base58 encoded, are "ST"
        base58Prefixes[ZCSPENDING_KEY]     = {0xAC,0x08};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nCbhMinimumAge = 99;
        nCbhSafeDepth = 52596;
        nScCoinsMaturity = 10;
        nScNumBlocksForScFeeCheck = 200;
        nScMinWithdrawalEpochLength = 100;
        nScMaxWithdrawalEpochLength = 4032;
        nScMaxNumberOfCswInputsInMempool = 100;

        checkpointData = (Checkpoints::CCheckpointData) {
            boost::assign::map_list_of
            (       0, consensus.hashGenesisBlock)
            (   38000, uint256S("0x001e9a2d2e2892b88e9998cf7b079b41d59dd085423a921fe8386cecc42287b8"))
            (  362210, uint256S("0x00023d5c074a7c2ccf130dac34b2b6f77e3c4466cfed0b72c3f3715157c92949"))
            (  423000, uint256S("0x000d04b28067fe99445961f795ee7436f1dbbffc3a045f6890868e605209d170"))
            (  467550, uint256S("0x0007f73f339ea99e920e83da38d7537ce7d0028d48e709c88b1b89adf521b4f9"))
            (  520000, uint256S("0x00052e65426a0ffbb90893208a6c89a82816abbed328fa2be5a647828609e61a"))
            (  595000, uint256S("0x0000da85ddc79fdd297e996d6b6b887fc5b345619b7a6726c496941dcf830966"))
            (  643000, uint256S("0x0000cabf39e3ac435d54b95c32e6173d6bb1b060066ecb7453d2146a0dd40947"))
            (  729000, uint256S("0x00013f6d5315f29094287bf0981b177098c5d467422bc4ab7764f88f11333f5f"))
            (  816500, uint256S("0x0004c69745c68058fb35b2a8e090887500f71f7e107f0fd6f3e57d21afa5fe76"))
            (  869828, uint256S("0x0009d4d6d27f523b76ef9ed76b4a4c5044d30b3a6248b0a7296bdc58a5524c05"))
            (  924840, uint256S("0x0007e7525b8958d387aedbfbc622feed4a82d7ecb1033a080af75dcb8933a453"))
            (  926224, uint256S("0x0001bbe15a4dc7b4c580ba3211c0d074d5716a0eb924d228440f88e0dfc23248")) // pre fork8
            (  926225, uint256S("0x0002032ec1b1cc65502e24959a3fb6ed04ff52ff67add53c90cddfeca6cd13c6")) // fork8 activation
            (  949700, uint256S("0x0001ec9be52a04c305335d0669bd2aa283248be6f274ab5280bd883d8b8db0d8"))
            ( 1021000, uint256S("0x000118d2f94a42758d0efa60d5a95f968a668b0d4669cd7ca0c20b95d1d187e8"))
            ( 1133000, uint256S("0x00022703828f9b9e76d2c11525d9fcc182b2119095b27c5f51081615b3132b11"))
            ( 1201000, uint256S("0x0004acc3f9f26a8314a59962219b23e3c7ed06cbec16893fb0ea8a993167a847"))
            ( 1216000, uint256S("0x000288327d649ba2a7d570c8e103cc2ed4a4d3a0581d0b4794fc2645756f9ef6"))
            ( 1232700, uint256S("0x00094f376533c408e24dccaa16dbab3e060aa98b5fddf19aa8af708157c81892"))
            ( 1262900, uint256S("0x0001e8e23d050a6d9aaff13605692333a048296a0e8945dc241a256eadbb79e4"))
            ( 1324900, uint256S("0x000505e8a3427bd01cb980d8b8c78125be7cc5e045a1fd4fa534c2ea5c5d3144"))
            ( 1364500, uint256S("0x0001cbed909e6f3acae5ee97bb7e25b952969db96819dbd98c03889753815efc"))
            ( 1405200, uint256S("0x00021862f286f715f7a0488873156ef355372f73b414fd95322c085da6d45360"))
            ( 1425300, uint256S("0x0005830d3cc95017da5f5ab2ce9846925f3c34ca7c60ea886cc09a6b97858c8d"))
            ( 1453200, uint256S("0x000311dd646c1e74902f56be31c241e37f9e452c774ea8a88729e9b25f4fe16c"))
            ( 1483500, uint256S("0x000654110f87f10f8638be34d85a52d4535dc4e6ae7ebd597a6977e212ebdd8b"))
            ( 1528500, uint256S("0x0006f8cd5b90d5dd8027123be8025d3e8ff5ff3e20ecbbd4482874ec2fdfb35d"))
            ( 1582300, uint256S("0x000f1341912640b8c68d9b6ae21983df52c23ecd69b00ed533d14aea820fb499"))
            ( 1636200, uint256S("0x00035bd39dec21ad02de6f06fbcf8cee8d7c3e9e9237252530dd00b22f814587")),
            1740379553,     // * UNIX timestamp of last checkpoint block
            2584653,        // * total number of transactions between genesis and last checkpoint
                            //   (the tx=... number in the SetBestChain debug.log lines)
            910             // * estimated number of transactions per day after checkpoint
                            //   total number of tx / (checkpoint block height / (24 * 24))
        };

//  commented out - seems to make no sense but kept around for reference just in case
//        assert(vCommunityFundAddress.size() <= consensus.GetLastCommunityRewardBlockHeight());
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        strCurrencyUnits = "REG";
        consensus.nSubsidySlowStartInterval = 0;
        consensus.nSubsidyHalvingInterval = 2000;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.powLimit = uint256S("0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f");
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 0; // Turn off adjustment down
        consensus.nPowMaxAdjustUp = 0; // Turn off adjustment up

        pchMessageStart[0] = 0x2f;
        pchMessageStart[1] = 0x54;
        pchMessageStart[2] = 0xcc;
        pchMessageStart[3] = 0x9d;
//        nMinerThreads = 1;
        nMaxTipAge = 24 * 60 * 60;
        const size_t N = 48, K = 5;
        BOOST_STATIC_ASSERT(equihash_parameters_acceptable(N, K));
        nEquihashN = N;
        nEquihashK = K;
        genesis.hashPrevBlock.SetNull();
        genesis.nTime = 1494548150;
        genesis.nBits = 0x200f0f0f;
        genesis.nVersion = 4;
        genesis.nNonce = uint256S("0x000000000000000000000000000000000000000000000000000000000000003d");
        genesis.nSolution = ParseHex("00CBA7185285F4FF37432E1F3AA7A569FBC81B5A0876F23DA8D38840B0130C74E68297B5");
        consensus.hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19133;
        assert(consensus.hashGenesisBlock == uint256S("0x0da5ee723b7923feb580518541c6f098206330dbc711a6678922c11f2ccf1abb"));

        nPruneAfterHeight = 1000;

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        //fRequireStandard = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nCbhMinimumAge = 99;
        nCbhSafeDepth = 320;
        nScCoinsMaturity = 3;
        nScNumBlocksForScFeeCheck = 10;
        nScMinWithdrawalEpochLength = 2;
        nScMaxWithdrawalEpochLength = 4032;
        nScMaxNumberOfCswInputsInMempool = 5;

        checkpointData = (Checkpoints::CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x0da5ee723b7923feb580518541c6f098206330dbc711a6678922c11f2ccf1abb")),
            0,
            0,
            0
        };

//  commented out - seems to make no sense but kept around for reference just in case
//        assert(vCommunityFundAddress.size() <= consensus.GetLastCommunityRewardBlockHeight());
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
    ForkManager::getInstance().selectNetwork(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}

int64_t CChainParams::MaxTipAge() const {
    if ( Params().NetworkIDString() == "regtest" )
    {
        return GetArg("-maxtipage", nMaxTipAge);
    }
    
    return nMaxTipAge;
}

// Block height must be >0 and <=last CF reward block height (note that after hfCommunityFundHeight hard fork CF reward is permanent)
// Index variable i ranges from 0 - (vCommunityFundAddress.size()-1)
std::string CChainParams::GetCommunityFundAddressAtHeight(int nHeight , Fork::CommunityFundType cfType) const {
    return ForkManager::getInstance().getCommunityFundAddress(nHeight,consensus._deprecatedGetLastCommunityRewardBlockHeight(), cfType);
}

// The community fund address is expected to be a multisig (P2SH) address
CScript CChainParams::GetCommunityFundScriptAtHeight(int nHeight, Fork::CommunityFundType cfType) const {
    assert(nHeight > 0);

    CBitcoinAddress address(GetCommunityFundAddressAtHeight(nHeight, cfType).c_str());
    assert(address.IsValid());
    assert(address.IsScript());
    CScriptID scriptID = get<CScriptID>(address.Get()); // Get() returns a boost variant
    CScript script = CScript() << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
    return script;
}
