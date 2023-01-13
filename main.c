#include "solver.h"


int main(int argc, char *argv[])
{
    size_t start_time, stop_time;               // Замер времени исполнения.

    int dim,                                    // Размерность матрицы коэффициентов системы и векторов.
        return_code;                            // Код возврата.

    double *a_matrix,                           // Матрица коэффициентов системы.
           *b_array,                            // Вектор значений свободных членов.
           *x_array;                            // Вектор значений неизвестных переменных.

    size_t index = 1;                           // Начальный индекс в массиве аргументов приложения.
    FILE *in_file = fopen("input.txt", "r"),    // Входной файл.
         *out_file = fopen("output.txt", "w");  // Выходной файл.

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
            case 'd': debug_print = 1;
            case 'p': matrix_print = 1; break;
            case 'e': errors_print = 1; break;
            case 't': time_print = 1; break;

            case 'h':
            case '?':
                help_print();

                fclose(in_file);
                fclose(out_file);

                return 0;

            default:
                if (errors_print)
                    aborting_print("Unknown option!");

                fclose(in_file);
                fclose(out_file);

                return -2;
        }

    if (!in_file || !out_file)
    {
        if (errors_print)
            aborting_print("File(s) opening error!");

        fclose(in_file);
        fclose(out_file);

        return -3;
    }

    fscanf_s(in_file, "%d", &dim);

    a_matrix = (double*)malloc(lss_memsize_28_08(dim * dim));
    b_array = (double*)malloc(lss_memsize_28_08(dim));
    x_array = (double*)malloc(lss_memsize_28_08(dim));

    if ((a_matrix == NULL) || (b_array == NULL) || (x_array == NULL))
    {
        if (errors_print)
            aborting_print("Memory allocation error!\n");

        free(a_matrix);
        free(b_array);
        free(x_array);

        fclose(in_file);
        fclose(out_file);

        return -4;
    }

    for (size_t i = 0; i < dim * dim; ++i)
        fscanf_s(in_file, "%lf", &a_matrix[i]);

    for (size_t i = 0; i < dim; ++i)
        fscanf_s(in_file, "%lf", &b_array[i]);

    if (time_print)
        start_time = clock();

    return_code = lss_28_08(dim, a_matrix, b_array, x_array, NULL);

    if (time_print)
    {
        stop_time = clock();
        printf("Working time - %zu ms.\n", stop_time - start_time);
    }

    if (!return_code)
    {
        fprintf(out_file, "%d\n", dim);

        for (int i = 0; i < dim; ++i)
            fprintf(out_file, "%.9lf\n", x_array[i]);
    }
    else
        fprintf(out_file, "%d\n", 0);

    free(a_matrix);
    free(b_array);
    free(x_array);

    fclose(in_file);
    fclose(out_file);

    return return_code;
}