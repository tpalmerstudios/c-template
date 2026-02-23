/**
 * @file flags.c
 * @brief source file for flags module
 */

/*
 * project: 01PROJTEMP
 * module: flags
 * created: 2026-01-21
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */
#include "flags.h"
#include "messages.h"
#include <getopt.h>
#include <string.h>

static Flags flags = { 0, 0 };

void
initFlags (int argc, char *argv[])
{
	flags.flagName = 0;
	flags.printFlags = 0;
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
					flags.printFlags = 1;
					printVersion ();
					break;
				case OPT_FLAG_NAME:
					flags.flagName = 1;
					break;
				case 'h':
					flags.printFlags = 1;
					printHelp ();
					break;
				default:
					flags.printFlags = 1;
					printBadFlag ();
				}
		}
}

const Flags *
getFlags (void)
{
	return &flags;
}
