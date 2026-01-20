#include <stdio.h>
#include "messages.h"

static const char *projectName = "01PROJTEMP";
static const char *projectDesc = "01PROJDESC";
static const char *projectCmd = "01PROJCMD";

static const char *helpText =
"Usage ./%s [OPTION]\n"
"%s\n\n"
"-v, --version\t\toutput version information and exit\n"
"-h, --help\t\tdisplay this help and exit\n"
"    --flagName\t\trun %s in \"flag\" mode\n\n"
"Documentation <https://github.com/tpalmerstudios/%s>\n"
"Questions for the author: <obsoleteTiger@protonmail.com>\n";

static const char versionText[] =
"%s\n"
"%s\n"
"Version: %s\n"
"Please donate to the EFF if this program has been of any help\n\n"
"Copyright © 2026 tpalmerstudios\n"
"License GPLv3+: GNU GPL version 3 or later https://gnu.org/licenses/gpl.html.\n"
"This is free software: you are free to change and redistribute it.\n"
"There is NO WARRANTY, to the extent permitted by law.\n\n"
"Written by tpalmerstudios\n";

void printHelp (void)
{
	printf (helpText, projectCmd, projectDesc, projectName, projectCmd);
}

void printVersion (void)
{
	printf (versionText, projectName, projectDesc, PROJECT_VERSION);
}

const char *
getVersion (void)
{
	return PROJECT_VERSION;
}
