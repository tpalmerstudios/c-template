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
	if (str == NULL)
		return 0;
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}

static size_t
bucketIndex (const ctHM_t *map, unsigned long hash)
{
	if (map == NULL || map->bucketCount == 0)
		return 0;
	return hash % map->bucketCount;
}

static ctHMEntry_t *
entryCreate (const char *key, const char *value)
{
	if (key == NULL || value == NULL)
		return NULL;
	ctHMEntry_t *entry = malloc (sizeof (ctHMEntry_t));
	if (entry == NULL)
		return NULL;
	entry->key = strdup (key);
	if (entry->key == NULL)
		{
			free (entry);
			return NULL;
		}
	entry->value = strdup (value);
	if (entry->value == NULL)
		{
			free (entry->key);
			free (entry);
			return NULL;
		}
	entry->hash = hash (key);
	return entry;
}

static void
entryDestroy (ctHMEntry_t *entry)
{
	if (entry == NULL)
		return;
	free (entry->key);
	free (entry->value);
	free (entry);
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
			map->buckets[i] = ctListInit (sizeof (ctHMEntry_t *));
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

void
ctHMFree (ctHM_t *map)
{
	if (map == NULL)
		return;
	size_t i;
	ctHMEntry_t *entry;
	if (map->buckets == NULL)
		{
			free (map);
			return;
		}
	for (i = 0; i < map->bucketCount; i++)
		if (map->buckets[i] != NULL)
			{
				while (map->buckets[i]->size != 0)
					{
						if (ctListPopBack (map->buckets[i], &entry) != 0)
							{
								// Add an error handler here
								break;
							}
						entryDestroy (entry);
					}
				ctListFree (map->buckets[i]);
			}
	free (map->buckets);
	free (map);
}

size_t
ctHMSize (const ctHM_t *map)
{
	if (map == NULL)
		return 0;
	return map->size;
}

int
ctHMIsEmpty (const ctHM_t *map)
{
	if (map->size != 0)
		return 1;
	return 0;
}

void *
ctHMGet (const ctHM_t *map, const char *key)
{
	return NULL;
}

int
ctHMPut (ctHM_t *map, const char *key, const char *value)
{
	if (map == NULL)
		return -1;
	ctHMEntry_t *entry = entryCreate (key, value);
	if (entry == NULL)
		return -1;
	size_t i = bucketIndex (map, entry->hash);
	if (map->buckets[i] == NULL)
		return -1;
	if (ctListInsertBack (map->buckets[i], entry) != 0)
		return -1;
	map->size++;
	return 0;
}

void
ctHMRemove (ctHM_t *map, void (*freeValue) (void *))
{
	if (map == NULL)
		return;
}
int ctHMContains (const ctHM_t *map, const char *key);

void
ctHMClear (ctHM_t *map)
{
	if (map == NULL)
		return;
	size_t i;
	ctHMEntry_t *entry;
	if (map->buckets == NULL)
		return;
	for (i = 0; i < map->bucketCount; i++)
		if (map->buckets[i] != NULL)
			{
				while (map->buckets[i]->size != 0)
					{
						if (ctListPopBack (map->buckets[i], &entry) != 0)
							{
								// Add an error handler here
								break;
							}
						entryDestroy (entry);
					}
			}
	map->size = 0;
}
