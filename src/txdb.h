// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SRCCHAIN_TXDB_H
#define SRCCHAIN_TXDB_H

#include "coins.h"
#include "dbwrapper.h"
#include "chain.h"

#include <map>
#include <string>
#include <utility>
#include <vector>
#include "spentindex.h" //added for bitpay

class CBlockIndex;
class CCoinsViewDBCursor;
class uint256;

//added for bitpay start
struct CAddressUnspentKey;
struct CAddressUnspentValue;
struct CAddressIndexKey;
struct CAddressIndexIteratorKey;
struct CAddressIndexIteratorHeightKey;
struct CTimestampIndexKey;
struct CTimestampIndexIteratorKey;
struct CTimestampBlockIndexKey;
struct CTimestampBlockIndexValue;
struct CSpentIndexKey;
struct CSpentIndexValue;
//added for bitpay end

//! No need to periodic flush if at least this much space still available.
static constexpr int MAX_BLOCK_COINSDB_USAGE = 10;
//! -dbcache default (MiB)
static const int64_t nDefaultDbCache = 450;
//! -dbbatchsize default (bytes)
static const int64_t nDefaultDbBatchSize = 16 << 20;
//! max. -dbcache (MiB)
static const int64_t nMaxDbCache = sizeof(void*) > 4 ? 16384 : 1024;
//! min. -dbcache (MiB)
static const int64_t nMinDbCache = 4;
//! Max memory allocated to block tree DB specific cache, if no -txindex (MiB)
static const int64_t nMaxBlockDBCache = 2;
//! Max memory allocated to block tree DB specific cache, if -txindex (MiB)
// Unlike for the UTXO database, for the txindex scenario the leveldb cache make
// a meaningful difference: https://github.com/srcchain/srcchain/pull/8273#issuecomment-229601991
static const int64_t nMaxBlockDBAndTxIndexCache = 1024;
//! Max memory allocated to coin DB specific cache (MiB)
static const int64_t nMaxCoinsDBCache = 8;

//added for bitpay start

struct CTimestampIndexIteratorKey {
    unsigned int timestamp;

    size_t GetSerializeSize(int nType, int nVersion) const {
        return 4;
    }
    template<typename Stream>
//    void Serialize(Stream& s, int nType, int nVersion) const {
    void Serialize(Stream& s) const {
        ser_writedata32be(s, timestamp);
    }
    template<typename Stream>
//    void Unserialize(Stream& s, int nType, int nVersion) {
    void Unserialize(Stream& s) {
        timestamp = ser_readdata32be(s);
    }

    CTimestampIndexIteratorKey(unsigned int time) {
        timestamp = time;
    }

    CTimestampIndexIteratorKey() {
        SetNull();
    }

    void SetNull() {
        timestamp = 0;
    }
};

struct CTimestampIndexKey {
    unsigned int timestamp;
    uint256 blockHash;

//    size_t GetSerializeSize(int nType, int nVersion) const {
    size_t GetSerializeSize() const {
        return 36;
    }
    template<typename Stream>
//    void Serialize(Stream& s, int nType, int nVersion) const {
    void Serialize(Stream& s) const {
        ser_writedata32be(s, timestamp);
//        blockHash.Serialize(s, nType, nVersion);
        blockHash.Serialize(s);
    }
    template<typename Stream>
//    void Unserialize(Stream& s, int nType, int nVersion) {
    void Unserialize(Stream& s) {
        timestamp = ser_readdata32be(s);
//        blockHash.Unserialize(s, nType, nVersion);
        blockHash.Unserialize(s);
    }

    CTimestampIndexKey(unsigned int time, uint256 hash) {
        timestamp = time;
        blockHash = hash;
    }

    CTimestampIndexKey() {
        SetNull();
    }

    void SetNull() {
        timestamp = 0;
        blockHash.SetNull();
    }
};

struct CTimestampBlockIndexKey {
    uint256 blockHash;

//    size_t GetSerializeSize(int nType, int nVersion) const {
    size_t GetSerializeSize() const {
        return 32;
    }

    template<typename Stream>
//    void Serialize(Stream& s, int nType, int nVersion) const {
    void Serialize(Stream& s) const {
//        blockHash.Serialize(s, nType, nVersion);
        blockHash.Serialize(s);
    }

