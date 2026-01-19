#include "flags.h"
#include "version.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Flags globalFlags = { 0 };

void
showHelp (void)
{
	printf ("Usage ./01PROJCMD [OPTION]\n");
	printf ("01PROJDESC\n\n");
	printf ("-v, --version\t\toutput version information and exit\n");
	printf ("-h, --help\t\tdisplay this help and exit\n");
	printf ("    --flagName\t\trun 01PROJTEMP in \"flag\" mode\n\n");
	printf ("Documentation <https://github.com/tpalmerstudios/01PROJCMD>\n");
	printf ("Questions for the author: <obsoleteTiger@protonmail.com>\n");
}

void
showVersion (void)
{
	printf ("01PROJTEMP\n");
	printf ("01PROJDESC\n");
	printf ("Version: %s\n", PROJECT_VERSION);
	printf ("Please donate to the EFF if this program has been of any help\n\n");
	printf ("Copyright © 2026 tpalmerstudios\n");
	printf ("License GPLv3+: GNU GPL version 3 or later https://gnu.org/licenses/gpl.html.\n");
	printf ("This is free software: you are free to change and redistribute it.\n");
	printf ("There is NO WARRANTY, to the extent permitted by law.\n\n");
	printf ("Written by tpalmerstudios\n");
}

void
initFlags (int argc, char *argv[])
{
	int i;
	globalFlags.flagName = 0;

	for (i = 0; i < argc; ++i)
		{
			if ((strcmp (argv[i], "--help") == 0) || (strcmp (argv[i], "-h") == 0))
				{
					showHelp ();
					exit (0);
				}
			if ((strcmp (argv[i], "--version") == 0) || (strcmp (argv[i], "-v") == 0))
				{
					showVersion ();
					exit (0);
				}
			if (strcmp (argv[i], "--flagName") == 0)
				{
					globalFlags.flagName = 1;
				}
		}
}

const Flags *
getFlags (void)
{
	return &globalFlags;
}

int isFlagName (void)
{
	return globalFlags.flagName;
}
