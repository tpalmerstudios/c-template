/**
 * @file debug.h
 * @brief Header defining debug macros
 */

/*
 * project: 01PROJTEMP
 * module: debug
 * created: 2026-01-21
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */
#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#include <stdio.h>
#define DBG(fmt, ...) fprintf (stderr, "[DEBUG %s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DBG(...) ((void)0)
#endif

#endif // DEBUG_H
