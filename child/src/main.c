/*************************************
 * @file main.c
 * @brief Entry point for 01PROJTEMP
 *
 * 01PROJDESC
 * @author tpalmerstudios
 * @maintainer tpalmerstudios
 * @date 2026-01-19
 *
 * ***********************************/

#include "flags.h"
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
		}
#ifdef DEBUG
	DBG ("Main End");
#endif
	return 0;
}
