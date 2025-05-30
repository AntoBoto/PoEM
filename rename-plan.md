# Binary Rename Plan: dogecoin-* → poem-*

> **Note:** Translation pages and foreign language documentation will remain unchanged.

## Completed ✅
1. **Core Files**
   - Updated `src/Makefile.am` with new binary names and paths
   - Updated `init/README.md` with new service names
   - Updated `configure.ac` with new package metadata and version info
   - Updated `Makefile.am` with new package names and OSX app names
   - Renamed source files from `bitcoin*` to `poem*` (bitcoind.cpp → poemd.cpp, etc.)
   - Updated all references in source code to use new names

2. **Documentation**
   - Updated `README.md` with PoEM branding and information
   - Updated `INSTALL.md` with PoEM-specific installation instructions
   - Updated `doc/README.md` with PoEM documentation
   - Created `doc/release-notes/release-notes-2.0.0.md` for the new version

3. **Build System**
   - Updated build configuration and include paths
   - Renamed configuration headers and variables
   - Updated library and binary names
   - Configured build with `--disable-wallet --disable-tests --disable-bench`

4. **Dependencies**
   - Installed required build dependencies
   - Set up build environment with necessary compilers and tools
   - Attempted to build using the depends system (incomplete)

## Build Issues Encountered 🚧
1. **Dependency Build**
   - The `make -C depends` command was attempted but encountered issues
   - Switched to using system Boost libraries (version 1.74.0)
   - Installed GCC-10 for better compatibility

2. **Compilation Errors**
   - Encountered Boost.Signals2 compatibility issues with C++ standard library
   - Attempted builds with different configurations:
     - Standard configuration with wallet and GUI disabled
     - Minimal configuration with most features disabled
     - Using system Boost libraries instead of bundled ones
   - Error persists in `init.cpp` related to `std::basic_ostream` and Boost.Signals2

3. **Current Environment**
   - System: Linux
   - Compiler: GCC-10 (attempted with both GCC-11 and GCC-10)
   - Boost Version: 1.74.0
   - C++ Standard: C++17
   - Configure flags used:
     - `--disable-wallet --without-gui --without-miniupnpc --disable-tests --disable-bench`
     - `--with-boost-libdir=/usr/lib/x86_64-linux-gnu --with-boost=/usr`
     - `CXXFLAGS="-g -O2 -std=c++17"`

## Next Steps ⏳
1. **Resolve Build Issues**
   - [ ] Try building with `-D_GLIBCXX_USE_CXX11_ABI=0` flag
   - [ ] Consider patching Boost.Signals2 compatibility
   - [ ] Try building with older Boost version (1.71.0 or earlier)
   - [ ] Investigate if the issue is specific to the Ubuntu 22.04 environment
   
2. **Alternative Approaches**
   - [ ] Try building in a Docker container with Ubuntu 20.04
   - [ ] Consider using the depends system with specific Boost version
   - [ ] Look into using conan for dependency management

3. **Documentation Updates**
   - [ ] Document the build environment requirements
   - [ ] Update build instructions based on findings
   - [ ] Add troubleshooting section for common build issues

2. **Complete Build**
   - Successfully build the project with all dependencies
   - Verify all binaries are properly named and functional
   - Test basic functionality of built binaries

3. **Testing**
   - Update and run unit tests
   - Perform integration testing
   - Update CI/CD pipelines for the new build

4. **Packaging**
   - Create installers for different platforms
   - Update package metadata and descriptions
   - Prepare distribution files

5. **Documentation**
   - Update man pages (.1 files)
   - Update command-line help text
   - Finalize release notes

## Notes for Next Session
- Current working directory: `/home/v2/brrrfren-core`
- Last attempted build command:
  ```bash
  export CC=gcc-10 CXX=g++-10
  export CXXFLAGS="-g -O2 -std=c++17"
  ./autogen.sh
  ./configure --with-boost-libdir=/usr/lib/x86_64-linux-gnu \
              --with-boost=/usr \
              --disable-wallet \
              --without-gui \
              --without-miniupnpc \
              --disable-tests \
              --disable-bench
  make -j$(nproc)
  ```
- The main issue appears to be a compatibility problem between Boost.Signals2 and the C++ standard library implementation in GCC-10/11
- May need to modify the code to work around the Boost.Signals2 issues or update the build system to use a different concurrency model

## Testing
1. **Unit Tests**
   - Update test fixtures
   - Update test assertions
   - Update test data

2. **Integration Tests**
   - Update test scripts
   - Update CI/CD pipelines

## Verification
1. **Build Verification**
   - Verify all platforms build
   - Verify binary names
   - Verify library names

2. **Runtime Verification**
   - Verify service startup
   - Verify RPC calls
   - Verify CLI commands

## Rollback Plan
1. Revert to backup tag
2. Rebuild
3. Verify functionality
