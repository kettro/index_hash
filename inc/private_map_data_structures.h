#ifndef _PRIVATE_MAP_DATA_STRUCTURES_H_
#define _PRIVATE_MAP_DATA_STRUCTURES_H_
#include <stdint.h>
#include <env.h>


#define null NULL
#define MAP_BASE_SIZE       11
#define BIN_BASE_SIZE       11

typedef struct _symbol_{
    uint32_t hash;
    void* data;
    char* key;
    struct _symbol_* next;
    struct _symbol_* prev;
} Symbol;
typedef struct {
    Symbol* symbolRoot;
    uint16_t length;
    uint16_t max_length;
} ArrayBin;

#endif
