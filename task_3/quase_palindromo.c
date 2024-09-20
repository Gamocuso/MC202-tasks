#include <stdio.h>
#define MAX_STR 400

int almost_palindrome(char str[], int k, int left, int right)
{

    if (left >= right && k >= 0)
    {

        return 1;
    }

    if (str[left] != str[right])
    {

        k -= 2;
    }

    if (k < 0)
    {

        return 0;
    }

    return almost_palindrome(str, k, left + 1, right - 1);
}

int main()
{
    char str[MAX_STR];
    int k;
    scanf("%d", &k);
    scanf("%s", str);
    int right;

    for (int i = 0; str[i] != '\0'; i++)
        right = i;

    if (almost_palindrome(str, k, 0, right))
        printf("sim\n");
    else
        printf("nao\n");

    return 0;
}
