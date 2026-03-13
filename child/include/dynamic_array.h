/**
 * @file da.h
 * @brief Basic Data Structures
 */

/*
 * project: 01PROJTEMP
 * module: Data Structures
 * created: 2026-03-07
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

typedef struct ctDynamicArray
{
	void *data;
	size_t size;
	size_t capacity;
	size_t elementSize;
} ctDynamicArray_t;

/* Lifecycle */
int ctDynamicArrayInit (ctDynamicArray_t *da, size_t initialCapacity, size_t elementSize);
void ctDynamicArrayFree (ctDynamicArray_t *da);

/* Capacity management */
int ctDynamicArrayResize (ctDynamicArray_t *da, size_t newCapacity);
int ctDynamicArrayReserve (ctDynamicArray_t *da, size_t capacity);
int ctDynamicArrayShrinkToFit (ctDynamicArray_t *da);

/* Element operations */
int ctDynamicArrayPush (ctDynamicArray_t *da, void *element);
int ctDynamicArrayPop (ctDynamicArray_t *da, void *element);

void *ctDynamicArrayGet (const ctDynamicArray_t *da, size_t index);
int ctDynamicArraySet (ctDynamicArray_t *da, size_t index, void *element);

int ctDynamicArrayInsert (ctDynamicArray_t *da, size_t index, void *element);
int ctDynamicArrayRemove (ctDynamicArray_t *da, size_t index, void *element);

/* Add a find() function */

/* State / utilities */
size_t ctDynamicArraySize (const ctDynamicArray_t *da);
size_t ctDynamicArrayCapacity (const ctDynamicArray_t *da);
void ctDynamicArrayClear (ctDynamicArray_t *da);

#endif // DYNAMIC_ARRAY_H