    template<typename Stream>
//    void Unserialize(Stream& s, int nType, int nVersion) {
    void Unserialize(Stream& s) {
//        blockHash.Unserialize(s, nType, nVersion);
        blockHash.Unserialize(s);
    }

    CTimestampBlockIndexKey(uint256 hash) {
        blockHash = hash;
    }

    CTimestampBlockIndexKey() {
        SetNull();
    }

    void SetNull() {
        blockHash.SetNull();
    }
};

struct CTimestampBlockIndexValue {
    unsigned int ltimestamp;
//    size_t GetSerializeSize(int nType, int nVersion) const {
    size_t GetSerializeSize() const {
        return 4;
    }

    template<typename Stream>
//    void Serialize(Stream& s, int nType, int nVersion) const {
    void Serialize(Stream& s) const {
        ser_writedata32be(s, ltimestamp);
    }

    template<typename Stream>
//    void Unserialize(Stream& s, int nType, int nVersion) {
    void Unserialize(Stream& s) {
        ltimestamp = ser_readdata32be(s);
    }

    CTimestampBlockIndexValue (unsigned int time) {
        ltimestamp = time;
    }

    CTimestampBlockIndexValue() {
        SetNull();
    }

    void SetNull() {
        ltimestamp = 0;
    }
};

struct CAddressUnspentKey {
    unsigned int type;
    uint160 hashBytes;
    uint256 txhash;
    size_t index;

//    size_t GetSerializeSize(int nType, int nVersion) const {
    size_t GetSerializeSize() const {
        return 57;
    }
    template<typename Stream>
//    void Serialize(Stream& s, int nType, int nVersion) const {
    void Serialize(Stream& s) const {
        ser_writedata8(s, type);
//        hashBytes.Serialize(s, nType, nVersion);
        hashBytes.Serialize(s);
//        txhash.Serialize(s, nType, nVersion);
        txhash.Serialize(s);
        ser_writedata32(s, index);
    }
    template<typename Stream>
//    void Unserialize(Stream& s, int nType, int nVersion) {
    void Unserialize(Stream& s) {
        type = ser_readdata8(s);
//        hashBytes.Unserialize(s, nType, nVersion);
        hashBytes.Unserialize(s);
//        txhash.Unserialize(s, nType, nVersion);
        txhash.Unserialize(s);
        index = ser_readdata32(s);
    }

    CAddressUnspentKey(unsigned int addressType, uint160 addressHash, uint256 txid, size_t indexValue) {
        type = addressType;
        hashBytes = addressHash;
        txhash = txid;
        index = indexValue;
    }

    CAddressUnspentKey() {
        SetNull();
    }

    void SetNull() {
        type = 0;
        hashBytes.SetNull();
        txhash.SetNull();
        index = 0;
    }
};

struct CAddressUnspentValue {
    CAmount satoshis;
    CScript script;
    int blockHeight;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
//    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(satoshis);
        READWRITE(*(CScriptBase*)(&script));
        READWRITE(blockHeight);
    }

    CAddressUnspentValue(CAmount sats, CScript scriptPubKey, int height) {
        satoshis = sats;
        script = scriptPubKey;
        blockHeight = height;
    }

    CAddressUnspentValue() {
        SetNull();
    }

    void SetNull() {
        satoshis = -1;
        script.clear();
        blockHeight = 0;
    }

    bool IsNull() const {
        return (satoshis == -1);
    }
};

struct CAddressIndexKey {
    unsigned int type;
    uint160 hashBytes;
    int blockHeight;
    unsigned int txindex;
    uint256 txhash;
    size_t index;
    bool spending;

//    size_t GetSerializeSize(int nType, int nVersion) const {
    size_t GetSerializeSize() const {
        return 66;
    }
    template<typename Stream>
//    void Serialize(Stream& s, int nType, int nVersion) const {
    void Serialize(Stream& s) const {
        ser_writedata8(s, type);
//        hashBytes.Serialize(s, nType, nVersion);
        hashBytes.Serialize(s);
        // Heights are stored big-endian for key sorting in LevelDB
        ser_writedata32be(s, blockHeight);
        ser_writedata32be(s, txindex);
//        txhash.Serialize(s, nType, nVersion);
        txhash.Serialize(s);
        ser_writedata32(s, index);
        char f = spending;
        ser_writedata8(s, f);
    }
    template<typename Stream>
//    void Unserialize(Stream& s, int nType, int nVersion) {
    void Unserialize(Stream& s) {
        type = ser_readdata8(s);
//        hashBytes.Unserialize(s, nType, nVersion);
        hashBytes.Unserialize(s);
        blockHeight = ser_readdata32be(s);
        txindex = ser_readdata32be(s);
//        txhash.Unserialize(s, nType, nVersion);
        txhash.Unserialize(s);
        index = ser_readdata32(s);
        char f = ser_readdata8(s);
        spending = f;
    }

