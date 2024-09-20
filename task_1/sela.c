#include <stdio.h>

void read_matrix(int matrix[][100], int line_s, int col_s)
{
    int i, j;

    for (i = 0; i < line_s; i++)
    {

        for (j = 0; j < col_s; j++)
        {

            scanf("%d", &matrix[i][j]);
        }
    }
}

void find_sela(int matrix[][100], int line_s, int col_s, int answer[])
{

    int i, j;

    for (i = 0; i < line_s; i++)
    {

        int lower_term = matrix[i][0];
        int not_unic;
        int aux_col = 0;

        for (j = 0; j < col_s; j++)
        {
            if (lower_term > matrix[i][j])
            {
                aux_col = j;
                lower_term = matrix[i][j];
            }
            else if (lower_term == matrix[i][j] && j != 0)
            {
                not_unic = lower_term;
            }
        }

        if (lower_term == not_unic)
            continue;

        int answ = 1;

        for (int line = 0; line < line_s; line++)
        {

            if (lower_term <= matrix[line][aux_col] && line != i)
            {
                answ = 0;
                break;
            }
        }

        if (answ)
        {
            answer[0] = i;
            answer[1] = aux_col;
            answer[2] = matrix[i][aux_col];
            break;
        }
    }
}

int main()
{

    int line_s, col_s;
    int matrix[100][100];
    int asnwer[3];

    asnwer[0] = -1;

    scanf("%d %d", &line_s, &col_s);

    read_matrix(matrix, line_s, col_s);
    find_sela(matrix, line_s, col_s, asnwer);
    if (asnwer[0] == -1)
    {
        printf("nao existe ponto de sela\n");
    }
    else
    {
        printf("(%d, %d) eh ponto de sela com valor %d\n", asnwer[0], asnwer[1], asnwer[2]);
    }

    return 0;
}
