#include <stdint.h>

typedef struct {
  uint16_t data;
  uint16_t location;
  char* key;
} Symbol;

typedef enum{
  FALSE = 0,
  TRUE = 1,
  NUL = '\0',
} Bool;

typedef struct {
  uint16_t* array;
  uint16_t current_size;
  uint16_t max_size
} ArrayBin;
