#include <stdio.h>
#define PROB 0.1667

double recompensa(int n, int x)
{

    double poss = 0.0;

    for (int i = 1; i <= 6; i++)
    {

        if (x - i == 0)
        {

            poss += PROB;
            return poss;
        }
        else if (x - i > 0 && n - 1 > 0)
        {

            poss += PROB * recompensa(n - 1, x - i);
        }
    }

    return poss;
}

int main()
{

    int n, x;

    scanf("%d %d", &n, &x);

    double probabilidade = recompensa(n, x);

    printf("%.3lf\n", probabilidade);

    return 0;
}