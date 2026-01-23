#!/bin/bash

echo "This should be run after the basic $(git init) and copy of the files to the proper directory"

echo "${PWD##*/}"

read -r -p "Type the project name. Must match the Current Directory: " input_dir

if [[ "$input_dir" != "${PWD##*/}" ]]; then
	echo "Wrong Directory! Exiting"
	exit 1
fi

cmake -G Ninja -B build --log-level=ERROR || exit 1
ninja dev_build -C build || exit 1
rm -rf build/*

cmake -B build --log-level=ERROR || exit 1
cd build || exit 1
make -s dev_build || exit 1

cd ..
rm -rf build/
rm -rf docs/
echo "Ninja Built successfuly"
echo "make Built successfuly"
echo "build & docs directories removed"
