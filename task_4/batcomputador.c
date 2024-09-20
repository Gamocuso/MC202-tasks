#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bat-memory.h"

int main()
{

    int prompts;
    char command[10];
    bat_memory memory_data = create_memory();

    scanf("%d", &prompts);

    for (int i = 0; i < prompts; i++)
    {

        int *list_alloc;
        int address;
        int n;

        scanf("%s", command);

        if (strcmp(command, "bat-alloc") == 0)
        {
            scanf("%d", &n);
            list_alloc = malloc(n * sizeof(int));
            for (int j = 0; j < n; j++)
            {

                scanf("%d", &list_alloc[j]);
            }

            memory_data = bat_alloc(memory_data, n, list_alloc);
            free(list_alloc);
        }
        else if (strcmp(command, "bat-free") == 0)
        {

            scanf("%d", &address);

            memory_data = bat_free(memory_data, address);
        }
        else if (strcmp(command, "bat-print") == 0)
        {

            scanf("%d", &address);
            bat_print(memory_data, address);
        }
        else if (strcmp(command, "bat-uso") == 0)
        {

            bat_usage(memory_data);
        }

        for (int i = 0; i < memory_data.length; i++)
        {

            printf(" %d |", memory_data.memory[i]);
        }
        printf("\n");
    }

    free(memory_data.addresses);
    free(memory_data.memory);

    return 0;
}
