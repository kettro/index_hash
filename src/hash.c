// Includes
#include <stdlib.h>
#include <string.h>
#include <hash.h>
#include <private_map_data_structures.h>


/*
 * So we have to build a hash. Shouldn't be too difficult.
 * Need: hashing function, to map strings => hashes.
 * Need: definitions for the function pointers defined
 * Need: constructor for the hash
 */


uint32_t hash(char* key);
static ArrayBin* newArrayBin();
static void arrayBinDelete(ArrayBin*);

void _mapAdd(Map*, char*, void*);
void _mapRemove(Map*, char*);
void* _mapGet(Map*, char*);
void _mapDelete(Map*);
static Map* newMap_binNumbers(int);
static Map* resizeMap(Map*, int);

static Symbol* newSymbol(void);
static Symbol* getSymbol(Map*, char*);

// ArrayBin methods
static ArrayBin* newArrayBin()
{
    // allocate an ArrayBin
    // allocate an array of Symbols
    // put the array of symbols in the arraybin
    // return the ArrayBin pointer

    return null;
}

static void arrayBinDelete(ArrayBin* self)
{
    // call delete on all the symbols in the bins
    // then free the arrays of each bin
    // then free the arraybin itself
}

// Symbol Methods
static Symbol* newSymbol(void)
{
    // allocate space for key and data
}

static Symbol* getSymbol(Map* self, char* key)
{
    // use the key to find the symbol
    // returnthe Symbol pointer

    return null;
}

// Map Methods
extern Map* newMap(void)
{
    return newMap_binNumbers(1);
}

static Map* newMap_binNumbers(int resize_count){
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
    map->delete = _mapDelete;
    // set the length of the map
    map->length = 0;
    // set the number of bins
    map->bin_count = resize_count;

    return map;
}

void _mapAdd(Map* self, char* key, void* data)
{
    // Add a new item to the Map
}

void _mapRemove(Map* self, char* key)
{

}

void* _mapGet(Map* self, char* key)
{
    // using the key, calculate the bin the key is in.
    // get the bin, then linear search for the correct symbol
    // return the pointer to the data in the symbol
    return null;
}

void _mapDelete(Map* self)
{
    // call delete on all arraybins
    // then free the arraybin array
    // then free self. 
}

