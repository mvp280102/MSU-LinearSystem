#include "lss_28_08.h"

size_t debug_print = 0;
size_t errors_print = 0;
size_t matrix_print = 0;
size_t time_print = 0;

size_t lss_memsize_28_08(int n)
{
    return n * sizeof(double);
}

int lss_28_08(int n, double *A, double *B, double *X, double *tmp)
{
    // [i][j] = i * n + j

    return 0;
}