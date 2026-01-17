# Changelog for C-Template
All notable changes to my C Template Generator will be documented here.

---

## [0.1.0] - 2026-01-10
### Added
- Initial project structure
- CMake build system
- Formatting target (`clang-format`)
- Doxygen support
- CONTRIBUTING guide

## [1.0.0] - 2026-01-11
### Added
- Add in various Project Variables
- Tested with ninja
- Create `template-config.sh` for faster template renaming

## [1.1.0] - 2026-01-11
### Added
- Fix license separation
- Run ninja and make and tests the output

## [1.2.0] - 2026-01-11
### Added
- Automate the naming of proj_upper to replace spaces with underscore and remove special characters and move to upper case
- Validate input

## [1.2.1] - 2026-01-11
### Added
- Update this log

## [1.3.0] - 2026-01-11
### Added
- Add a debug target with debug macros

## [1.3.3] - 2026-01-12
### Added
- Fixed README.md and separated child meta files from parent meta files
- Fixed LICENSE for final time hopefully
- Added local formatting tooling `shfmt`

## [1.4.0] - 2026-01-15
### Added
- Added `--help` flags - Outputs help info
- Added `--force` flags - Forces using a directory even if it exists
- Added `--remove` flags - Removes an existing directory before using it
- Added `--no-git` flags - Skips all git commands
- Added `--version` flags - Outputs version and license info

## [1.4.2] - 2026-01-15
### Added
- Fixed README format
- Organized meta files more effectively

## [1.5.0] - 2026-01-16
### Added
- Added Flags to the C Program (needs work)

---

## Planned for [1.3+]
### To Do
- Add basic unit tests to the C files
- Integrate `version.h` into build output and into github possibly
- Test with meson-buid

