#ifndef PROJECT_VERSION_H
#define PROJECT_VERSION_H

#define PROJECT_VERSION_MAJOR 0
#define PROJECT_VERSION_MINOR 0
#define PROJECT_VERSION_PATCH 1

#define PROJECT_VERSION "0.0.1"

/**********************************************************
 * @brief gets the semantic version number
 * @return a string literal of the version
 * ********************************************************/
inline const char *
getVersion (void)
{
	return PROJECT_VERSION;
}

#endif // PROJECT_VERSION_H
