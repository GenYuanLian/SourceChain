Shared Libraries
================

## srcchainconsensus

The purpose of this library is to make the verification functionality that is critical to Srcchain's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `srcchainconsensus.h` located in  `src/script/srcchainconsensus.h`.

#### Version

`srcchainconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`srcchainconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `srcchainconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `srcchainconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `srcchainconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/srcchain/bips/blob/master/bip-0016.mediawiki)) subscripts
- `srcchainconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/srcchain/bips/blob/master/bip-0066.mediawiki)) compliance
- `srcchainconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/srcchain/bips/blob/master/bip-0147.mediawiki))
- `srcchainconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/srcchain/bips/blob/master/bip-0065.mediawiki))
- `srcchainconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/srcchain/bips/blob/master/bip-0112.mediawiki))
- `srcchainconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/srcchain/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `srcchainconsensus_ERR_OK` - No errors with input parameters *(see the return value of `srcchainconsensus_verify_script` for the verification status)*
- `srcchainconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `srcchainconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `srcchainconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `srcchainconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NSrcchain](https://github.com/NicolasDorier/NSrcchain/blob/master/NSrcchain/Script.cs#L814) (.NET Bindings)
- [node-libsrcchainconsensus](https://github.com/bitpay/node-libsrcchainconsensus) (Node.js Bindings)
- [java-libsrcchainconsensus](https://github.com/dexX7/java-libsrcchainconsensus) (Java Bindings)
- [srcchainconsensus-php](https://github.com/Bit-Wasp/srcchainconsensus-php) (PHP Bindings)
