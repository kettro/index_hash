#include <map.h>
#include <stdlib.h>
#include <stdio.h>

extern void testSuite(void)
{
    Map* new_map = newMap();
    char* value = malloc(2);
    *value = 23;
    new_map->add(new_map, "key1", value);
    char* recovered = new_map->get(new_map, "key1");
    printf("Recovered = %d\n", *recovered);
    new_map->remove(new_map, "key1");
    free(value);
    printf("Item removed from new_map\n");
    printf("length of Map = %d\n", new_map->length);

    uint64_t newVal = 583820;
    new_map->add(new_map, "newKey", &newVal);
    uint64_t* newRecovery = (uint64_t*)new_map->get(new_map, "newKey");
    printf("newRecovery = %lu\n", *newRecovery);
    printf("new length of map after insertion = %d\n", new_map->length);
    uint32_t newnewVal = 2345245;
    new_map->set(new_map, "newKey", &newnewVal);
    uint32_t* newnewRecovery = (uint32_t*)new_map->get(new_map, "newKey");
    printf("newnewRecovery = %u\n", *newnewRecovery);



}
