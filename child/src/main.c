/**
 * @file main.c
 * @brief Entry point for 01PROJTEMP
 */

/*
 * project: 01PROJTEMP
 * description: 01PROJDESC
 * created: 2026-01-19
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */

#include "flags.h"
#include "logger.h"
#include <assert.h>
#include <stdio.h>
#ifdef DEBUG
#include "debug.h"
#endif

/************************************
 * @brief Entry Point for 01PROJTEMP
 * **********************************/
int
main (int argc, char *argv[])
{
#ifdef DEBUG
	DBG ("Main Start");
#endif
	initFlags (argc, argv);
	if (initLog ("log.txt", VERBOSE) != 0)
		printf ("Log failed!\n");
	if (isFlagName ())
		printf ("Example Flag Mode\n");

	int loop = 1;
	assert (loop == 1);
	while (loop)
		{
#ifdef DEBUG
			DBG ("loop=%d", loop);
#endif
			printf ("Hello, World!\n");
			loop = 0;
			logMessage (WARNING, "warning: loop set to %d", loop);
			logMessage (INFO, "loop set to %d", loop);
		}
	closeLog ();
#ifdef DEBUG
	DBG ("Main End");
#endif
	return 0;
}
