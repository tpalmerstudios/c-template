/**
 * @file: invocation.c
 * @brief: Source file for invocation modile
 */

/*
 * project: 01PROJTEMP
 * module: sys_info
 * created: 2026-02-15
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Rushabh Jain
 */

#include "invocation.h"


/**
 * @brief Get current directory
 * @param[in] cwd point to char to populate the buffer
 */
static void getCurrentDirectory(char* cwd);

 invocation_t* initInvocation(int argc, char *argv[])
 {
    invocation_t *localInvocation = (invocation_t*)malloc(sizeof(invocation_t));

    if(localInvocation != NULL)
    {
        //Store argc
        localInvocation->argc = argc;

        //Deep copy argv
        localInvocation->argv = (char**)malloc((argc+1)* sizeof(char*));
        if (localInvocation->argv != NULL)
        {
            localInvocation->argv = argv;
        }
        else
        {
            //TODO: Log the error
            return NULL;
        }

        
        
    }
    else
    {
        //TODO: Log the error 
        return NULL;
    }
    return localInvocation;
 }


static void getCurrentDirectory(char* cwd)
 {
    char buffer[MAX_PATH_LEN];

#if defined(_WIN32) || defined(_WIN64)
    if(_getcwd(buffer, sizeof(buffer)) == NULL)
    {
        //Log the error
    }
#else
    if(getcwd(buffer, sizeof(buffer)) == NULL)
    {
        // Log the error
    }
#endif

    // Doing safe copy into the argument
    strlcpy(cwd, buffer, sizeof(cwd));
 }