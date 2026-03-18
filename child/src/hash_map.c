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
	unsigned long keyHash = 5381;
	int c;
	while ((c = *str++))
		keyHash = ((keyHash << 5) + keyHash) + c;
	return keyHash;
}

static size_t
bucketIndex (const ctHM_t *map, unsigned long keyHash)
{
	if (map == NULL || map->bucketCount == 0)
		return 0;
	return keyHash % map->bucketCount;
}

static ctHMEntry_t *
entryCreate (const char *key, const char *value)
{
	if (key == NULL || value == NULL)
		return NULL;
	ctHMEntry_t *entry = malloc (sizeof (ctHMEntry_t));
	if (entry == NULL)
		return NULL;
	entry->key = malloc (strlen (key) + 1);
	if (entry->key == NULL)
		{
			free (entry);
			return NULL;
		}
	memcpy (entry->key, key, strlen (key) + 1);
	entry->value = malloc (strlen (value) + 1);
	if (entry->value == NULL)
		{
			free (entry->key);
			free (entry);
			return NULL;
		}
	memcpy (entry->value, value, strlen (value) + 1);
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

static int
keyEqual (const ctHMEntry_t *entry, const char *key)
{
	if (entry == NULL || key == NULL)
		return 0;
	if (strcmp (entry->key, key) == 0)
		return 1;
	return 0;
}

static ctHMEntry_t *
findEntry (const ctHM_t *map, const char *key)
{
	if (map == NULL || key == NULL || map->buckets == NULL || map->bucketCount == 0)
		return NULL;
	unsigned long keyHash = hash (key);
	size_t i = bucketIndex (map, keyHash);
	ctLL_t *bucket = map->buckets[i];
	if (bucket == NULL)
		return NULL;
	size_t listIndex;
	ctHMEntry_t *current;
	for (listIndex = 0; listIndex < bucket->size; listIndex++)
		{
			if (ctListGet (bucket, listIndex, &current) == 0)
				{
					if (keyEqual (current, key))
						return current;
				}
			// Error Handler
		}
	return NULL;
}

static int
findIndex (const ctHM_t *map, const char *key)
{
	if (map == NULL || key == NULL || map->buckets == NULL || map->bucketCount == 0)
		return -1;
	unsigned long keyHash = hash (key);
	size_t i = bucketIndex (map, keyHash);
	ctLL_t *bucket = map->buckets[i];
	if (bucket == NULL)
		return -1;
	size_t listIndex;
	ctHMEntry_t *current;
	for (listIndex = 0; listIndex < bucket->size; listIndex++)
		{
			if (ctListGet (bucket, listIndex, &current) == 0)
				if (keyEqual (current, key))
					return (int)listIndex;
			// Error Handler
		}
	return -1;
}

/* Externals */
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
	if (map == NULL)
		return 1;
	return map->size == 0;
}

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

int
ctHMContains (const ctHM_t *map, const char *key)
{
	if (map == NULL)
		return 0;
	if (findEntry (map, key) == NULL)
		return 0;
	return 1;
}

char *
ctHMGet (const ctHM_t *map, const char *key)
{
	if (map == NULL || key == NULL)
		return NULL;
	ctHMEntry_t *entry = findEntry (map, key);
	if (entry == NULL)
		return NULL;
	return entry->value;
}

/* Not Complete */
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
