/**
 * @file: invocation.h
 * @brief: Header file for invocation modile
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

#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
#include <direct.h>
#else
#include <unistd.h>
#endif

#define MAX_PATH_LEN    4096

typedef struct 
{
    int argc;
    char **argv;
    char *cwd;    
} invocation_t;

/**
 * @brief initializes the Invocation
 * @param[in] argc argument count 
 * @param[in] argv argument array
 * @return pointer to invocation structure
 */
invocation_t* initInvocation(int argc, char *argv[]);  

/**
 * @brief free the dynamic memory for the structure
 * @param[in] inv pointer to invocation structure 
 */
void freeInvocation(invocation_t *inv);

/**
 * @brief print the invocation strucutre
 * @param[in] inv pointer to invocation structure
 */
void printInvocation(const invocation_t *inv);

#endif // INVOCATION_H
