/**
 * @file da.c
 * @brief Dynamic Arrays and Stacks
 */

/*
 * project: 01PROJTEMP
 * module: Data Structures
 * created: 2026-03-07
 * SPDX-License-Identifier: GPL-3.0-or-later
 * author: Tim Palmer
 */

#include "dynamic_array.h"
#include <stdlib.h>
#include <string.h>

int
ctDynamicArrayInit (ctDynamicArray_t *da, size_t initialCapacity, size_t elementSize)
{
	if (da == NULL || elementSize == 0)
		return -1;
	if (initialCapacity == 0)
		initialCapacity++;
	da->size = 0;
	da->capacity = 0;
	da->elementSize = 0;
	da->data = NULL;
	da->data = malloc (initialCapacity * elementSize);
	if (da->data == NULL)
		return -1;
	da->elementSize = elementSize;
	da->capacity = initialCapacity;
	return 0;
}

int
ctDynamicArrayResize (ctDynamicArray_t *da, size_t newCapacity)
{
	if (da == NULL || newCapacity == 0)
		return -1;
	void *tmp = realloc (da->data, newCapacity * da->elementSize);
	if (tmp == NULL)
		return -1;
	da->data = tmp;
	da->capacity = newCapacity;
	// Truncates to smaller sizes
	da->size = da->size > da->capacity ? da->capacity : da->size;
	return 0;
}

int
ctDynamicArrayReserve (ctDynamicArray_t *da, size_t capacity)
{
	if (da == NULL)
		return -1;
	if (da->capacity >= capacity)
		return 0;
	void *tmp = realloc (da->data, capacity * da->elementSize);
	if (tmp == NULL)
		return -1;
	da->data = tmp;
	da->capacity = capacity;
	return 0;
}

int
ctDynamicArrayShrinkToFit (ctDynamicArray_t *da)
{
	if (da == NULL)
		return -1;
	if (da->capacity == da->size)
		return 0;
	if (da->size == 0)
		{
			ctDynamicArrayFree (da);
			return 0;
		}
	void *tmp = realloc (da->data, da->size * da->elementSize);
	if (tmp == NULL)
		return -1;
	da->data = tmp;
	da->capacity = da->size;
	return 0;
}

int
ctDynamicArrayPush (ctDynamicArray_t *da, void *element)
{
	if (da == NULL || element == NULL)
		return -1;
	if (da->capacity == 0)
		if (ctDynamicArrayResize (da, 1) != 0)
			return -1;
	if (da->size == da->capacity)
		if (ctDynamicArrayResize (da, da->capacity * 2) != 0)
			return -1;
	memcpy ((char *)da->data + da->size * da->elementSize, element, da->elementSize);
	da->size++;
	return 0;
}

int
ctDynamicArrayPop (ctDynamicArray_t *da, void *element)
{
	if (da == NULL || da->size == 0 || element == NULL)
		return -1;
	da->size--;
	memcpy (element, (char *)da->data + da->size * da->elementSize, da->elementSize);
	memset ((char *)da->data + da->size * da->elementSize, 0, da->elementSize);
	return 0;
}

void *
ctDynamicArrayGet (const ctDynamicArray_t *da, size_t index)
{
	if (da == NULL || index >= da->size)
		return NULL;
	return (char *)da->data + index * da->elementSize;
}

int
ctDynamicArraySet (ctDynamicArray_t *da, size_t index, void *element)
{
	if (da == NULL || index >= da->size || element == NULL)
		return -1;
	memcpy ((char *)da->data + index * da->elementSize, element, da->elementSize);
	return 0;
}

void
ctDynamicArrayFree (ctDynamicArray_t *da)
{
	if (da == NULL)
		return;
	free (da->data);
	da->data = NULL;
	da->size = 0;
	da->elementSize = 0;
	da->capacity = 0;
}

int
ctDynamicArrayInsert (ctDynamicArray_t *da, size_t index, void *element)
{
	if (da == NULL || index > da->size || element == NULL)
		return -1;
	if (index == da->size)
		{
			if (ctDynamicArrayPush (da, element) != 0)
				return -1;
			return 0;
		}
	if (da->size == da->capacity)
		if (ctDynamicArrayResize (da, da->capacity * 2) != 0)
			return -1;
	size_t i = da->size - index;
	memmove ((char *)da->data + (index + 1) * da->elementSize,
			 (char *)da->data + index * da->elementSize, i * da->elementSize);
	memcpy ((char *)da->data + index * da->elementSize, element, da->elementSize);
	da->size++;
	return 0;
}

int
ctDynamicArrayRemove (ctDynamicArray_t *da, size_t index, void *element)
{
	if (da == NULL || index >= da->size || element == NULL)
		return -1;
	size_t i = da->size - index - 1;
	memcpy (element, (char *)da->data + index * da->elementSize, da->elementSize);
	memmove ((char *)da->data + index * da->elementSize,
			 (char *)da->data + (index + 1) * da->elementSize, i * da->elementSize);
	da->size--;
	memset ((char *)da->data + da->size * da->elementSize, 0, da->elementSize);
	return 0;
}

size_t
ctDynamicArraySize (const ctDynamicArray_t *da)
{
	if (da == NULL)
		return 0;
	return da->size;
}

size_t
ctDynamicArrayCapacity (const ctDynamicArray_t *da)
{
	if (da == NULL)
		return 0;
	return da->capacity;
}

void
ctDynamicArrayClear (ctDynamicArray_t *da)
{
	if (da == NULL)
		return;
	memset ((char *)da->data, 0, da->elementSize * da->size);
	da->size = 0;
}
