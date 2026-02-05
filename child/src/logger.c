/**
 * @file logger.c
 * @brief Source for logger module
 */

/*
 * project: 01PROJTEMP
 * module: logger
 * created: 2026-02-03
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */

#include "logger.h"
#include <stdarg.h>
#include <stdio.h>

static FILE *log = NULL;
static int threshold = ERROR;

void
logSink (const char *message, int level)
{
	if (log == NULL)
		return;
	if (level > threshold)
		return;

	fputs (message, log);
	fputc ('\n', log);
	fflush (log);
}

int
initLog (char *file, int initThreshold)
{
	if (log != NULL)
		{
			logMessage (WARNING, "attempted to reinitialize log");
			return 0;
		}
	log = fopen (file, "a");
	if (log == NULL)
		return -1;
	threshold = initThreshold;
	return 0;
}

void
logMessage (int level, const char *message, ...)
{
	if (log == NULL)
		return;

	char buffer[LOG_LENGTH];

	va_list args;
	va_start (args, message);
	vsnprintf (buffer, sizeof (buffer), message, args);
	va_end (args);

	logSink (buffer, level);
}

void
closeLog ()
{
	if (log == NULL)
		return;
	logMessage (INFO, "closed log file");
	fclose (log);
	log = NULL;
}
