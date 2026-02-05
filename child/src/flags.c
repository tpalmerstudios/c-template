#include "flags.h"
#include "messages.h"
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

static Flags globalFlags = { 0 };

void
initFlags (int argc, char *argv[])
{
	globalFlags.flagName = 0;
	int c;
	enum
	{
		// NEW FLAGS CAN BE ADDED ABOVE 255
		OPT_FLAG_NAME = 256
	};
	static const struct option long_options[] = { { "flagName", no_argument, 0, OPT_FLAG_NAME },
												  { "help", no_argument, 0, 'h' },
												  { "version", no_argument, 0, 'v' },
												  { 0, 0, 0, 0 } };
	while ((c = getopt_long (argc, argv, "hv", long_options, NULL)) != -1)
		{
			switch (c)
				{
				case 'v':
					printVersion ();
					exit (0);
					break;
				case OPT_FLAG_NAME:
					globalFlags.flagName = 1;
					break;
				case '?':
				case 'h':
				default:
					printHelp ();
					exit (0);
					break;
				}
		}
}

const Flags *
getFlags (void)
{
	return &globalFlags;
}

int
isFlagName (void)
{
	return globalFlags.flagName;
}