    CAddressIndexKey(unsigned int addressType, uint160 addressHash, int height, int blockindex,
                     uint256 txid, size_t indexValue, bool isSpending) {
        type = addressType;
        hashBytes = addressHash;
        blockHeight = height;
        txindex = blockindex;
        txhash = txid;
        index = indexValue;
        spending = isSpending;
    }

    CAddressIndexKey() {
        SetNull();
    }

    void SetNull() {
        type = 0;
        hashBytes.SetNull();
        blockHeight = 0;
        txindex = 0;
        txhash.SetNull();
        index = 0;
        spending = false;
    }

};

struct CAddressIndexIteratorKey {
    unsigned int type;
    uint160 hashBytes;

//    size_t GetSerializeSize(int nType, int nVersion) const {
    size_t GetSerializeSize() const {
        return 21;
    }
    template<typename Stream>
//    void Serialize(Stream& s, int nType, int nVersion) const {
    void Serialize(Stream& s) const {
        ser_writedata8(s, type);
//        hashBytes.Serialize(s, nType, nVersion);
        hashBytes.Serialize(s);
    }
    template<typename Stream>
//    void Unserialize(Stream& s, int nType, int nVersion) {
    void Unserialize(Stream& s) {
        type = ser_readdata8(s);
//        hashBytes.Unserialize(s, nType, nVersion);
        hashBytes.Unserialize(s);
    }

    CAddressIndexIteratorKey(unsigned int addressType, uint160 addressHash) {
        type = addressType;
        hashBytes = addressHash;
    }

    CAddressIndexIteratorKey() {
        SetNull();
    }

    void SetNull() {
        type = 0;
        hashBytes.SetNull();
    }
};

struct CAddressIndexIteratorHeightKey {
    unsigned int type;
    uint160 hashBytes;
    int blockHeight;

//    size_t GetSerializeSize(int nType, int nVersion) const {
    size_t GetSerializeSize() const {
        return 25;
    }
    template<typename Stream>
//    void Serialize(Stream& s, int nType, int nVersion) const {
    void Serialize(Stream& s) const {
        ser_writedata8(s, type);
//        hashBytes.Serialize(s, nType, nVersion);
        hashBytes.Serialize(s);
        ser_writedata32be(s, blockHeight);
    }
    template<typename Stream>
//    void Unserialize(Stream& s, int nType, int nVersion) {
    void Unserialize(Stream& s) {
        type = ser_readdata8(s);
//        hashBytes.Unserialize(s, nType, nVersion);
        hashBytes.Unserialize(s);
        blockHeight = ser_readdata32be(s);
    }

    CAddressIndexIteratorHeightKey(unsigned int addressType, uint160 addressHash, int height) {
        type = addressType;
        hashBytes = addressHash;
        blockHeight = height;
    }

    CAddressIndexIteratorHeightKey() {
        SetNull();
    }

    void SetNull() {
        type = 0;
        hashBytes.SetNull();
        blockHeight = 0;
    }
};

//added for bitpay end

struct CDiskTxPos : public CDiskBlockPos
{
    unsigned int nTxOffset; // after header

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action) {
        READWRITE(*(CDiskBlockPos*)this);
        READWRITE(VARINT(nTxOffset));
    }

    CDiskTxPos(const CDiskBlockPos &blockIn, unsigned int nTxOffsetIn) : CDiskBlockPos(blockIn.nFile, blockIn.nPos), nTxOffset(nTxOffsetIn) {
    }

    CDiskTxPos() {
        SetNull();
    }

    void SetNull() {
        CDiskBlockPos::SetNull();
        nTxOffset = 0;
    }
};

/** CCoinsView backed by the coin database (chainstate/) */
class CCoinsViewDB : public CCoinsView
{
protected:
    CDBWrapper db;
public:
    CCoinsViewDB(size_t nCacheSize, bool fMemory = false, bool fWipe = false);

