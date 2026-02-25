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
#include "invocation.h"
#include "logger.h"
#include "sys_info.h"
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

int
startup (int argc, char *argv[])
{
	int error = 0;

	if (initLog ("log.txt", VERBOSE) != 0)
		{
			printf ("Log failed!\n");
			error = 1;
		}
	if (initInvocation (argc, argv) != 0)
		{
			logMessage (ERROR, "Invocation failed!");
			error += 1;
		}
	else
		logMessage (INFO, "Invocation saved");
	const invocation_t *inv = getInvocation ();
	logMessage (INFO, "Invocation Current Directory: %s", inv->cwd);
	initFlags (argc, argv);

	char currentTime[64];
	if (getDateAndTime (currentTime, sizeof (currentTime), "%Y-%m-%d %H:%M:%S") == 0)
		printf ("The current time is: %s\n", currentTime);
	if (getTimeMS (currentTime, sizeof (currentTime), "%Y-%m-%d %H:%M:%S") == 0)
		printf ("The current time is: %s\n", currentTime);

	SysInfo info;
	if (getPlatformInfo (&info) == 0)
		{
			printf ("Operating System: %s\n", info.os_name);
			printf ("OS Version: %s\n", info.os_release);
			printf ("Architecture: %s\n", info.arch);
			printf ("Number of Cores: %d\n", info.cpu_count);
			printf ("Page Size: %d\n", (int)info.page_size);
		}
	const Flags *flags = getFlags ();
	if (flags->printFlags)
		exit (0);
	if (flags->flagName)
		printf ("Example Flag Mode\n");

	return error;
}

void
shutdown ()
{
	freeInvocation ();
	closeLog ();
	return;
}

/************************************
 * @brief Entry Point for 01PROJTEMP
 * **********************************/
int
main (int argc, char *argv[])
{
#ifdef DEBUG
	DBG ("Main Start");
#endif
	if (startup (argc, argv) != 0)
		printf ("Startup Failed\n");
	runProgram ();
	shutdown ();
#ifdef DEBUG
	DBG ("Main End");
#endif
	return 0;
}
