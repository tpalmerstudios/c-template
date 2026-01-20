#ifndef FLAGS_H
#define FLAGS_H

/***********************************************
 * @brief A structure to hold command line flags
 * *********************************************/
typedef struct Flags
{
	int flagName;
} Flags;

/***********************************************
 * @brief Parses command line arguments into the structure passed to it
 **********************************************/
void initFlags (int argc, char *argv[]);
const Flags *getFlags (void);
int isFlagName (void);

#endif // FLAGS_H
