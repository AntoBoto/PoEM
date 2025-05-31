# PoEM (BrrrFren) Development Guide

This document describes key development practices and design decisions for the PoEM (BrrrFren) Core project.

## Build System

### Dual-Binary Approach

PoEM Core uses a dual-binary approach during its development and transition phase:

1. **Internal Build System**:
   - Both legacy `dogecoin*` binaries (`dogecoind`, `dogecoin-cli`, `dogecoin-tx`) and new `poem*` binaries (`poemd`, `poem-cli`, `poem-tx`) are built by the build system
   - This ensures backward compatibility with tests and build scripts that expect the old binary names
   - The codebase maintains both sets of binaries to avoid breaking changes during the transition

2. **Release Packaging**:
   - Only the new `poem*` binaries are included in release packages
   - The CI/CD process filters out old binary names during the packaging step
   - End users only receive the new PoEM binaries

This approach allows us to:
- Maintain a stable build environment
- Keep all tests passing during transition
- Gradually migrate to new binary names
- Ship clean releases with only the new branding

### Implementation Details

The dual-binary approach is implemented through:

1. **Makefile.am**:
   - Defines targets for both sets of binaries
   - Links both to the same underlying code

2. **CI/CD Pipeline**:
   - GitHub Actions workflow builds both sets of binaries
   - Filters out old binaries during packaging
   - Creates release archives with only PoEM binaries

## Release Process

1. **Creating a Release**:
   - Create and push a tag (e.g., `git tag -a v2.0.4 -m "Release v2.0.4"`)
   - Push the tag to GitHub (`git push origin v2.0.4`)
   - GitHub Actions workflow will automatically:
     - Build binaries for all platforms
     - Filter out legacy binaries
     - Create a GitHub Release with the PoEM binaries

2. **Release Versioning**:
   - PoEM follows semantic versioning
   - Version format: `vMAJOR.MINOR.PATCH`
   - Example: `v2.0.4`

## Future Considerations

1. **Complete Migration**:
   - Eventually, the dual-binary approach will be phased out
   - References to Dogecoin will be removed from the codebase
   - Only PoEM binaries will be built

2. **Documentation Updates**:
   - Documentation will be gradually updated to reflect the new branding
   - User-facing documentation should already refer only to PoEM

## Security Considerations

1. **Private Keys and Credentials**:
   - Never commit private keys (e.g., `.pem` files) to the repository
   - `.gitignore` has been updated to exclude `.pem` files
   - Any sensitive credentials have been removed from the repository history
