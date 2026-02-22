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
#include "sys_info.h"
#include "invocation.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef DEBUG
#include "debug.h"
#endif

void
runProgram (void)
{
#ifdef DEBUG
	DBG ("runProgram Start");
#endif
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
#ifdef DEBUG
	DBG ("runProgram End");
#endif
}

/*
 * Add a startup() function he
 */

/************************************
 * @brief Entry Point for 01PROJTEMP
 * **********************************/
int
main (int argc, char *argv[])
{
#ifdef DEBUG
	DBG ("Main Start");
#endif
	if (initLog ("log.txt", VERBOSE) != 0)
		printf ("Log failed!\n");
	initFlags (argc, argv);
	getDateAndTime ();
	getPlatformInfo();
	const Flags *flags = getFlags ();
	if (flags->printFlags)
		exit (0);
	if (flags->flagName)
		printf ("Example Flag Mode\n");

	runProgram ();
	closeLog ();
#ifdef DEBUG
	DBG ("Main End");
#endif
	return 0;
}
