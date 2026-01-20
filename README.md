# C-Template

C-Template is a project made to save time in starting a new project. It uses a script to take the name of the project and a brief description and add that into Doxygen as well as creating and running basic CMake setup.

Intended to set up a basic program structure and common targets to save time so you can focus on coding.

[![Super-Linter](https://github.com/tpalmerstudios/c-template/actions/workflows/super-linter.yml/badge.svg)](https://github.com/marketplace/actions/super-linter)
[![code style: prettier](https://img.shields.io/badge/code_style-prettier-ff69b4.svg?style=flat-square)](https://github.com/prettier/prettier)
![Build & Test](https://github.com/tpalmerstudios/c-template/actions/workflows/cmake-single-platform.yml/badge.svg)

## Usage

```bash
./template-setup.sh
```

Input a name for the project and a description.

> Some validation occurs, but I'd recommend not naming your project something that has a lot of special characters
> If you do, use a simplified version of the name that would be suitable in regular files and manually change it in the human readble locations.

That will generate a directory as a sibling to wherever the `c-template` package is or where you select when using the `--path` flag.
A Git repository will init and files with the new names and valued are copied.

| Flags                | Description                                                                         |
| -------------------- | ----------------------------------------------------------------------------------- |
| `-v`,`--version`     | output version information and exit                                                 |
| `-h`,`--help`,`help` | display this help and exit                                                          |
| `--no-git`           | skips all setup related to Git                                                      |
| `--force`            | uses a direcotry even if it already exists. does NOT empty that folder              |
| `--remove`           | removes a directory COMPLETELY before creating the template files in that directory |
| `--path PATH`        | sets a directory where the project will be installed under                          |

## Project Content

The generated project contains several targets and base files to build from.

1. Documentation (Doxygen)
2. Formatting and Linting (clang-format, shfmt)
   - `clang-format` is defined
   - `super-linter` is added as a GitHub Action
3. Testing (ctest)
   - Automated with GitHub Action
4. Issue Templates
5. Meta Files
   - README.md
   - LICENSE
   - CHANGELOG.md
   - CONTRIBUTING.md
6. Debug (target in CMake)
7. ~~Automatic Versioning~~

## Test Install

```bash
cd ../proj-name
./test-install.sh
```

This runs cmake with all targets including documentation.

## Dependencies

### Required

```bash
bash
```

### Optional

```bash
CMake
Doxygen
clang-format
gcc || clang
make
git
ninja
```

## Post Setup

I make the assumption you know how to run all of the dependencies, but here are the most vital

```bash
# From the directory of your new project

# generates documentation see: man doxygen
doxygen Doxyfile

# Runs all targets of cmake through ninja
cmake -G Ninja -B build
ninja -C build

# Runs all targets of cmake through make
cmake -B build
cd build
make dev_build

# Formats code
clang-format -i filename.c
```

## CMake Options

`-DCMAKE_BUILD_TYPE=Debug` for debug builds
`-DBUILD_TESTS=OFF` to turn off testing
`-DENABLE_WARNINGS=OFF` to disable compiler warnings

**NOTE**: The bottom two should be turned off for release builds.
I will be reworking those in CMake to have them set based on target or build type.

---

## Other things to change before programming

Change the meta files based on actual usage and installation

## Contact

**obsoleteTiger@protonmail.com** is the best way to contact me.
In an emergency, try calling +1 911. _(/s)_

## License

_I love supporting the **[EFF](https://eff.org)**. Please donate to them if this program has been of any help_

Copyright &copy; 2026 [tpalmerstudios](mailto:obsoleteTiger@protonmail.com)

License GPLv3+: GNU GPL version 3 or later [https://gnu.org/licenses/gpl.html](https://gnu.org/licenses/gpl.html).
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Written by **tpalmerstudios**
