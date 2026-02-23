/**
 * @file invocation.h
 * @brief Header file for invocation modile
 */

/*
 * project: 01PROJTEMP
 * module: sys_info
 * created: 2026-02-15
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Rushabh Jain
 */
#ifndef INVOCATION_H
#define INVOCATION_H

#define MAX_PATH_LEN 4096

typedef struct invocation_t
{
	int argc;
	char **argv;
	char *cwd;
} invocation_t;

/**
 * @brief initializes the Invocation
 * @param[in] argc argument count
 * @param[in] argv argument array
 * @return 0 on success, non-zero on failure
 */
int initInvocation (int argc, char *argv[]);

/**
 * @brief free the dynamic memory for the structure
 */
void freeInvocation (void);

/**
 * @brief print the invocation strucutre
 * @return pointer to invocation structure
 */
const invocation_t *getInvocation (void);

#endif // INVOCATION_H
