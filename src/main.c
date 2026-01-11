#include "main.h"
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
	int pizza = 1;
	struct example Example;
	Example.hello = "Hello World!\n";
	while (pizza)
		{
			printf ("%s", Example.hello);

			pizza = 0;
		}
	return 0;
}
