#include <stdio.h>
#include <stdlib.h>
#include "bat-memory.h"

bat_memory create_memory()
{

    bat_memory memory_data;
    memory_data.addresses = malloc(8 * sizeof(int));
    memory_data.memory = malloc(8 * sizeof(int));
    memory_data.length = 8;
    memory_data.usage_addr = 0;
    return memory_data;
}

void address_alloc(int *addresses, int usage_addr, int *addr_alloc)
{
    // função que adiciona um novo endereço alocado no vetor dinâmico ordenado de endereços alocados

    int j = usage_addr - 1;
    int i = addr_alloc[0];

    for (; i <= j; j--)
    {

        addresses[j + 1] = addresses[j];
    }

    addresses[i] = addr_alloc[1];
}

int find_memory_space(bat_memory memory_data, int n, int *addr_alloc)
{
    // acha um espaço possível de se alocar o conteúdo requerido

    // primeiro analisa do início da memória até o primeiro endereço alocado
    // depois analisa entre os endereços alocados
    // e por último analisa o espaço entre o último endereço alocado e o ultimo espaço do vetor memória

    // addr alloc indica no primeiro índice o local onde o endereço ficará no vetor ordenado de endereços
    // e no segundo índice representa o endereço na memória

    int usage_add = memory_data.usage_addr;
    int *memory = memory_data.memory;
    int *addresses = memory_data.addresses;
    int i;

    if ((usage_add == 0 && memory_data.length > n) || addresses[0] > n)
    {

        addr_alloc[1] = 0;
        addr_alloc[0] = 0;
        return 1;
    }

    for (i = 0; i < usage_add - 1; i++)
    {

        int addr_1 = addresses[i];
        int addr_2 = addresses[i + 1];

        if (addr_2 - addr_1 - memory[addr_1] - 1 > n)
        {

            addr_alloc[1] = addr_1 + memory[addr_1] + 1;
            addr_alloc[0] = i + 1;
            return 1;
        }
    }

    int last_addr = addresses[i];

    if (memory_data.length - 1 - last_addr - memory[last_addr] > n)
    {

        addr_alloc[1] = last_addr + memory[last_addr] + 1;
        addr_alloc[0] = i + 1;
        return 1;
    }

    addr_alloc[1] = -1;
    return 0;
}

bat_memory duplicate_space(bat_memory memory_data)
{
    // apenas duplica o tamanho do vetor memória e copia os itens antes alocados

    bat_memory new_memory_data;
    new_memory_data.length = memory_data.length * 2;
    new_memory_data.memory = malloc(new_memory_data.length * sizeof(int));
    new_memory_data.addresses = malloc(new_memory_data.length * sizeof(int));
    new_memory_data.usage_addr = memory_data.usage_addr;

    for (int i = 0; i < memory_data.usage_addr; i++)
    {

        int addr = memory_data.addresses[i];
        new_memory_data.addresses[i] = addr;

        for (int j = 0; j <= memory_data.memory[addr]; j++)
        {

            new_memory_data.memory[j + addr] = memory_data.memory[j + addr];
        }
    }

    free(memory_data.addresses);
    free(memory_data.memory);

    return new_memory_data;
}

bat_memory bat_alloc(bat_memory memory_data, int n, int *list)
{
    // procura espaço de memória até poder alocar a lista requerida

    int *addr_alloc;
    addr_alloc = malloc(2 * sizeof(int));
    addr_alloc[1] = -1;
    while (addr_alloc[1] == -1)
    {

        int res = find_memory_space(memory_data, n, addr_alloc);
        if (res == 1)
        {

            address_alloc(memory_data.addresses, memory_data.usage_addr, addr_alloc);
            printf("%d\n", addr_alloc[1]);
            memory_data.usage_addr++;
            int addr = addr_alloc[1];

            memory_data.memory[addr] = n;
            addr += 1;

            for (int i = 0; i < n; i++)
            {

                memory_data.memory[addr] = list[i];
                addr += 1;
            }
        }
        else
        {

            memory_data = duplicate_space(memory_data);
        }
    }

    free(addr_alloc);
    return memory_data;
}

bat_memory reduce_half_memory(bat_memory memory_data)
{
    // quando possível, reduz o tamanho do vetor pela metade para poupar memória

    bat_memory new_memory_data;
    new_memory_data.length = memory_data.length / 2;
    new_memory_data.memory = malloc(new_memory_data.length * sizeof(int));
    new_memory_data.addresses = malloc(new_memory_data.length * sizeof(int));
    new_memory_data.usage_addr = memory_data.usage_addr;

    for (int i = 0; i < memory_data.usage_addr; i++)
    {

        int addr = memory_data.addresses[i];
        new_memory_data.addresses[i] = addr;

        for (int j = 0; j <= memory_data.memory[addr]; j++)
        {

            new_memory_data.memory[j + addr] = memory_data.memory[j + addr];
        }
    }

    free(memory_data.addresses);
    free(memory_data.memory);

    return new_memory_data;
}

bat_memory bat_free(bat_memory memory_data, int address)
{
    // remove o endereço requerido do vetor dinâmico ordenado de endereços alocados

    int usage_addr = memory_data.usage_addr;
    int i;

    for (i = 0; memory_data.addresses[i] != address; i++)
        ;

    for (; i < usage_addr - 1; i++)
    {

        memory_data.addresses[i] = memory_data.addresses[i + 1];
    }
    memory_data.addresses[i] = 0;

    memory_data.usage_addr--;

    int last_address = memory_data.addresses[i - 1];

    while (last_address + memory_data.memory[last_address] < memory_data.length / 4 && memory_data.length > 8)
    {

        memory_data = reduce_half_memory(memory_data);
    }

    return memory_data;
}

void bat_print(bat_memory memory_data, int address)
{

    for (int i = 1; i <= memory_data.memory[address]; i++)
    {

        printf("%d ", memory_data.memory[address + i]);
    }

    printf("\n");
}

void bat_usage(bat_memory memory_data)
{

    int usage_addr = memory_data.usage_addr;

    int usage = 0;

    for (int i = 0; i < usage_addr; i++)
    {

        int addr = memory_data.addresses[i];

        usage += 1 + memory_data.memory[addr];
    }

    printf("%d de %d\n", usage, memory_data.length);
}