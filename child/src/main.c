#include "debug.h"
#include "flags.h"
#include <assert.h>
#include <stdio.h>

/***************************
 * @brief A main function that loops once
 * @param argc Number of Arguments
 * @param argv An array of arguments as a string
 * @return 0 for success
 * ***********************/
int
main (int argc, char *argv[])
{
#ifdef DEBUG
	DBG ("Main Start");
#endif

	Flags flags;
	initFlags (argc, argv, &flags);
	if (flags.testing) printf ("Testing\n");

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
