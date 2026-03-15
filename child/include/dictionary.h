/**
 * @file dictionary.h
 * @brief Module for a hash map
 */

/*
 * project: C-Template
 * module: dictionary
 * created: 2026-03-03
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */
#ifndef DICTIONARY_H
#define DICTIONARY_H

// For size_t
#include <stddef.h>

typedef struct hashTable hashTable;

hashTable *initHashTable (size_t maxSize);

int insertHT (hashTable *ht, const char *key, const char *value);

const char *getHT (hashTable *ht, const char *key);

void freeHashTable (hashTable **ht);

#endif // DICTIONARY_H
