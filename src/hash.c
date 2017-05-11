#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

uint32_t hash(char* key)
{
    // djb2 algorithm
    uint32_t hash_val = 5481;
    int c;
    while(c = *key++){
        hash_val = ((hash_val << 5) + hash_val) + c;
    }
    return hash_val;
}
