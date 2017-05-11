#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include "map.h"
#include "private_map_data_structures.h"
#include <stdint.h>

Symbol* newSymbol(char*, void*);
Symbol* getSymbol(Map*, char*);
void deleteSymbol(Symbol*);

#endif
