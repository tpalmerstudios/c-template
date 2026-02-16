#!/bin/bash

echo "Post Installation Script"
PWD="${PWD%/}"
echo "${PWD##*/}"

cmake -G Ninja -B build --log-level=ERROR || exit 1
ninja dev_build -C build || exit 1
rm -rf build/*

cmake -B build --log-level=ERROR || exit 1
cd build || exit 1
make -s dev_build || exit 1

cd ..
rm -rf build/
rm -rf docs/
