#include <stdint.h>
#include <stdlib.h>
#include "map.h"
#include "private_map_data_structures.h"
#include "arraybin.h"
#include "hash.h"
#include "symbol.h"

void deleteArrayBin(ArrayBin* self)
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

ArrayBin* newArrayBin()
{
    // allocate an ArrayBin
    ArrayBin* bin = (ArrayBin*)malloc(sizeof(ArrayBin));
    bin->length = 0;
    bin->max_length = (uint16_t)(BIN_BASE_SIZE/2 + 1);
    // allocate an array of Symbols
    // using calloc  to init to 0
    bin->symbolRoot = (Symbol*)malloc(sizeof(Symbol*));
    bin->symbolRoot->next = bin->symbolRoot;
    bin->symbolRoot->prev = bin->symbolRoot;
    // return the ArrayBin pointer

    return bin;
}
