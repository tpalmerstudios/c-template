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
	char *value;
	unsigned long hash;
} ctHMEntry_t;

typedef struct
{
	ctLL_t **buckets;
	size_t bucketCount;
	size_t size;
} ctHM_t;

ctHM_t *ctHMInit (size_t bucketCount);
void ctHMFree (ctHM_t *map);
size_t ctHMSize (const ctHM_t *map);
int ctHMIsEmpty (const ctHM_t *map);
void ctHMClear (ctHM_t *map);

int ctHMPut (ctHM_t *map, const char *key, const char *value);
void *ctHMGet (const ctHM_t *map, const char *key);
void ctHMRemove (ctHM_t *map, void (*freeValue) (void *));
int ctHMContains (const ctHM_t *map, const char *key);

/**
 * TODO
 * keyCompare
 * findEntry
 * findEntryPrev
 *
 * remove
 * put
 * get
 * contains
 *
 * HELPERS
 * resize
 * rehash
 *
 * keys
 * values
 * forEach
 * print
 * debugDump
 */

#endif // HASH_MAP_H
