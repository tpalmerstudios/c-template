# Contributing Guide

Thanks for considering contributing to 01PROJTEMP

## How to Contribute

1. **Fork the Repository**: Click the "Fork" button at the top of the repository page to create your own fork.

2. **Clone Your Fork**: Clone your fork to your local machine and create a new branch for your changes.

3. **Coding Style**: Please use the GNU coding style. You can run the formatter with the CMake target (`make clang-format`) to ensure your code matches the style guidelines.

4. **Documentation**: All changes should be documented with Doxygen. Include any parameters, return values, a brief description, and inline logic descriptions when they aren't easily understood. (This means any spots where there's an intentional off by one of prefix `++` that is used as a value. Also any bitwise operations unless they are decribed in the function brief)

5. **Testing**: Add testing as possible. Speaking mostly to myself here.

6. **Make Changes and Commit**: Make your changes and commit them with clear, descriptive commit messages.

7. **Submit a Pull Request**: Once your changes are ready, push your branch and open a pull request. We'll review it as soon as we can!

## Code of Conduct

Be respectful. No name caling, no flaming. We're all here to learn and grow together.

