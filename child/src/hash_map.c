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

#include "hash_map.h"
#include "linked_list.h"
#include <stdlib.h>
#include <string.h>

static unsigned long
hash (const char *str)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}

ctHM_t *
ctHMInit (size_t bucketCount)
{
	if (bucketCount == 0)
		return NULL;
	ctHM_t *map = malloc (sizeof (ctHM_t));
	if (map == NULL)
		return NULL;
	map->buckets = calloc (bucketCount, sizeof (ctLL_t *));
	if (map->buckets == NULL)
		{
			free (map);
			return NULL;
		}
	size_t i;
	for (i = 0; i < bucketCount; i++)
		{
			map->buckets[i] = ctListInit (sizeof (ctHMEntry_t));
			if (map->buckets[i] == NULL)
				{
					while (i-- > 0)
						ctListFree (map->buckets[i]);
					free (map->buckets);
					free (map);
					return NULL;
				}
		}
	map->bucketCount = bucketCount;
	map->size = 0;
	return map;
}
