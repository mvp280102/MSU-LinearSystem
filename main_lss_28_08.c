// LU-разложение.
// Вместо вычисления определителя можно проверять на равенство нулю элементов главной диагонали матрицы U.
// Вместо двух матриц L и U можно хранить все это в одной матрице.

#include "lss_28_08.h"

int main(int argc, char *argv[])
{
    size_t start_time, stop_time;

    int dim, error_code;
    double *a_matrix, *b_array, *x_array;

    size_t index = 1;
    FILE *in_file = fopen("lss_00_00_in.txt", "r"),
         *out_file = fopen("lss_00_00_out.txt", "w");

    if ((argc > 1) && (argv[1][0] != '-'))
    {
        in_file = fopen(argv[1], "r");
        ++index;
    }

    if ((argc > 2) && (argv[2][0] != '-'))
    {
        out_file = fopen(argv[2], "w");
        ++index;
    }

    for (size_t i = index; i < argc; ++i)
        switch (argv[i][1])
        {
            case 'd': debug_print = 1; break;
            case 'e': errors_print = 1; break;
            case 'p': matrix_print = 1; break;
            case 't': time_print = 1; break;

            default:
                printf("Ignoring unknown option: -%c.\n", argv[i][1]);
        }

    if (!in_file || !out_file)
    {
        printf("Aborting application!\n");
        exit(1);
    }

    fscanf_s(in_file, "%d", &dim);

    a_matrix = (double*)malloc(lss_memsize_28_08(dim * dim));
    b_array = (double*)malloc(lss_memsize_28_08(dim));
    x_array = (double*)malloc(lss_memsize_28_08(dim));

    for (size_t i = 0; i < dim * dim; ++i)
        fscanf_s(in_file, "%lf", &a_matrix[i]);

    for (size_t i = 0; i < dim; ++i)
        fscanf_s(in_file, "%lf", &b_array[i]);

    if (time_print)
        start_time = clock();

    error_code = lss_28_08(dim, a_matrix, b_array, x_array, NULL);

    if (time_print)
    {
        stop_time = clock();
        printf("Working time - %zu ms.\n", stop_time - start_time);
    }

    for (size_t i = 0; i < dim; ++i)
    {
        for (size_t j = 0; j < dim; ++j)
            printf("%.4lf\t", a_matrix[i * dim + j]);

        printf("\n");
    }

    free(a_matrix);
    free(b_array);
    free(x_array);

    fclose(out_file);
    fclose(in_file);

    return error_code;
}
