#include "main.h"
#include "debug.h"
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
	DBG ("Start!");
#endif

	int pizza = 1;
	struct example Example;
	assert (pizza == 1);
	Example.hello = "Hello World!\n";
	while (pizza)
		{
			printf ("%s", Example.hello);
#ifdef DEBUG
			DBG ("Example.hello=%d", Example.hello);
#endif

			pizza = 0;
		}
	return 0;
}
