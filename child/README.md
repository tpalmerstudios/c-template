# 01PROJTEMP

01PROJDESC

---

### Install

```bash
cmake -B build
cd build/
make 01PROJCMD
./01PROJCMD --flags
```

### Basic Usage

| Flag        | Values | Description                         |
| ----------- | ------ | ----------------------------------- |
| `--testing` |        | Run 01PROJTEMP in testing mode      |
| `-v`        |        | output version information and exit |
| `-h`        |        | output help information and exit    |

## Installation

### Standard Installation

```bash
cmake -B build
cmake --build build
cd build
./01PROJCMD
```

### clang-format

The GNU Format is used by clang-format. And is automatically run by `make` when using either `dev_build` or `clang-format` targets
`clang-format -i fileName.ext` will also format the spcified file (tip: use \* and wildcards)

### docs

Doxygen is required for documentation. And is automatically run by `make` when using either `dev_build` or `docs` targets.
`doxygen Doxyfile` will also create documentation

### run-tests

ctest is the CMake tester. And is automatically run by `make` when using the `dev_build` target.
`ctest` when run from the `build/` directory will also run the generated tests if they have been generated

### 01PROJCMD

01PROJCMD is the regular executable. And is automatically run by `make` when using either `dev_build` or `01PROJCMD` targets.

### Debug

`cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug`

### ~~Windows~~

~~TO NOT DO~~

### ~~Other Platforms~~

~~TODO~~

---

## Usage

| Flag        | Values | Description                         |
| ----------- | ------ | ----------------------------------- |
| `--testing` |        | Run 01PROJTEMP in testing mode      |
| `-v`        |        | output version information and exit |
| `-h`        |        | output help information and exit    |

Go into detail of all the configuration options as well as syntax of any commands.

## Dependencies

- Compiler like `gcc` or `clang`
- `cmake`

---

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
