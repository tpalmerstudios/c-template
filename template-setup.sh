#!/bin/bash

read -p "Project command name (name of target and directory): " proj_command
if [ -d "../$proj_command" ]; then
	echo "Error: '../$proj_command' already exists"
	exit 1
fi

mkdir "../$proj_command"
git init "../$proj_command"
mkdir "../$proj_command/.github" || exit 1

cp_check() {
	if cp -r "$1" "../$proj_command"; then
		echo "Copied $1 to ../$proj_command"
	else
		echo "Failed to copy $1"
		exit 1
	fi
}
cp_check ./.clang-format
cp_check ./.github/
cp_check ./.gitignore
cp_check ./include
cp_check ./src
cp_check ./tests
cp_check ./CMakeLists.txt
cp_check ./CONTRIBUTING.md
cp_check ./Doxyfile
cp_check ./LICENSE
cp_check ./test.sh

cp ./CHANGELOG-NEW.md ../$proj_command/CHANGELOG.md
cp ./README-NEW.md ../$proj_command/README.md

cd ../$proj_command

# fnd and replace recursively through new current directory
read -p "Project Name in a readable format: " proj_readable
read -p "Project description. 1-2 Sentences don't use \\ or \/ or \|: " proj_description
read -p "Project Command in Upper Case (used for CMake file globbing): " proj_upper

echo "$proj_description" > .git/description

find . -type f -exec sed -i "s|01PROJCMD|$proj_command|g" {} +
find . -type f -exec sed -i "s|01PROJTEMP|$proj_readable|g" {} +
find . -type f -exec sed -i "s|01PROJDESC|$proj_description|g" {} +
find . -type f -exec sed -i "s|01PROJUPPER|$proj_upper|g" {} +

git add .
git commit -m "initial commit; copied template from tpalmerstudios/c-template"

echo "Project $proj_command set up successfully!"
echo "--------------------------------------------"
echo "Todo:"
echo "Create the repo on Github."
echo "Set origin and push."
echo "Update Version numbers"
echo "Start coding"

