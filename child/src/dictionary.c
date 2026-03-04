/**
 * @file dictionary.c
 * @brief Module for a hash map implementation
 */

/*
 * project: C-Template
 * module: dictionary
 * created: 2026-03-03
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */

#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

// The famous DJB2 hash function
// hash = hash * 33 + c
// Beware of numbers larger than the table size
// Modulo to table size
unsigned long
hash (const char *str)
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}

hashTable *
initHashTable (size_t maxSize)
{
	hashTable *ht = malloc (sizeof (hashTable));
	if (!ht)
		return NULL;
	ht->size = maxSize;
	ht->buckets = calloc (ht->size, sizeof (Entry *));
	if (!ht->buckets)
		{
			free (ht);
			return NULL;
		}

	return ht;
}

int
insertHT (hashTable *ht, const char *key, const char *value)
{
	if (!ht || !key || !value)
		return -1;

	size_t i = hash (key) % ht->size;
	Entry *newBucket = malloc (sizeof (Entry));
	if (!newBucket)
		return -1;

	newBucket->key = NULL;
	newBucket->value = NULL;
	newBucket->key = strdup (key);
	newBucket->value = strdup (value);

	if (!newBucket->key || !newBucket->value)
		{
			free (newBucket->key);
			free (newBucket->value);
			free (newBucket);
			return -1;
		}

	newBucket->next = ht->buckets[i];
	ht->buckets[i] = newBucket;
	return 0;
}

const char *
getHT (hashTable *ht, const char *key)
{
	if (!ht || !key)
		return NULL;

	size_t i = hash (key) % ht->size;
	Entry *current = ht->buckets[i];

	while (current)
		{
			if (strcmp (current->key, key) == 0)
				return current->value;
			// Ensures that we go to the next item if we have duplicate indexes
			current = current->next;
		}

	return NULL;
}

// Using ** makes sure we delete their pointer as well
void
freeHashTable (hashTable **ht)
{
	if (!ht || !*ht)
		return;
	hashTable *table = *ht;
	size_t i;

	for (i = 0; i < table->size; i++)
		{
			Entry *current = table->buckets[i];
			while (current)
				{
					Entry *temp = current;
					current = current->next;
					free (temp->key);
					free (temp->value);
					free (temp);
				}
		}
	free (table->buckets);
	free (table);
	*ht = NULL;
}
