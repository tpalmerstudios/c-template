# C-Template
C-Template is a project made to save time in starting a new project. It uses a script to take the name of the project and a brief description and add that into Doxygen as well as creating and running  basic CMake setup. The key here is that it sets up a basic program structure and common targets to save time so you can focus on coding.

## Usage
Run the `./template-setup.sh` script and input a name for the project as well as a description.
> Some validation occurs, but I'd recommend not naming your project something that has a lot of special characters
> If you do, use a simplified version of the name that would be suitable in regular files and manually change it in the human readble locations.

That will generate a directory as a sibling to wherever the `c-template` package is.
A git repository will init and files with the new names and valued are copied.

| Flags | Description |
|---|---|
| `-v`,`--version`| output version information and exit |
| `-h`,`--help`,`help` | display this help and exit |
| `--no-git` | skips all setup related to git |
| `--force` | uses a direcotry even if it already exists. does NOT empty that folder |
| `--remove` | removes a directory COMPLETELY before creating the template files in that directory |

## Test Install
`cd ../proj-name` and run `./test-install.sh`
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
make build_all 

# Formats code
clang-format -i filename.c
```

## CMake Options
`-DCMAKE_BUILD_TYPE=Debug` for debug builds

---------------
## Internal Variables
I leave these because a user could adapt these to have more advanced projects or CMake targets that are dfferent than the single project name.
(Like I did with rabbithole. rabbit was a target, as was hole)

- **01PROJTEMP** Human readable project name

- **01PROJUPPER** is the name of the project used in the CMakeLists. It should be uppercase and not have any spaces

- **01PROJCMD** is the name of the executable file

- **01PROJDESC** Description of Stuff it does!

---------------

## Other things to change before starting
Change the new readme based on actual usage and installation

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

