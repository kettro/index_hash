#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "private_map_data_structures.h"
#include "private_map.h"
#include "map.h"
#include "hash.h"

Symbol* newSymbol(char* key, void* data)
{
    // allocate space for key and data
    Symbol* symbol = (Symbol*)malloc(sizeof(Symbol));
    symbol->key = (char*)malloc(sizeof(char) * strlen(key));
    symbol->data = data;
    symbol->hash = hash(key);
    symbol->prev = null;
    symbol->next = null;
}

Symbol* getSymbol(Map* self, char* key)
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

void deleteSymbol(Symbol* symbol)
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
    if(symbol->data != null){
        free(symbol->data);
        symbol->data = null;
    }
    free(symbol);
    symbol = null;
}
