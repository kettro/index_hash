#ifndef _MAP_H_
#define _MAP_H_

#include <stdint.h>

// Structures

typedef struct _map_{
    void* array_bins;
    uint16_t bin_count;
    uint16_t length;

    // "Methods"
    void (*add)(struct _map_*, char*, void*);
    void (*remove)(struct _map_*, char*, char);
    void* (*get)(struct _map_*, char*);
    void (*set)(struct _map_*, char*, void*);
    void (*delete)(struct _map_*, char);
}Map;

Map* newMap();

#endif
