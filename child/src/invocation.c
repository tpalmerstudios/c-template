/**
 * @file invocation.c
 * @brief Source file for invocation modile
 */

/*
 * project: 01PROJTEMP
 * module: sys_info
 * created: 2026-02-15
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Rushabh Jain
 */

#include "invocation.h"
#include "logger.h"
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <unistd.h>
#endif

static int isInit = 0;
static invocation_t g_inv;

/**
 * @brief Get current directory
 * @param[in] cwd point to char to populate the buffer
 */
static char *getCurrentDirectory ();

int
initInvocation (int argc, char *argv[])
{
	if (isInit == 0)
		{
			// Store argc
			g_inv.argc = argc;

			// Deep copy argv
			g_inv.argv = (char **)malloc ((argc + 1) * sizeof (char *));
			if (g_inv.argv != NULL)
				{
					for (int i = 0; i < argc; i++)
						{
							g_inv.argv[i] = strdup (argv[i]); // Creates a new copy
							if (!g_inv.argv[i])
								{
									// If there is any failure to allocate to any of the given
									// input. Free the memory
									for (int j = 0; j < i; j++)
										free (g_inv.argv[i]);
									free (g_inv.argv);
									logMessage (ERROR, "Could not allocate memory for argv[%d]", i);
									return -1;
								}
						}
					g_inv.argv[argc] = NULL;
					// Argument array must always have a NULL terminated
				}
			else
				{
					logMessage (ERROR, "Could not allocate memory for argv");
					return -1;
				}

			g_inv.cwd = getCurrentDirectory ();

			if (!g_inv.cwd)
				{
					for (int i = 0; i < argc; i++)
						free (g_inv.argv[i]);

					free (g_inv.argv);
					logMessage (ERROR, "Could not allocate memory for cwd");
					return -1;
				}
			isInit = 1;
		}
	else
		{
			logMessage (WARNING, "Invocation already initialized");
			return -1;
		}
	return 0;
}

void
freeInvocation (void)
{
	if (!isInit)
		return;

	// Free the individual memory from the array
	if (g_inv.argv)
		{
			for (int i = 0; i < g_inv.argc; i++)
				free (g_inv.argv[i]);
			free (g_inv.argv);
			g_inv.argv = NULL;
		}
	// Free the cwd path
	if (g_inv.cwd)
		{
			free (g_inv.cwd);
			g_inv.cwd = NULL;
		}
	g_inv.argc = 0;
	isInit = 0;
}

const invocation_t *
getInvocation (void)
{
	return &g_inv;
}

static char *
getCurrentDirectory ()
{
	char buffer[MAX_PATH_LEN];
	char *result = NULL;

#if defined(_WIN32) || defined(_WIN64)
	if (_getcwd (buffer, sizeof (buffer)) == NULL)
		{
			logMessage (ERROR, "Could not get the current directory");
			result = NULL;
		}
#else
	if (getcwd (buffer, sizeof (buffer)) == NULL)
		{
			logMessage (ERROR, "Could not get the current directory");
			result = NULL;
		}
#endif
	else
		{
			// Doing safe copy into the argument
			result = strdup (buffer);
		}
	return result;
}
