#ifndef _MAP_DATA_STRUCTURES_H_
#define _MAP_DATA_STRUCTURES_H_
#include <stdint.h>
#include <env.h>


#define null NULL
#define MAP_BASE_SIZE       11
#define BIN_BASE_SIZE       11

typedef struct _symbol_{
    uint32_t hash;
    struct _symbol_* next;
    struct _symbol_* prev;
    void* data;
    char* key;
} Symbol;

typedef struct _arraybin_{
    uint16_t length;
    uint16_t max_length;
    Symbol* symbolRoot;
} ArrayBin;

#endif
