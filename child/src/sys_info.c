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

#include "sys_info.h"
#include <stdio.h>
#include <time.h>

// Include necessary headers based on the platform
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <sys/utsname.h>
#endif

void
getPlatformInfo ()
{
#if defined(_WIN32) || defined(_WIN64)
	OSVERSIONINFOEX osVersionInfo;
	ZeroMemory (&osVersionInfo, sizeof (OSVERSIONINFOEX));
	osVersionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);

	if (GetVersionEx ((OSVERSIONINFO *)&osVersionInfo))
		{
			printf ("Platform: Windows\n");
			printf ("Version: %lu.%lu\n", osVersionInfo.dwMajorVersion,
					osVersionInfo.dwMinorVersion);
			printf ("Build: %lu\n", osVersionInfo.dwBuildNumber);
		}

	SYSTEM_INFO systemInfo;
	GetSystemInfo (&systemInfo);
	printf ("Architecture: ");
	switch (systemInfo.wProcessorArchitecture)
		{
		case PROCESSOR_ARCHITECTURE_AMD64:
			printf ("x64\n");
			break;
		case PROCESSOR_ARCHITECTURE_INTEL:
			printf ("x86\n");
			break;
		case PROCESSOR_ARCHITECTURE_ARM:
			printf ("ARM\n");
			break;
		case PROCESSOR_ARCHITECTURE_ARM64:
			printf ("ARM64\n");
			break;
		default:
			printf ("Unknown\n");
		}
#else
	struct utsname systemInfo;

	if (uname (&systemInfo) == 0)
		{
			printf ("Platform: %s\n", systemInfo.sysname);
			printf ("Node: %s\n", systemInfo.nodename);
			printf ("Release: %s\n", systemInfo.release);
			printf ("Version: %s\n", systemInfo.version);
			printf ("Architecture: %s\n", systemInfo.machine);
		}
	else
		{
			printf ("uname() failed\n");
		}
#endif
}

void
getDateAndTime ()
{
#if defined(_WIN32) || defined(_WIN64)
	time_t now = time (NULL);
	struct tm timeInfo;
	if (localtime_s (&timeInfo, &now) == 0)
		{
			char buf[64];
			strftime (buf, sizeof (buf), "%Y-%m-%d %H:%M:%S", &timeInfo);
			SYSTEMTIME systemTime;
			GetLocalTime (&systemTime);
			printf ("Date and Time: %s.%03u\n", buf, (unsigned)systemTime.wMilliseconds);
		}
	else
		{
			printf ("localtime_s() failed\n");
		}
#else
	struct timespec timeSpec;
	if (clock_gettime (CLOCK_REALTIME, &timeSpec) == 0)
		{
			struct tm timeInfo;
			localtime_r (&timeSpec.tv_sec, &timeInfo);
			char buf[64];
			strftime (buf, sizeof (buf), "%Y-%m-%d %H:%M:%S", &timeInfo);
			printf ("Date and Time: %s.%03ld\n", buf, timeSpec.tv_nsec / 1000000L);
		}
	else
		{
			time_t now = time (NULL);
			struct tm timeInfo;
			if (localtime_r (&now, &timeInfo))
				{
					char buf[64];
					strftime (buf, sizeof (buf), "%Y-%m-%d %H:%M:%S", &timeInfo);
					printf ("Date and Time: %s\n", buf);
				}
			else
				{
					printf ("time retrieval failed\n");
				}
		}
#endif
}
