#ifndef _HASH_H_
#define _HASH_H_

#include <stdint.h>

// Structures

typedef struct _map_{
    void* array_bins;
    uint16_t bin_count;
    uint16_t length;

    // "Methods"
    void (*add)(struct _map_*, char*, void*);
    void (*remove)(struct _map_*, char*);
    void* (*get)(struct _map_*, char*);
    void (*delete)(struct _map_*);
}Map;

Map* newMap();

#endif
