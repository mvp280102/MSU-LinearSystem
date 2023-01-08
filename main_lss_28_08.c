#include "lss_28_08.h"


int main(int argc, char *argv[])
{
    size_t start_time, stop_time;

    int dim, error_code = 0;
    double *a_matrix, *b_array, *x_array;

    size_t index = 1;
    FILE *in_file = fopen("lss_28_08_in.txt", "r"),
         *out_file = fopen("lss_28_08_out.txt", "w");

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
                return error_code;

            default:
                if (errors_print)
                    printf("Unknown option: %s.\n", argv[i]);

                error_code = 2;
        }

    if (!in_file || !out_file)
    {
        if (errors_print)
            printf("File(s) opening error!\n");

        error_code = 3;
    }

    if (error_code)
    {
        printf("Aborting application!\n");
        return error_code;
    }

    fscanf(in_file, "%d", &dim);

    a_matrix = (double*)malloc(lss_memsize_28_08(dim * dim));
    b_array = (double*)malloc(lss_memsize_28_08(dim));
    x_array = (double*)malloc(lss_memsize_28_08(dim));

    for (size_t i = 0; i < dim * dim; ++i)
        fscanf(in_file, "%lf", &a_matrix[i]);

    for (size_t i = 0; i < dim; ++i)
        fscanf(in_file, "%lf", &b_array[i]);

    if (time_print)
        start_time = clock();

    error_code = lss_28_08(dim, a_matrix, b_array, x_array, NULL);

    if (time_print)
    {
        stop_time = clock();
        printf("Working time - %zu ms.\n", stop_time - start_time);
    }

    if (!error_code)
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

    fclose(out_file);
    fclose(in_file);

    return error_code;
}
