#ifndef _PRIVATE_MAP_H_
#define _PRIVATE_MAP_H

#include <stdint.h>
#include "map.h"
#include "arraybin.h"
#include "private_map_data_structures.h"

ArrayBin* findArrayBinGivenHash(Map*, uint32_t);
Symbol* findSymbolGivenHash(ArrayBin*, uint32_t);

#endif
