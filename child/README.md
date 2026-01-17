# 01PROJTEMP
01PROJDESC

--------------

## Quick Start
Fork and rename
Find and replace all variables Update the readme and the changelog
~~Remove the install srcipt~~

### Linux Install
```bash
cmake -B build
cd build/
make 01PROJCMD
./01PROJCMD --flags
```

### Basic Usage
| Flag | Values | Description |
|------|--------|-------------|
| `--testing` |  | Run 01PROJTEMP in testing mode |
| `-v` |  | output version information and exit |
| `-h` |  | output help information and exit |

## Installation

### Standard Installation
```bash
cmake -B build
cmake --build build
cd build
./01PROJCMD
```

- ### clang-format
The GNU Format is used by clang-format. And is automatically run by `make` when using either `build_all` or `clang-format` targets

- ### docs
Doxygen is used for Documentation. And is automatically run by `make` when using either `build_all` or `docs` targets.

- ### ~~check~~
~~ctest is the CMake tester. It is not implemented yet. And is automatically run by `make` when using either `build_all` or `check` targets.~~

- ### 01PROJCMD
01PROJCMD is the regular executable. And is automatically run by `make` when using either `build_all` or `prep` targets.

- ### Debug
`cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`

- ### ~~Windows~~
~~TO NOT DO~~

- ### ~~Other Platforms~~
~~TODO~~

---------

## Usage
| Flag | Values | Description |
|------|--------|-------------|
| `--testing` |  | Run 01PROJTEMP in testing mode |
| `-v` |  | output version information and exit |
| `-h` |  | output help information and exit |

Go into detail of all the configuration options as well as syntax of any commands.

## Dependencies
- Compiler like `gcc` or `clang`
- `cmake`
- `et cetera`

---------

## Contact
**obsoleteTiger@protonmail.com** is the best way to contact me.
In an emergency, try calling +1 911. *(/s)*

## License
*I love supporting the **[EFF](https://eff.org)**. Please donate to them if this program has been of any help*

Copyright &copy; 2026 [tpalmerstudios](mailto:obsoleteTiger@protonmail.com)

License GPLv3+: GNU GPL version 3 or later [https://gnu.org/licenses/gpl.html](https://gnu.org/licenses/gpl.html).
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Written by **tpalmerstudios**

