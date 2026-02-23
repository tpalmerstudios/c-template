/**
 * @file logger.h
 * @brief Header for logger module
 */

/*
 * project: 01PROJTEMP
 * module: logger
 * created: 2026-02-03
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */
#ifndef LOGGER_H
#define LOGGER_H

#define LOG_LENGTH 512
enum logLevel
{
	ERROR,
	WARNING,
	INFO,
	VERBOSE
};

/**
 * @brief initializes the log
 * @param file complete filepath to the log
 * @param threshold messages at or below this number will be logged
 */
int initLog (char *file, int threshold);

/**
 * @brief formats a message to log sink
 */
void logMessage (int level, const char *message, ...);

/**
 * @brief closes log file
 */
void closeLog ();

#endif // LOGGER_H
