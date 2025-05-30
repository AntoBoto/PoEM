# BrrrFren Core - Rename Progress

This document tracks the progress of renaming Dogecoin to BrrrFren in the codebase.

## Current Status (2025-05-30)

- Successfully reverted to working commit `18ac001` where the benchmark tool builds and runs correctly
- Benchmark tool (`bench_dogecoin`) is now functional
- Main binaries (`dogecoind`, `dogecoin-cli`, `dogecoin-tx`) build successfully

## Known Issues

- The build system still uses `dogecoin` in various places (filenames, variable names, etc.)
- Some test files and documentation still reference Dogecoin

## Next Steps

1. Continue renaming components from Dogecoin to BrrrFren
2. Update build system to use BrrrFren naming
3. Update documentation and test files
4. Ensure all tests pass after renaming

## Building

To build the project:

```bash
./autogen.sh
./configure --disable-wallet --with-incompatible-bdb
make -j$(nproc)
```

## Running Benchmarks

To run benchmarks:

```bash
src/bench/bench_dogecoin
```
