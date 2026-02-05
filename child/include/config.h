/**
 * @file: config.h
 * @brief: Source for auto-generated constants
 */

/*
 * project: C-Template
 * module: config
 * created: 2026-02-05
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */
#ifndef CONFIG_H
#define CONFIG_H

#define PROJ_NAME "01PROJUPPER"
#define PROJ_DESC "01PROJDESC"
#define VERSION "0.0.1"
#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 1

#define PLATFORM "Linux"
#define TARGET_ARCH "x86_64"
#define CROSS_COMPILE 0
#define COMPILER_ID "GNU"
#define COMPILER_VERSION "15.2.1"
#define CONFIG_TIMESTAMP "2026-02-05T21:53:11Z"

#define DEF_TEMPLATE_DIR "templates/"

#ifdef DEBUG
#define DEF_LOG_LEVEL VERBOSE
#define BUILD_TYPE "Debug"
#define GIT_DIRTY 1
#define GIT_COMMIT "94407b3"
#else
#define DEF_LOG_LEVEL ERROR
#define BUILD_TYPE "Release"
// These should be set for runs on machines without git... TODO
#define GIT_DIRTY 0
#define GIT_COMMIT "000000"
#endif

/*
 * #define INSTALL_PREFIX NULL
 * #define DEF_CONFIG_DIR NULL
 * #define
 */
#endif // CONFIG_H
