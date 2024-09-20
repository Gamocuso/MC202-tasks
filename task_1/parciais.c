#include <stdio.h>

void read_sequence(int sequence[], int n)
{

    int number, i;

    for (i = 0; i < n; i++)
    {

        scanf("%d ", &number);
        sequence[i] = number;
    }
}

void parcial_sum(int sequence[], int sum_sequence[], int n)
{
    sum_sequence[0] = sequence[0];

    for (int i = 1; i < n; i++)
    {
        sum_sequence[i] = sequence[i] + sum_sequence[i - 1];
    }
}

void invert_sequence(int inv_sequence[], int sum_sequence[], int n)
{

    int j = n - 1;

    for (int i = 0; i < n; i++)
    {

        inv_sequence[j] = sum_sequence[i];
        j--;
    }
}

int main()
{

    int n, i;
    int sequence[1000];
    int sum_sequence[1000];
    int inv_sequence[1000];

    scanf("%d", &n);

    read_sequence(sequence, n);
    parcial_sum(sequence, sum_sequence, n);
    invert_sequence(inv_sequence, sum_sequence, n);

    for (i = 0; i < n; i++)
    {
        printf("%d ", inv_sequence[i]);
    }
    printf("\n");

    return 0;
}
