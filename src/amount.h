// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SRCCHAIN_AMOUNT_H
#define SRCCHAIN_AMOUNT_H

#include <stdint.h>

/** Amount in satoshis (Can be negative) */
typedef int64_t CAmount;

static const CAmount COIN = 100000000;
static const CAmount CENT = 1000000;

/** No amount larger than this (in satoshi) is valid.
 *
 * Note that this constant is *not* the total money supply, which in Srcchain
 * currently happens to be less than 21,000,000 STK for various reasons, but
 * rather a sanity check. As this sanity check is used by consensus-critical
 * validation code, the exact value of the MAX_MONEY constant is consensus
 * critical; in unusual circumstances like a(nother) overflow bug that allowed
 * for the creation of coins out of thin air modification could lead to a fork.
 * */
static const CAmount MAX_MONEY = 21000000000 * COIN;
inline bool MoneyRange(const CAmount& nValue) { return (nValue >= 0 && nValue <= MAX_MONEY); }

static const int64_t GENESIS_BASE_ALLOC = 6300000000;	//巨额基础预分配; 单位 COIN

#endif //  SRCCHAIN_AMOUNT_H
