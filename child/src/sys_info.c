/**
 * @file sys_info.c
 * @brief Source file for sys_info module
 */

/*
 * project: 01PROJTEMP
 * module: sys_info
 * created: 2026-02-09
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Rushabh Jain
 */
#include "sys_info.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <sys/utsname.h>
#include <unistd.h>
#endif

int
getPlatformInfo (SysInfo *info)
{
	if (info == NULL)
		return -1;

#if defined(_WIN32) || defined(_WIN64)
	SYSTEM_INFO systemInfo;
	GetNativeSystemInfo (&systemInfo);
	strncpy (info->os_name, "Windows", sizeof (info->os_name));

	info->page_size = (size_t)systemInfo.dwPageSize;
	info->cpu_count = (int)systemInfo.dwNumberOfProcessors;

	OSVERSIONINFOEX osVersionInfo;
	ZeroMemory (&osVersionInfo, sizeof (OSVERSIONINFOEX));
	osVersionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);

	/* Maintainer Note:
	 * We may need to switch to *RtlGetVersion due to changes in Windows
	 * But I could care less about windows functionality for now
	 * Let's make sure this runs, and gives sbasic values and move to real code
	 */

	if (GetVersionEx ((OSVERSIONINFO *)&osVersionInfo))
		snprintf (info->os_release, sizeof (info->os_release), "%lu.%lu\0",
				  osVersionInfo.dwMajorVersion, osVersionInfo.dwMinorVersion);

	switch (systemInfo.wProcessorArchitecture)
		{
		case (PROCESSOR_ARCHITECTURE_AMD64):
			strncpy (info->arch, "x64", sizeof (info->arch));
			break;
		case (PROCESSOR_ARCHITECTURE_ARM):
			strncpy (info->arch, "ARM", sizeof (info->arch));
			break;
		case (PROCESSOR_ARCHITECTURE_ARM64):
			strncpy (info->arch, "ARM64", sizeof (info->arch));
			break;
		case (PROCESSOR_ARCHITECTURE_IA64):
			strncpy (info->arch, "IA64", sizeof (info->arch));
			break;
		case (PROCESSOR_ARCHITECTURE_INTEL):
			strncpy (info->arch, "x86", sizeof (info->arch));
			break;
		default:
			strncpy (info->arch, "Unknown", sizeof (info->arch));
		}

#else
	struct utsname systemInfo;
	if (uname (&systemInfo) != 0)
		return -1;
	snprintf (info->os_name, sizeof (info->os_name), "%s", systemInfo.sysname);
	snprintf (info->os_release, sizeof (info->os_release), "%s", systemInfo.release);
	snprintf (info->arch, sizeof (info->arch), "%s", systemInfo.machine);
	info->cpu_count = (int)sysconf (_SC_NPROCESSORS_ONLN);
	info->page_size = (size_t)sysconf (_SC_PAGESIZE);
#endif
	return 0;
}

int
getDateAndTime (char *timeOutput, size_t maxSize, const char *timeFormat)
{
	struct tm timeInfo;
	time_t now = time (NULL);
	/* Maintainer Note:
	 * Reimplemented because my planned design was over engineered
	 */

#if defined(_WIN32) || defined(_WIN64)
	if (localtime_s (&timeInfo, &now) != 0)
		return -1;
#else
	if (localtime_r (&now, &timeInfo) == NULL)
		return -1;
#endif
	strftime (timeOutput, maxSize, timeFormat, &timeInfo);
	return 0;
}

int
getTimeMS (char *timeOutput, size_t maxSize, const char *timeFormat)
{
	if (getDateAndTime (timeOutput, maxSize, timeFormat) != 0)
		return -1;
	size_t i;
	int mils;
	for (i = 0; i < maxSize; i++)
		if (timeOutput[i] == '\0')
			break;
#if defined(_WIN32) || defined(_WIN64)
	SYSTEMTIME systemTime;
	GetLocalTime (&systemTime);
	mils = systemTime.wMilliseconds;
#else
	struct timespec timeSpec;
	if (clock_gettime (CLOCK_REALTIME, &timeSpec) != 0)
		return -1;
	mils = timeSpec.tv_nsec / 1000000L;
#endif
	if (i < maxSize)
		snprintf (timeOutput + i, maxSize - i, ".%03d", mils);
	return 0;
}
