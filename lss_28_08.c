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

    lu_decomposition(n, A);
    solve(n, A, B, X);

    return 0;
}

double l_sum(int n, size_t i, size_t k, const double *A)
{
    double res = 0;

    for (size_t j = 0; j < k; ++j)
        res += A[i * n + j] * A[j * n + k];

    return res;
}

double u_sum(int n, size_t i, size_t k, const double *A)
{
    double res = 0;

    for (size_t j = 0; j < i; ++j)
        res += A[i * n + j] * A[j * n + k];

    return res;
}

void lu_decomposition(int n, double *A)
{
    for (size_t k = 1; k < n; ++k)
        A[k] /= A[0];

    for (size_t i = 1; i < n; ++i)
        for (size_t j = i; j < n; ++j)
        {
            A[j * n + i] -= l_sum(n, j, i, A);

            if (j < n - 1)
            {
                A[i * n + j + 1] -= u_sum(n, i, j + 1, A);
                A[i * n + j + 1] /= A[i * (n + 1)];
            }
        }
}

double x_sum(int n, size_t i, const double *A, const double *X)
{
    double res = 0;

    for (size_t j = n - 1; j > i + 1; --j)
        res += A[i * n + j] * X[j];

    return res + X[i];
}

double y_sum(int n, size_t i, const double *A, const double *Y)
{
    double res = 0;

    for (size_t j = 0; j < n; ++j)
        res += A[i * n + j] * Y[j];

    return res;
}

void solve(int n, const double *A, const double *B, double *X)
{

}

void print_matrix(int n, const double *matrix)
{
    for (size_t i = 0; i < n * n; ++i)
        printf("%lf ", matrix[i]);

    printf("\n");
}