    bool GetCoin(const COutPoint &outpoint, Coin &coin) const override;
    bool HaveCoin(const COutPoint &outpoint) const override;
    uint256 GetBestBlock() const override;
    std::vector<uint256> GetHeadBlocks() const override;
    bool BatchWrite(CCoinsMap &mapCoins, const uint256 &hashBlock) override;
    CCoinsViewCursor *Cursor() const override;

    //! Attempt to update from an older database format. Returns whether an error occurred.
    bool Upgrade();
    size_t EstimateSize() const override;
};

/** Specialization of CCoinsViewCursor to iterate over a CCoinsViewDB */
class CCoinsViewDBCursor: public CCoinsViewCursor
{
public:
    ~CCoinsViewDBCursor() {}

    bool GetKey(COutPoint &key) const override;
    bool GetValue(Coin &coin) const override;
    unsigned int GetValueSize() const override;

    bool Valid() const override;
    void Next() override;

private:
    CCoinsViewDBCursor(CDBIterator* pcursorIn, const uint256 &hashBlockIn):
        CCoinsViewCursor(hashBlockIn), pcursor(pcursorIn) {}
    std::unique_ptr<CDBIterator> pcursor;
    std::pair<char, COutPoint> keyTmp;

    friend class CCoinsViewDB;
};

/** Access to the block database (blocks/index/) */
class CBlockTreeDB : public CDBWrapper
{
public:
    CBlockTreeDB(size_t nCacheSize, bool fMemory = false, bool fWipe = false, bool compression = true, int maxOpenFiles = 1000);//added for bitpay
private:
    CBlockTreeDB(const CBlockTreeDB&);
    void operator=(const CBlockTreeDB&);
public:
    bool WriteBatchSync(const std::vector<std::pair<int, const CBlockFileInfo*> >& fileInfo, int nLastFile, const std::vector<const CBlockIndex*>& blockinfo);
    bool ReadBlockFileInfo(int nFile, CBlockFileInfo &fileinfo);
    bool ReadLastBlockFile(int &nFile);
    bool WriteReindexing(bool fReindex);
    bool ReadReindexing(bool &fReindex);
    bool ReadTxIndex(const uint256 &txid, CDiskTxPos &pos);
    bool WriteTxIndex(const std::vector<std::pair<uint256, CDiskTxPos> > &list);

    //added for bitpay start
    bool ReadSpentIndex(CSpentIndexKey &key, CSpentIndexValue &value);
    bool UpdateSpentIndex(const std::vector<std::pair<CSpentIndexKey, CSpentIndexValue> >&vect);
    bool UpdateAddressUnspentIndex(const std::vector<std::pair<CAddressUnspentKey, CAddressUnspentValue > >&vect);
    bool ReadAddressUnspentIndex(uint160 addressHash, int type,
                                 std::vector<std::pair<CAddressUnspentKey, CAddressUnspentValue> > &vect);
    bool WriteAddressIndex(const std::vector<std::pair<CAddressIndexKey, CAmount> > &vect);
    bool EraseAddressIndex(const std::vector<std::pair<CAddressIndexKey, CAmount> > &vect);
    bool ReadAddressIndex(uint160 addressHash, int type,
                          std::vector<std::pair<CAddressIndexKey, CAmount> > &addressIndex,
                          int start = 0, int end = 0);
    bool WriteTimestampIndex(const CTimestampIndexKey &timestampIndex);
    bool ReadTimestampIndex(const unsigned int &high, const unsigned int &low, const bool fActiveOnly, std::vector<std::pair<uint256, unsigned int> > &vect);
    bool WriteTimestampBlockIndex(const CTimestampBlockIndexKey &blockhashIndex, const CTimestampBlockIndexValue &logicalts);
    bool ReadTimestampBlockIndex(const uint256 &hash, unsigned int &logicalTS);
    //added for bitpay end

    bool WriteFlag(const std::string &name, bool fValue);
    bool ReadFlag(const std::string &name, bool &fValue);
    bool LoadBlockIndexGuts(const Consensus::Params& consensusParams, std::function<CBlockIndex*(const uint256&)> insertBlockIndex);
    bool blockOnchainActive(const uint256 &hash);//added for bitpay
};

#endif // SRCCHAIN_TXDB_H
