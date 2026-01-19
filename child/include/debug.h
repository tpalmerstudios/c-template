#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
#include <stdio.h>
#define DBG(fmt, ...) fprintf (stderr, "[DEBUG %s:%d] " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define DBG(...) ((void) 0)
#endif

#endif // DEBUG_H
