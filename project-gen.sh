#!/bin/bash

set -euo pipefail
IFS=$'\n\t'

complete_output() {
	echo "Project $proj_command set up successfully!"
	echo ""
	echo "Next Steps"
	if [ "$do_git" = true ]; then
		echo "Create the repo on Github."
		echo "Set origin and push."
	fi
	echo "Test install in $install_path/$proj_command"
	echo "Update Readme and any meta files"
	echo "Start coding"
	echo ""
}

version_output() {
	echo "C-Template is a small tool that generates a ready-to-use C project"

	echo "Version 2.0.0"
	echo "Please donate to the EFF if this program has been of any help"
	echo ""
	echo "Copyright © 2026 tpalmerstudios"
	echo "License GPLv3+: GNU GPL version 3 or later https://gnu.org/licenses/gpl.html."
	echo "This is free software: you are free to change and redistribute it."
	echo "There is NO WARRANTY, to the extent permitted by law."
	echo ""
	echo "Written by tpalmerstudios"
}

help_output() {
	echo "Usage ./project-gen.sh [OPTION]"
	echo "Install a stub C Project to a directory"
	echo ""
	echo "-v, --version			output version information and exit"
	echo "-h, --help			display this help and exit"
	echo "    --no-git			skips all setup related to a git repository"
	echo "    --force			uses a directory even if it already exists. does not empty it first"
	echo "    --remove			removes a directory COMPLETELY before creating the template files in that directory"
	echo "    --path [PATH]		sets a directory where the project will be installed under"
	echo ""
	echo "Documentation <https://github.com/tpalmerstudios/c-template>"
	echo "Questions for the author: <obsoleteTiger@protonmail.com>"
}

# Unsure how to do this for bulk actions
#sed_inplace() {
#	sed -i.bak "$@" && rm -f "$1.bak"
#}

sed_escape_repl() {
	# escape: backslash, ampersand, and delimiter |
	printf '%s' "$1" | sed -e 's/[\\&|]/\\&/g'
}

force=false
version=false
remove=false
do_git=true
show_help=false
install_path=".."
optind=0
args=("$@")
argc=$#

while [ $optind -lt $argc ]; do
	param="${args[$optind]}"

	case "$param" in
	--version | -v)
		version=true
		;;
	--force)
		force=true
		;;
	--remove)
		remove=true
		;;
	--no-git)
		do_git=false
		;;
	--help | -h | help)
		show_help=true
		;;
	--path)
		next=$((optind + 1))
		if [ $next -ge $argc ]; then
			echo "\"--path some/path\" is the proper syntax"
			exit 1
		fi
		install_path="${args[$next]}"
		optind=$((optind + 1))
		;;
	*)
		echo "Unknown Option: $param"
		exit 1
		;;
	esac
	optind=$((optind + 1))
done

if [ "$version" = true ]; then
	version_output
	exit 0
fi

if [ "$show_help" = true ]; then
	help_output
	exit 0
fi

if [ ! -d "$install_path" ]; then
	echo "Installation Path invalid. Must be an existing directory"
	echo "Project Will Be installed as a subdirectory with the name you give it"
	exit 1
fi
install_path="${install_path%/}"

read -r -p "Project Name: " proj_readable

proj_command=${proj_readable//[^[:alnum:] ]/}
proj_command=${proj_command//[[:space:]]/_}
proj_upper=${proj_command^^}
target_dir="$install_path/$proj_command"

read -r -p "Project description in 1-2 Sentences: " proj_description
proj_description=${proj_description//\\/\\\\}
proj_description=${proj_description//\"/\\\"}
proj_description=${proj_description//\$/\\\$}
proj_description=${proj_description//;/\\;}

echo "Regular Name:		${proj_readable}"
echo "Upper Case:		${proj_upper}"
echo "Directory Name:		${proj_command}"
echo "Description:		${proj_description}"
read -r -p "Confirm Variables make sense (y/N): " confirm
if [[ "${confirm}" != "y" && "${confirm}" != "Y" ]]; then
	echo "Nothing Done... Exiting!"
	exit 1
fi

if [ "$remove" = true ] && [ -d "$target_dir" ]; then
	echo "Removing the directory: '$target_dir'"
	read -r -p "Type the name of the directory to confirm. ($proj_command): " confirm_remove
	if [[ "${proj_command}" != "${confirm_remove}" ]]; then
		echo "Nothing Done... Exiting!"
		exit 1
	else
		rm -rf -- "${target_dir:?}"
		echo "Removed $target_dir"
	fi
fi

if [ -d "$target_dir" ]; then
	echo "'$target_dir' already exists."
	if [ "$force" = true ]; then
		echo "Using existing directory $target_dir due to --force"
	else
		echo "Use \"--force\" to overwrite."
		echo "Exiting"
		exit 1
	fi
fi

mkdir -p "$target_dir"
if [ ! -d "$target_dir" ]; then
	echo "Directory not created. Exiting"
	exit 1
fi

if [ "$do_git" = true ]; then
	git init "$target_dir"
	cp -r ./.github/ "$target_dir"
	cp ./.gitignore "$target_dir"
fi

# child dir copy
if cp -r ./child/* "$target_dir"; then
	echo "Copied 'child' to $target_dir"
else
	echo "Failed to copy 'child'"
	exit 1
fi

cd "$target_dir"

proj_command_s=$(sed_escape_repl "$proj_command")
proj_readable_s=$(sed_escape_repl "$proj_readable")
proj_description_s=$(sed_escape_repl "$proj_description")
proj_upper_s=$(sed_escape_repl "$proj_upper")
find . -type f -exec sed -i "s|01PROJCMD|$proj_command_s|g" {} +
find . -type f -exec sed -i "s|01PROJTEMP|$proj_readable_s|g" {} +
find . -type f -exec sed -i "s|01PROJDESC|$proj_description_s|g" {} +
find . -type f -exec sed -i "s|01PROJUPPER|$proj_upper_s|g" {} +

if [ "$do_git" = true ]; then
	git add .
	git commit -m "initial commit; template generated by tpalmerstudios/c-template"
fi

complete_output
exit 0
