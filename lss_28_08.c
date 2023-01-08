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
    lu_decomposition(n, A);

    for (int i = 0; i < n; ++i)
        if (A[i * (n + 1)] == 0)
        {
            if (errors_print)
            {
                printf("Given matrix is degenerate.\n");
                printf("LU-decomposition method is not applicable.\n");
            }

            return -1;
        }

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
    {
        printf("Step %d:\n\n", 0);
        l_u_matrix_print(n, A);
    }

    for (int i = 1; i < n; ++i)
    {
        if (matrix_print)
            printf("Step %d:\n\n", i);

        for (int j = i; j < n; ++j)
        {
            A[j * n + i] -= l_sum(n, j, i, A);

            if (j < n - 1)
            {
                A[i * n + j + 1] -= u_sum(n, i, j + 1, A);
                A[i * n + j + 1] /= A[i * (n + 1)];
            }

            if (matrix_print)
            {
                l_u_matrix_print(n, A);

                if (debug_print)
                {
                    printf("L subtraction sum: %.4lf\n", l_sum(n, j, i, A));
                    printf("U subtraction sum: %.4lf\n", u_sum(n, i, j + 1, A));
                    printf("\n");
                }
            }
        }
    }
}

double x_sum(int n, int i, const double *A, const double *X)
{
    double res = 0;

    for (int j = n - 1; j > i; --j)
        res += A[i * n + j] * X[j];

    return res;
}

double y_sum(int n, int i, const double *A, const double *Y)
{
    double res = 0;

    for (int j = 0; j < i; ++j)
        res += A[i * n + j] * Y[j];

    return res;
}

void solve(int n, const double *A, const double *B, double *X)
{
    for (int i = 0; i < n; ++i)
        X[i] = (B[i] - y_sum(n, i, A, X)) / A[i * (n + 1)];

    if (debug_print)
    {
        printf("Y vector:\n");
        vector_print(n, X);
        printf("\n");
    }

    for (int i = n - 1; i >= 0; --i)
        X[i] -= x_sum(n, i, A, X);

    if (debug_print)
    {
        printf("X vector:\n");
        vector_print(n, X);
    }
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

void l_u_matrix_print(int n, const double *A)
{
    printf("L matrix:\n");
    l_matrix_print(n, A);

    printf("\n");

    printf("U matrix:\n");
    u_matrix_print(n, A);

    printf("\n");
}

void vector_print(int n, const double *X)
{
    for (int i = 0; i < n; ++i)
        printf("%.4lf\t", X[i]);

    printf("\n");
}