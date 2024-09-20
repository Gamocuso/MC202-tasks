#include <stdio.h>

void digitos(int vetor[], long int numero, int n)
{

    long int res = numero;

    for (int i = 0; i < n; i++)
    {

        vetor[i] = res % 10;
        res = res / 10;
    }
}

long int tamanho_numero(long int numero)
{

    long int res = numero, i = 0;

    do
    {
        res = res / 10;
        i++;

    } while (res > 0);

    return i;
}

int verifica_capicua(int vetor[], int n)
{

    int j = n - 1;

    for (int i = 0; i < n / 2; i++)
    {

        if (vetor[i] == vetor[j])
        {

            j--;
        }
        else
        {

            return 0;
        }
    }

    return 1;
}

int main()
{

    int qnt, i;
    scanf("%d", &qnt);

    for (i = 0; i < qnt; i++)
    {

        long int numero;
        int vetor[10];
        int n;

        scanf("%ld", &numero);
        n = tamanho_numero(numero);

        digitos(vetor, numero, n);
        if (verifica_capicua(vetor, n))
            printf("%ld eh capicua\n", numero);
        else
            printf("%ld nao eh capicua\n", numero);
    }

    return 0;
}
