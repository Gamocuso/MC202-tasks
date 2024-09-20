#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{

    double *coord;

} point;

void print_vector();

void read_points(point *p, int dim, int n)
{

    for (int i = 0; i < n; i++)
    {

        p[i].coord = malloc(dim * sizeof(double));

        for (int j = 0; j < dim; j++)
        {

            scanf("%lf", &p[i].coord[j]);
        }
    }
}

point centroid(point *points, int dim, int n)
{

    point cent;
    int i, j;

    cent.coord = malloc(dim * sizeof(double));

    for (j = 0; j < dim; j++)
    {

        double sum = 0;

        for (i = 0; i < n; i++)
        {

            sum += points[i].coord[j];
        }
        // por algum motivo sum resultava em -0.000 e como ha o arredondamento na terceira casa decimal no exercicio, decidi essa resolucao
        if (sum < 0.0001 && sum > -0.0001)
            sum = 0.0;

        cent.coord[j] = sum / n;
    }

    return cent;
}

void normalize_vector(double *coord, double *coord_norm, int dim, double norm)
{
    for (int j = 0; j < dim; j++)
    {

        coord_norm[j] = (coord[j] / norm);
    }
}

double get_norm(double *coord, int dim)
{

    double sqrt_sum = 0;

    for (int j = 0; j < dim; j++)
    {

        sqrt_sum += (pow(coord[j], 2));
    }

    return sqrt(sqrt_sum);
}

point centroid_norm(point *points, int dim, int n)
{

    point cent_norm;
    point *points_norm;

    points_norm = malloc(n * sizeof(point));

    for (int i = 0; i < n; i++)
    {

        double norm;
        points_norm[i].coord = malloc(dim * sizeof(double));

        norm = get_norm(points[i].coord, dim);

        normalize_vector(points[i].coord, points_norm[i].coord, dim, norm);
    }

    cent_norm = centroid(points_norm, dim, n);

    for (int j = 0; j < n; j++)
    {

        free(points_norm[j].coord);
    }

    free(points_norm);

    return cent_norm;
}

void find_min_max(point *points, double **max_min, int dim, int n)
{

    for (int j = 0; j < dim; j++)
    {
        max_min[j] = malloc(2 * sizeof(double));

        for (int i = 0; i < n; i++)
        {

            if (i == 0)
            {

                max_min[j][0] = points[i].coord[j];
                max_min[j][1] = points[i].coord[j];
            }
            else
            {

                if (max_min[j][0] < points[i].coord[j])
                {

                    max_min[j][0] = points[i].coord[j];
                }

                if (max_min[j][1] > points[i].coord[j])
                {

                    max_min[j][1] = points[i].coord[j];
                }
            }
        }
    }
}

point centroid_window(point *points, int dim, int n)
{
    double **max_min_vector;
    point *window_points;
    point cent_window;
    window_points = malloc(n * sizeof(point));
    max_min_vector = malloc(dim * sizeof(double));

    if (window_points == NULL || max_min_vector == NULL)
    {

        printf("espaco insuficiente de memoria\n");
        exit(1);
    }

    find_min_max(points, max_min_vector, dim, n);

    for (int i = 0; i < n; i++)
    {
        window_points[i].coord = malloc(dim * sizeof(double));

        for (int j = 0; j < dim; j++)
        {

            double min = max_min_vector[j][1];
            double max = max_min_vector[j][0];
            double zero_value = (max + min) / 2;

            if (min != max)
            {

                window_points[i].coord[j] = (points[i].coord[j] - zero_value) / (zero_value - min);
            }
            else
            {

                window_points[i].coord[j] = 0.0;
            }
        }
    }

    cent_window = centroid(window_points, dim, n);

    for (int i = 0; i < dim; i++)
    {

        free(max_min_vector[i]);
    }

    for (int j = 0; j < n; j++)
    {

        free(window_points[j].coord);
    }

    free(max_min_vector);
    free(window_points);

    return cent_window;
}

void print_vector(double *coord, int dim)
{

    for (int j = 0; j < dim; j++)
    {

        printf("%.3lf ", coord[j]);
    }

    printf("\n");
}

int main()
{

    int dim, n;
    point *points;
    point cent, cent_window, cent_norm;

    scanf("%d %d", &dim, &n);
    points = malloc(n * sizeof(point));

    if (points == NULL)
    {
        printf("espaco insuficiente na memoria!\n");
        exit(1);
    }

    read_points(points, dim, n);

    cent = centroid(points, dim, n);
    cent_norm = centroid_norm(points, dim, n);
    cent_window = centroid_window(points, dim, n);

    for (int i = 0; i < n; i++)
    {

        free(points[i].coord);
    }

    free(points);

    for (int i = 0; i < 3; i++)
    {
        switch (i)
        {
        case 0:
            printf("nenhum: ");
            print_vector(cent.coord, dim);
            free(cent.coord);
            break;
        case 1:
            printf("janela: ");
            print_vector(cent_window.coord, dim);
            free(cent_window.coord);
            break;
        default:
            printf("normal: ");
            print_vector(cent_norm.coord, dim);
            free(cent_norm.coord);
            break;
        }
    }

    return 0;
}
