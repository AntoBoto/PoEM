PoEM Core version 2.0.0 is now available from:

  <https://poem.technology/downloads/>

This is a new major version release, including new features, various bug fixes and
performance improvements, as well as updated translations.

Please report bugs using the issue tracker at GitHub:

  <https://github.com/poem/poem/issues>

How to Upgrade
=============

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the 
installer (on Windows) or just copy over `/usr/local/bin/poemd` and `/usr/local/bin/poem-qt` (on Linux).

Compatibility
============

PoEM Core is extensively tested on multiple operating systems using
the Linux kernel, macOS 10.10+, and Windows 7 and later. 32-bit versions of any
of these operating systems are not supported. PoEM Core should also work on most other Unix-like
systems but is not frequently tested on them.

From 2.0.0 onwards, it is required to use a Python version that is 3.6 or
greater.

Notable Changes
===============

### Major Changes in 2.0.0

- **Rebranding to PoEM Core**: Complete rebranding from BrrrFren Core to PoEM Core, including all binaries, configuration files, and user interfaces.
- **Updated Dependencies**: Upgraded to the latest versions of all dependencies for improved security and performance.
- **Improved Performance**: Various performance optimizations for faster block validation and transaction processing.
- **Enhanced Security**: Security improvements and bug fixes from upstream Bitcoin Core.
- **Updated User Interface**: Modernized user interface with PoEM branding and improved user experience.
- **Better Documentation**: Comprehensive documentation updates to reflect the new branding and features.

### Build System

- The build system has been updated to support the new PoEM branding.
- Minimum required compiler versions have been updated for better security and performance.

### RPC and Configuration

- All RPC commands and configuration options have been updated to use the new PoEM branding.
- New RPC commands and options have been added for better wallet and network management.

### Wallet

- Improved wallet performance and reliability.
- Better handling of transaction fees and coin selection.

### Network

- Improved peer-to-peer networking for better reliability and performance.
- Updated seed nodes for the PoEM network.

### GUI Changes

- Completely redesigned user interface with PoEM branding.
- Improved transaction creation and management.
- Better display of transaction details and wallet information.

Credits
=======

Thanks to everyone who directly contributed to this release:

- [List of contributors]

As well as everyone that helped translating on [Transifex](https://www.transifex.com/poem/poem/).

### Known Bugs

- [List any known issues]

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/doc/unit-tests.md](/doc/unit-tests.md).

There are also [regression and integration tests](/test/README.md) of the RPC interface, written
in Python, that are run automatically on the build server. These tests can be run (if the
test dependencies are installed) with: `test/functional/test_runner.py`

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.
