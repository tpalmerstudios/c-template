#!/bin/bash

help_output() {
	echo "Usage ./gen-c.sh [Filename]"
	echo "Create a C file with some basic metadata"
	echo ""
	echo "Written by tpalmerstudios"
}
escape_sed() {
	printf '%s\n' "$1" | sed 's/[\/&]/\\&/g'
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
project="Project Name"
module="Module Name"

if [ ! -f "$PROJECT_ROOT/README.md" ]; then
	read -r -p "$project: " project
else
	project_name="$(awk 'NR==1 {print $1; exit}' "$PROJECT_ROOT/README.md")"
fi

read -r -p "$description: " description
read -r -p "$module: " module
description="$(escape_sed "$description")"
project="$(escape_sed "$project")"
module="$(escape_sed "$module")"
author="$(git config user.name || echo 'John Doe')"
author="$(printf '%s\n' "$author" | sed 's/[\/&]/\\&/g')"
today_date="$(date +%F)"

cp "$TEMPLATE_FILE" "$OUTPUT_FILE"
if [ ! -f "$OUTPUT_FILE" ]; then
	echo "Error: file not created: $OUTPUT_FILE" >&2
	exit 1
fi
sed -i \
	-e "s/${file_var}/${file}/g" \
	-e "s/${brief_var}/${description}/g" \
	-e "s/${proj_var}/${project}/g" \
	-e "s/${mod_var}/${module}/g" \
	-e "s/${date_var}/${today_date}/g" \
	-e "s/${author_var}/${author}/g" \
	"$OUTPUT_FILE"

if [ "$filetype" = "header" ]; then
	guard="$(printf '%s\n' "$file" |
		tr '[:lower:]' '[:upper:]' |
		sed 's/\./_/g')"
	sed -i "s/include_guard/${guard}/g" "$OUTPUT_FILE"
fi

if grep -qE '\b(file_name|brief_desc|proj_name|mod_name|create_date|author_name)\b' "$OUTPUT_FILE"; then
	echo "Error: unreplaced template variables remain in $OUTPUT_FILE" >&2
	exit 1
else
	echo "Complete file at : $OUTPUT_FILE"
	exit 0
fi
