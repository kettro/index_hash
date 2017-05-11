// Includes
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "hash.h"
#include "private_map_data_structures.h"
#include "private_map.h"
#include "symbol.h"

void _mapAdd(Map*, char*, void*);
void _mapRemove(Map*, char*);
void* _mapGet(Map*, char*);
void _mapDelete(Map*);
void _mapSet(Map*, char*, void*);
static Map* newMap_binNumbers(int);
static Map* resizeMap(Map*, int);

Symbol* findSymbolGivenHash(ArrayBin* self, uint32_t hash_val)
{
    if(self == null){ return null; }
    Symbol* temp = self->symbolRoot->next;
    int i;
    for(i = 0; i < self->length; i++){
        if(temp->hash == hash_val){
            // found it
            return temp;
        }
        temp = temp->next;
    }
    // None found
    return null;
}

// Map Methods
extern Map* newMap(void)
{
    return newMap_binNumbers(1);
}

static Map* newMap_binNumbers(int resize_count)
{
    int number_bins = resize_count * MAP_BASE_SIZE;
    // Now, use the bin_number to allocate that many bins.
    // allocate new Map
    Map* map = malloc(sizeof(Map));
    // allocate arrayBins, for each in the array (and all that implies)
    ArrayBin** bin_array = (ArrayBin**)malloc(number_bins * sizeof(ArrayBin*));
    int i;
    for(i = 0; i < number_bins; i++){
        bin_array[i] = (ArrayBin*)newArrayBin();
    }
    map->array_bins = bin_array;
    // insert appropriate functions into the struct
    map->add = _mapAdd;
    map->remove= _mapRemove;
    map->get = _mapGet;
    map->set = _mapSet;
    map->delete = _mapDelete;
    // set the length of the map
    map->length = 0;
    // set the number of bins
    map->bin_count = resize_count;

    return map;
}

ArrayBin* findArrayBinGivenHash(Map* self, uint32_t hash_val)
{
    int i;
    int mod = hash_val % self->bin_count;
    return ((ArrayBin**)self->array_bins)[mod];
}

void _mapAdd(Map* self, char* key, void* data)
{
    // Add a new item to the Map
    // If the arraybin is oversized, then we need to resize
    // get the hash from the key;
    // ensure to increment the of both the array bin as well as the map
}

void _mapRemove(Map* self, char* key)
{
    if(self->length == 0){ return; }
    uint32_t hash_val = hash(key);
    ArrayBin* bin = findArrayBinGivenHash(self, hash_val);
    Symbol* symbol = findSymbolGivenHash(bin, hash_val);
    if(symbol == null){ return; }
    bin->length--;
    self->length--;
}

void* _mapGet(Map* self, char* key)
{
    if(self->length == 0){ return null; }
    Symbol* symbol = getSymbol(self, key);
    if(symbol == null){ return null; }
    // return the pointer to the data in the symbol
    return symbol->data;
}

void _mapSet(Map* self, char* key, void* data)
{
    Symbol* symbol = getSymbol(self, key);
    if(symbol == null){ return; }
    symbol->data = data;
}

void _mapDelete(Map* self)
{
    // call delete on all arraybins
    int i;
    for(i = 0; i < self->bin_count; i++){
        deleteArrayBin(((ArrayBin**)self->array_bins)[i]);
    }
    // then free the arraybin array
    free(self->array_bins);
    self->array_bins = null;
    // then free self.
    free(self);
    self = null;
}
