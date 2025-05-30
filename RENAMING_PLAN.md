# PoEM (formerly BrrrFren) Renaming Plan

## Current Status
- Successfully renamed repository from BrrrFren to PoEM (Poetic Expression on the Blockchain)
- Updated build system to handle both old (dogecoin/brrrfren) and new (poem) binary names
- Set up GitHub Actions for automated builds
- Resolved C++ standard library and Boost compatibility issues

## Build System Changes

### Build Configuration
- Using Ubuntu 22.04 as the build environment
- Standard system compiler (GCC 11) with C++11 compatibility
- Static linking for better binary distribution
- Disabled components: wallet, ZMQ, tests, benchmarks

### Dependencies
- Boost 1.74+ (system, filesystem, thread, chrono, program_options, test)
- OpenSSL
- Berkeley DB 4.8+ (with incompatible BDB flag)
- Other standard build tools

### Binary Naming
- Main daemon: `poemd`
- CLI: `poem-cli`
- Transaction tool: `poem-tx`
- Qt GUI: `poem-qt` (currently disabled in build)

## Remaining Tasks

### High Priority
1. Verify binary compatibility across different Linux distributions
2. Test network functionality with existing nodes (if any)
3. Update documentation and README

### Medium Priority
1. Re-enable wallet functionality after core build is stable
2. Add Windows build support
3. Set up automated releases

### Low Priority
1. Re-enable Qt GUI wallet
2. Add test suite
3. Set up code coverage reporting

## Known Issues
1. Some build warnings related to Boost compatibility
2. Need to verify network protocol compatibility
3. May need additional runtime testing for edge cases

## Build Instructions
```bash
./autogen.sh
./configure --enable-static --disable-shared --with-pic --with-incompatible-bdb --with-qt=no
make -j$(nproc)
```

## Verification
After building, verify the following:
1. `src/poemd --version` shows correct version
2. Basic RPC commands work: `src/poem-cli getblockchaininfo`
3. Network connectivity (if network is available)

## Rollback Plan
If issues are found:
1. Revert to previous working commit
2. Switch back to old binary names if needed
3. Update build configuration accordingly

## Contact
For questions or issues, please refer to the project's GitHub repository.
