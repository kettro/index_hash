// Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "map.h"
#include "map_data_structures.h"

// Hash
static ArrayBin* findArrayBinGivenHash(Map*, uint32_t);
static Symbol* findSymbolGivenHash(ArrayBin*, uint32_t);
static uint32_t hash(char*);
// Map
void _mapAdd(Map*, char*, void*);
void _mapRemove(Map*, char*);
void* _mapGet(Map*, char*);
void _mapDelete(Map*);
void _mapSet(Map*, char*, void*);
static Map* newMap_binNumbers(int);
static Map* resizeMap(Map*);
// Symbol
static Symbol* newSymbol(char*, void*);
static Symbol* getSymbol(Map*, char*);
static void deleteSymbol(Symbol*);
// Array Bin
static ArrayBin* newArrayBin();
static void deleteArrayBin(ArrayBin* self);

/*
 * NOTE:
 * I would generally prefer to have these functions split up into their
 * own files. For ease of importing it, however, I have it like this.
 */

/*** HASH ***/

static uint32_t hash(char* key)
{
    // djb2 algorithm
    uint32_t hash_val = 5481;
    int c;
    while(c = *key++){
        hash_val = ((hash_val << 5) + hash_val) + c;
    }
    return hash_val;
}

static Symbol* findSymbolGivenHash(ArrayBin* self, uint32_t hash_val)
{
    if(self == null){ return null; }
    Symbol* temp = self->symbolRoot->next;
    int i;
    for(i = 0; i < self->length; i++){
        // Naively assuming no hash collisions
        // As this is only GivenHash, not GivenHashAndKey
        if(temp->hash == hash_val){
            // found it
            return temp;
        }
        temp = temp->next;
    }
    // None found
    return null;
}

static ArrayBin* findArrayBinGivenHash(Map* self, uint32_t hash_val)
{
    int i;
    int mod = hash_val % self->bin_count;
    return ((ArrayBin**)self->array_bins)[mod];
}

/*** MAP ***/

extern Map* newMap(void)
{
    int number_bins = MAP_BASE_SIZE;
    // Now, use the bin_number to allocate that many bins.
    // allocate new Map
    Map* map = malloc(sizeof(Map));
    // allocate arrayBins, for each in the array (and all that implies)
    ArrayBin** bin_array = (ArrayBin**)malloc(number_bins * sizeof(ArrayBin));
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
    map->bin_count = number_bins;

    return map;
}

static Map* resizeMap(Map* self)
{
    // map has grown too large
    // Need to resize it
    // which means that I need to rebuild it in a new map, sorta.

    int new_num_bins = self->bin_count + MAP_BASE_SIZE;
    ArrayBin** new_bins = malloc(new_num_bins * sizeof(ArrayBin*));
    int i, j;
    for(i = 0; i < new_num_bins; i++){
        new_bins[i] = newArrayBin();
    }

    for(i = 0; i < self->bin_count; i++){
        // get all the Symbols from the bins
        ArrayBin* bin = ((ArrayBin**)self->array_bins)[i];
        for(;bin->length > 0; bin->length--){
            // Get symbol from the old bins
            Symbol* s = bin->symbolRoot->next;
            bin->symbolRoot->next = s->next;
            s->next->prev = bin->symbolRoot;
            // put into new bins
            int index = s->hash % new_num_bins;
            Symbol* root = new_bins[index]->symbolRoot;
            s->next = root->next;
            s->prev = root;
            root->next->prev = s;
            root->next = s;
            new_bins[index]->length++;
        }
        if(bin->symbolRoot != null){
            free(bin->symbolRoot);
        }
        free(bin);
        bin = null;
    }
    free(self->array_bins);
    self->array_bins = new_bins;
    self->bin_count = new_num_bins;
}


void _mapAdd(Map* self, char* key, void* data)
{
    // make new Symbol
    Symbol* s = newSymbol(key, data);
    // get the correct arrayBin
    // set volatile to protect against compiler fuckery
    volatile char index = (s->hash % self->bin_count);
    volatile ArrayBin* bin = ((ArrayBin**)self->array_bins)[index];
    if(bin->length + 1 >= bin->max_length){
        // need to resize Array
        resizeMap(self);
        index = (s->hash % self->bin_count);
        bin = ((ArrayBin**)self->array_bins)[index];
    }
    // add the new dude into the picture
    s->prev = bin->symbolRoot;
    s->next = bin->symbolRoot->next;
    bin->symbolRoot->next->prev = s;
    bin->symbolRoot->next = s;
    bin->length++;
    self->length++;
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

/*** SYMBOL ***/

static Symbol* newSymbol(char* key, void* data)
{
    // allocate space for key and data
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->key = (char*)malloc(sizeof(char) * strlen(key));
    strcpy(symbol->key, key);
    symbol->data = data;
    symbol->hash = hash(key);
    symbol->prev = null;
    symbol->next = null;
    return symbol;
}

static Symbol* getSymbol(Map* self, char* key)
{
    // get the hash
    uint32_t hash_val = hash(key);
    // get the ArrayBin
    ArrayBin* bin = findArrayBinGivenHash(self, hash_val);
    if(bin == null){ return null; }
    // finally get the symbol
    Symbol* symbol = findSymbolGivenHash(bin, hash_val);
    return symbol; // if the symbol is null, then it's null
}

static void deleteSymbol(Symbol* symbol)
{
    if(symbol == null){ return; }
    Symbol* tprev = symbol->prev;
    Symbol* tnext = symbol->next;
    tprev->next = tnext;
    tnext->prev = tprev;
    if(symbol->key != null){
        free(symbol->key);
        symbol->key = null;
    }
    // DO NOT FREE THE DATA: UP TO THE PROGRAMMER
    free(symbol);
    symbol = null;
}

/*** ARRAY BIN ***/

static void deleteArrayBin(ArrayBin* self)
{
    // call delete on all the symbols in the bins
    Symbol* root = self->symbolRoot;
    Symbol* s = root->next;
    Symbol* next = null;
    for(; self->length > 0; self->length--){
        deleteSymbol(root->next);
    }
    // then free the arrays of each bin
    if( self->symbolRoot != null){
        free(self->symbolRoot);
        self->symbolRoot = null;
    }
    // then free the arraybin itself
    free(self);
    self = null;
}

static ArrayBin* newArrayBin()
{
    // allocate an ArrayBin
    ArrayBin* bin = null;
    bin = (ArrayBin*)calloc(1, sizeof(ArrayBin));
    bin->length = 0;
    bin->max_length = (uint16_t)(BIN_BASE_SIZE/2 + 1);

    // allocate an array of Symbols
    // using calloc  to init to 0
    bin->symbolRoot = (Symbol*)calloc(1, sizeof(Symbol));
    bin->symbolRoot->next = bin->symbolRoot;
    bin->symbolRoot->prev = bin->symbolRoot;
    // return the ArrayBin pointer

    return bin;
}
