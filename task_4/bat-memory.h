#include <stdio.h>

typedef struct bat_memory
{

    int *memory;
    int *addresses;
    int usage_addr;
    int length;

} bat_memory;

bat_memory create_memory();

bat_memory bat_alloc(bat_memory data_memory, int n, int *list);

bat_memory bat_free(bat_memory memory_data, int address);

void bat_print(bat_memory memory_data, int address);

void bat_usage(bat_memory memory_data);
