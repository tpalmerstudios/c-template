/**
 * @file: sys_info.c
 * @brief: Source file for sys_info module
 */

/*
 * project: 01PROJTEMP
 * module: sys_info
 * created: 2026-02-09
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Rushabh Jain
 */
#ifndef SYS_INFO_H
#define SYS_INFO_H

#include <stddef.h>

#define SYS_LENGTH 128
typedef struct SysInfo
{
	char os_name[SYS_LENGTH];
	char os_release[SYS_LENGTH];
	char arch[SYS_LENGTH];
	size_t page_size;
	int cpu_count;
} SysInfo;

/**
 * @brief gets platform information
 * @param info struct containing core OS details
 * @return 0 on success, -1 on failure
 */
int getPlatformInfo (SysInfo *info);

/**
 * @brief fills a string with formatted time and date
 * @param timeOutput a character array that will have a formatted time string
 * @param maxSize size of timeOutput
 * @param timeFormat a string to determine the format of the time - see strftime()
 * @return 0 on success, -1 on failure
 */
int getDateAndTime (char *timeOutput, size_t maxSize, const char *timeFormat);

/**
 * @brief fills a string with formatted time and date add milliseconds
 * @param timeOutput string that will have the formatted time plus .XXX
 * @param maxSize size of timeOutput (account for 4 chars appended)
 * @param timeFormat a string to determine the format of the time - see strftime()
 * @return 0 on success, -1 on failure
 */
int getTimeMS (char *timeOutput, size_t maxSize, const char *timeFormat);

#endif // SYS_INFO_H
