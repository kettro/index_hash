#ifndef _PRIVATE_MAP_DATA_STRUCTURES_H_
#define _PRIVATE_MAP_DATA_STRUCTURES_H_
#include <stdint.h>
#include <env.h>


#define null NULL
#define MAP_BASE_SIZE       11

#ifdef ENV_64BIT
typedef struct {
    uint64_t hash;
    uint64_t data;
    char* key;
} Symbol;
#else
typedef struct {
    uint32_t hash;
    uint32_t data;
    char* key;
} Symbol;

#endif
typedef struct {
    Symbol* symbolArray;
    uint16_t length;
    uint16_t max_length;
} ArrayBin;

#endif
