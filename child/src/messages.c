/**
 * @file messages.c
 * @brief constants for a message module
 */

/*
 * project: 01PROJTEMP
 * module: messages
 * created: 2026-01-21
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */
#include "messages.h"
#include "config.h"
#include <stdio.h>

// TODO retrieve the command from an invocation module
static const char *projectCmd = "01PROJCMD";

static const char helpText[] = "Usage ./%s [OPTION]\n"
							   "%s\n\n"
							   "-v, --version\t\toutput version information and exit\n"
							   "-h, --help\t\tdisplay this help and exit\n"
							   "    --flagName\t\trun %s in \"flag\" mode\n\n"
							   "Documentation <https://github.com/tpalmerstudios/%s>\n"
							   "Questions for the author: <obsoleteTiger@protonmail.com>\n";

static const char versionText[]
	= "%s\n"
	  "%s\n"
	  "Version: %s\n"
	  "Please donate to the EFF if this program has been of any help\n\n"
	  "Copyright © 2026 tpalmerstudios\n"
	  "License GPLv3+: GNU GPL version 3 or later https://gnu.org/licenses/gpl.html.\n"
	  "This is free software: you are free to change and redistribute it.\n"
	  "There is NO WARRANTY, to the extent permitted by law.\n\n"
	  "Written by tpalmerstudios\n";

static const char badFlag[] = "Improper syntax. Unknown flag.\n\n";

void
printHelp (void)
{
	printf (helpText, projectCmd, PROJ_DESC, PROJ_NAME, projectCmd);
}

void
printVersion (void)
{
	printf (versionText, PROJ_NAME, PROJ_DESC, VERSION);
}

void
printBadFlag (void)
{
	printf (badFlag);
	printHelp ();
}
