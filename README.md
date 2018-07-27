Srcchain Core integration/staging tree
=====================================

[![Build Status](https://travis-ci.org/srcchain/srcchain.svg?branch=master)](https://travis-ci.org/srcchain/srcchain)

https://srcchaincore.org

What is Srcchain?
----------------

Srcchain is an experimental digital currency that enables instant payments to
anyone, anywhere in the world. Srcchain uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. Srcchain Core is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the Srcchain Core software, see https://srcchain.org/en/download, or read the
[original whitepaper](https://srcchaincore.org/srcchain.pdf).

License
-------

Srcchain Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/srcchain/srcchain/tags) are created
regularly to indicate new official, stable release versions of Srcchain Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

The developer [mailing list](https://lists.linuxfoundation.org/mailman/listinfo/srcchain-dev)
should be used to discuss complicated or controversial changes before working
on a patch set.

Developer IRC can be found on Freenode at #srcchain-core-dev.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

Translations
------------

Changes to translations as well as new translations can be submitted to
[Srcchain Core's Transifex page](https://www.transifex.com/projects/p/srcchain/).

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.

Translators should also subscribe to the [mailing list](https://groups.google.com/forum/#!forum/srcchain-translators).

Documentation
-------------------------
For more information, [Please visit here.](http://genyuanlian-docs.readthedocs.io "genyuanlian-docs")

Contact Developers
-------------------------

Developers are available at:

| Label Name              | Description                                                                                                                                                                                                                                                               |
| :---------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Gitter                  | [![Join the chat at https://gitter.im/genyuanlian-SourceBlockchain/Lobby](https://badges.gitter.im/genyuanlian-SourceBlockchain/Lobby.svg)](https://gitter.im/genyuanlian-SourceBlockchain/Lobby?utm_source=share-link&utm_medium=link&utm_campaign=share-link) |

Issues & PRs management
-------------------------
[![Waffle.io - Columns and their card count](https://badge.waffle.io/GenYuanLian/SourceChain.svg?columns=all)](https://waffle.io/GenYuanLian/SourceChain)              

[![Throughput Graph](https://graphs.waffle.io/GenYuanLian/SourceChain/throughput.svg)](https://waffle.io/GenYuanLian/SourceChain/metrics/throughput) 

LICENSE
-------------------------
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
