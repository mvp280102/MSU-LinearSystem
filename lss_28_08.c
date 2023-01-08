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

double l_sum(int n, int i, int k, const double *A)
{
    double res = 0;

    for (int j = 0; j < k; ++j)
        res += A[i * n + j] * A[j * n + k];

    return res;
}

double u_sum(int n, int i, int k, const double *A)
{
    double res = 0;

    for (int j = 0; j < i; ++j)
        res += A[i * n + j] * A[j * n + k];

    return res;
}

void lu_decomposition(int n, double *A)
{
    for (int k = 1; k < n; ++k)
        A[k] /= A[0];

    if (matrix_print)
        l_u_matrix_print(0, n, A);

    for (int i = 1; i < n; ++i)
        for (int j = i; j < n; ++j)
        {
            if (matrix_print)
            {
                l_u_matrix_print(i, n, A);

            }

            A[j * n + i] -= l_sum(n, j, i, A);

            if (j < n - 1)
            {
                A[i * n + j + 1] -= u_sum(n, i, j + 1, A);
                A[i * n + j + 1] /= A[i * (n + 1)];
            }
        }
}

double x_sum(int n, int i, const double *A, const double *X)
{

}

double y_sum(int n, int i, const double *A, const double *Y)
{

}

void solve(int n, const double *A, const double *B, double *X)
{

}

void l_matrix_print(int n, const double *A)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf("%.4lf\t", i >= j ? A[i * n + j] : 0);

        printf("\n");
    }
}

void u_matrix_print(int n, const double *A)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf("%.4lf\t", i < j ? A[i * n + j] : i == j ? 1 : 0);

        printf("\n");
    }
}

void l_u_matrix_print(int k, int n, const double *A)
{
    printf("Step %d:\n\n", k);

    printf("L matrix:\n");
    l_matrix_print(n, A);

    printf("U matrix:\n");
    u_matrix_print(n, A);

    printf("\n");
}