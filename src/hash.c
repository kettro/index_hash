// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "hash_data_structures.h"
// Constants
#define BASE_SIZE       11
// Local Variables
// Local Function Defintions
uint32_t hash(char* key);
// External Variables
// External Function Defintions
// Definitions

uint32_t hash(char* key)
{
  // hash function by sdbm; 
  uint32_t hash = 0;
  int c;
  while(c = *key++){
    hash = c + (hash << 6) + (hash << 16) - hash;
  }
  return hash;
}

void init_hash()
{
  ArrayBin* arrayBin = malloc(BASE_SIZE * sizeof(ArrayBin));
}

Bool add(Symbol* symbol)
{

}
