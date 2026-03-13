#!/bin/bash

help_output() {
	echo "Usage ./gen-c.sh [Filename]"
	echo "Create a C file with some basic metadata"
	echo ""
	echo "Written by tpalmerstudios"
}
escape_sed() {
	printf '%s\n' "$1" | sed 's/[\/&#]/\\&/g'
}

if [ "$#" -lt 1 ]; then
	help_output
	exit 1
fi

file="$1"
case "$file" in
*.h)
	template="gen-c.h"
	filetype="header"
	;;
*)
	template="gen-c.c"
	filetype="normal"
	;;
esac

USER_TEMPLATE_DIR="$HOME/.config/gen-c/templates"

PROJECT_ROOT="$(git rev-parse --show-toplevel 2>/dev/null)"
if [ -z "$PROJECT_ROOT" ]; then
	PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
fi

OUTPUT_DIR="$(pwd)"
OUTPUT_FILE="$OUTPUT_DIR/$file"
if [ -f "$USER_TEMPLATE_DIR/$template" ]; then
	TEMPLATE_FILE="$USER_TEMPLATE_DIR/$template"
elif [ -f "$PROJECT_ROOT/templates/$template" ]; then
	TEMPLATE_FILE="$PROJECT_ROOT/templates/$template"
else
	echo "Error: template not found: $template" >&2
	exit 1
fi

if [ -e "$OUTPUT_FILE" ]; then
	echo "Error: file already exists: $file" >&2
	exit 1
fi

if [ ! -f "$TEMPLATE_FILE" ]; then
	echo "Error: template not found: $TEMPLATE_FILE" >&2
	exit 1
fi

# Edit these if you edit them in the template files
file_var="file_name"
brief_var="brief_desc"
proj_var="proj_name"
mod_var="mod_name"
date_var="create_date"
author_var="author_name"
description="File Description"
project="01PROJTEMP"
module="Module Name"
include="include_guard"

if [ ! -f "$PROJECT_ROOT/README.md" ]; then
	read -r -p "$project: " project
else
	project="$(sed 's/^#[#[:space:]]*//' "$PROJECT_ROOT/README.md" | head -n 1)"
fi

read -r -p "$description: " description
read -r -p "$module: " module
author="$(git config user.name || echo 'John Doe')"
today_date="$(date +%F)"

file_esc="$(escape_sed "$file")"
description_esc="$(escape_sed "$description")"
project_esc="$(escape_sed "$project")"
module_esc="$(escape_sed "$module")"
author_esc="$(escape_sed "$author")"
date_esc="$(escape_sed "$today_date")"
guard_from="${file_esc##*/}"

cp "$TEMPLATE_FILE" "$OUTPUT_FILE"
if [ ! -f "$OUTPUT_FILE" ]; then
	echo "Error: file not created: $OUTPUT_FILE" >&2
	exit 1
fi
sed -i \
	-e "s/${file_var}/${file_esc}/g" \
	-e "s/${brief_var}/${description_esc}/g" \
	-e "s/${proj_var}/${project_esc}/g" \
	-e "s/${mod_var}/${module_esc}/g" \
	-e "s/${date_var}/${date_esc}/g" \
	-e "s/${author_var}/${author_esc}/g" \
	"$OUTPUT_FILE"

if [ "$filetype" = "header" ]; then
	guard="$(printf '%s\n' "$guard_from" |
		tr '[:lower:]' '[:upper:]' |
		sed 's#[^A-Z0-9]#_#g')"
	sed -i "s/${include}/${guard}/g" "$OUTPUT_FILE"
fi

if grep -qE '\b(file_name|brief_desc|proj_name|mod_name|create_date|author_name)\b' "$OUTPUT_FILE"; then
	echo "Error: unreplaced template variables remain in $OUTPUT_FILE" >&2
	exit 1
else
	echo "Complete file at : $OUTPUT_FILE"
	exit 0
fi
