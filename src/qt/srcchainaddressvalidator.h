// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SRCCHAIN_QT_SRCCHAINADDRESSVALIDATOR_H
#define SRCCHAIN_QT_SRCCHAINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class SrcchainAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SrcchainAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Srcchain address widget validator, checks for a valid srcchain address.
 */
class SrcchainAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit SrcchainAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // SRCCHAIN_QT_SRCCHAINADDRESSVALIDATOR_H
