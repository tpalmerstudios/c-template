#ifndef FLAGS_H
#define FLAGS_H

/***********************************************
 * @brief A structure to hold command line flags
 * *********************************************/
typedef struct Flags
{
	int testing;
} Flags;

/***********************************************
 * @brief Parses command line arguments into the structure passed to it
 **********************************************/
void initFlags (int argc, char *argv[], Flags *flags);
void showHelp (void);
void showVersion (void);

#endif // FLAGS_H
