/**
 * @file hash_map.c
 * @brief A hash map implementation
 */

/*
 * project: C-Template
 * module: hash_map
 * created: 2026-03-12
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */

#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

unsigned long
hash (const char *str)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}
