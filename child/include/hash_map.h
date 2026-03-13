/**
 * @file hash_map.h
 * @brief Hash Map Module
 */

/*
 * project: C-Template
 * module: hash_map
 * created: 2026-03-13
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */
#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "linked_list.h"
#include <stddef.h>

typedef struct
{
	char *key;
	void *value;
	size_t hash;
} ctHMEntry_t;

typedef struct
{
	ctLL_t **buckets;
	size_t bucketCount;
	size_t size;
} ctHM_t;

ctHM_t *ctHMInit (size_t bucketCount);
void ctHMFree (ctHM_t *map, void (*freeValue) (void *));

#endif // HASH_MAP_H
