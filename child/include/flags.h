/**
 * @file flags.h
 * @brief Header file for flags module
 */

/*
 * project: 01PROJTEMP
 * module: flags
 * created: 2025-01-21
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */
#ifndef FLAGS_H
#define FLAGS_H

/**
 * @brief A structure to hold command line flags
 */
typedef struct Flags
{
	int flagName;
	int printFlags;
} Flags;

/**
 * @brief Parses command line arguments into the structure passed to it
 */
void initFlags (int argc, char *argv[]);

const Flags *getFlags (void);

#endif // FLAGS_H
