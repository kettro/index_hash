# IndexHash

A simple HashMap for C.

## Building
To build the basic test platform, run:
```
$ make
```

The library can be used with `map.h` and `map.o`, if exported.
Simply export to a lib directory in your project, point your makefile to the
.o file, and include the `map.h` file in the include directory.

## Using
To use the map, initialize it with:
```
Map* map = newMap();
```
This creates a new Map instance.

All actions of the map can be done using the provided functions in the Map's
struct. All functions require that the user pass in the map instance as the
first argument.
```
map->add(map, key, value);
map_>remove(map, key, dataDelete);
map->get(map, key);
map->set(map, key, newValue);
map->delete(map, dataDelete);
```
Values are `void*`, and keys are charact4er strings. Keys do not need to be
allocated by the user, and a character array will suffice, as long as it is a
valid string. The system will allocate its own internal keys.

When setting data to new values, it is recommended to retrieve the data
beforehand, as it will not bve freed by the system, that is left to the
programmer in this instance.

The dataDelete flag is a notice for the map, when deleting an item or itself,
to call free() on each data filed in the map. If you have malloc'd items in the
map, and cannot free them yourself, set this flag to 1. Otherwise, keep it at
0.

### Data Representation
In a move that I may or may not regret, data is stored in the map as a `void*`.
This is done to keep the system as flexible as possible, and to let it handle
any sort of object. However, this also means that it cannot store un-malloc'd
data points, unless you do something squirrelly. (You can store literals, but
there will be no type checking, and are a maximum of 64 bits in size). This
is technically undefined behavior (though I myself have done it successfully).

## Organization
Build as a "box of bins", the map uses a series of bins, each which is a linked
list. When a given bin reaches capacity, then the system will increase the
number of bins, and redistribute the nodes. This is an expensive process, but
should not happen too often.

## Hashing

It uses a hash algorithm used by sdbm via http://www.cse.yorku.ca/~oz/hash.html.
