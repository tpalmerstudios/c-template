/**
 * @file: invocation.c
 * @brief: Source file for invocation modile
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <unistd.h>
#endif

/**
 * @brief Get current directory
 * @param[in] cwd point to char to populate the buffer
 */
static char *getCurrentDirectory ();

invocation_t *
initInvocation (int argc, char *argv[])
{
	invocation_t *localInvocation = (invocation_t *)malloc (sizeof (invocation_t));

	if (localInvocation != NULL)
		{
			// Store argc
			localInvocation->argc = argc;

			// Deep copy argv
			localInvocation->argv = (char **)malloc ((argc + 1) * sizeof (char *));
			if (localInvocation->argv != NULL)
				{
					for (int i = 0; i < argc; i++)
						{
							localInvocation->argv[i] = strdup (argv[i]); // Creates a new copy
							if (!localInvocation->argv[i])
								{
									// If there is any failure to allocate to any of the given
									// input. Free the memory
									for (int j = 0; j < i; j++)
										{
											free (localInvocation->argv[i]);
										}
									free (localInvocation->argv);
									free (localInvocation);
									logMessage (ERROR, "Could not allocate memory for argv[%d]", i);
									return NULL;
								}
						}
					localInvocation->argv[argc]
						= NULL; // Argument array must always have a NULL terminated
				}
			else
				{
					logMessage (ERROR, "Could not allocate memory for argv");
					free (localInvocation); // Free the space
					return NULL;
				}

			localInvocation->cwd = getCurrentDirectory ();

			if (!localInvocation->cwd)
				{
					for (int i = 0; i < argc; i++)
						{
							free (localInvocation->argv[i]);
						}

					free (localInvocation->argv);
					free (localInvocation);
					logMessage (ERROR, "Could not allocate memory for cwd");
					return NULL;
				}
		}
	else
		{
			logMessage (ERROR, "Could not allocate memory for invocation structure");
			return NULL;
		}
	return localInvocation;
}

void
freeInvocation (invocation_t *inv)
{
	if (!inv)
		return;

	// Free the individual memory from the array
	if (inv->argv)
		{
			for (int i = 0; i < inv->argc; i++)
				{
					free (inv->argv[i]);
				}
			free (inv->argv);
			inv->argv = NULL;
		}
	// Free the cwd path
	if (inv->cwd)
		{
			free (inv->cwd);
			inv->cwd = NULL;
		}
	inv->argc = 0;
}

void
printInvocation (const invocation_t *inv)
{
	if (!inv)
		{
			return;
		}

	printf ("CWD  : %s\n", inv->cwd);
	printf ("argc : %d\n", inv->argc);
	for (int i = 0; i < inv->argc; i++)
		{
			printf ("argv[%d]: %s\n", i, inv->argv[i]);
		}
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
