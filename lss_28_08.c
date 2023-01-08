#include "lss_28_08.h"

size_t debug_print = 0;
size_t errors_print = 0;
size_t matrix_print = 0;
size_t time_print = 0;


//// ОСНОВНЫЕ ФУНКЦИИ:

size_t lss_memsize_28_08(int n)
{
    return n * sizeof(double);
}

int lss_28_08(int n, double *A, double *B, double *X, double *tmp)
{
    lu_decomposition(n, A);

    for (int i = 0; i < n; ++i)
        if (fabs(A[i * (n + 1)]) < EPS)
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


//// ФУНКЦИИ LU-РАЗЛОЖЕНИЯ МАТРИЦЫ:

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


//// ФУНКЦИИ РЕШЕНИЯ СИСТЕМЫ ЛИНЕЙНЫХ УРАВНЕНИЙ:

// Возвращает сумму произведений вычисленных на данный момент
// значений неизвестных переменных на их коэффициенты, используя
// обратный ход метода Гаусса на верхней треугольной матрице U.
double x_sum(int n, int i, const double *A, const double *X)
{
    double res = 0;

    for (int j = n - 1; j > i; --j)
        res += A[i * n + j] * X[j];

    return res;
}

// Возвращает сумму произведений вычисленных на данный момент
// значений неизвестных переменных на их коэффициенты, используя
// прямой ход метода Гаусса на нижней треугольной матрице L.
double y_sum(int n, int i, const double *A, const double *Y)
{
    double res = 0;

    for (int j = 0; j < i; ++j)
        res += A[i * n + j] * Y[j];

    return res;
}

// Решает систему линейных уравнений, используя LU-разложение матрицы коэффициентов.
// После выполнения массив значений неизвестных переменных X содержит решение системы.
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


//// ФУНКЦИИ ВЫВОДА ВЕКТОРОВ И МАТРИЦ LU-РАЗЛОЖЕНИЯ:

// Выводит на экран в одной строке вектор значений.
void vector_print(int n, const double *X)
{
    for (int i = 0; i < n; ++i)
        printf("%.4lf\t", X[i]);

    printf("\n");
}

// Выводит на экран матрицу L, т. е. нижний треугольник
// матрицы коэффициентов с ее главной диагональю.
void l_matrix_print(int n, const double *A)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf("%.4lf\t", i >= j ? A[i * n + j] : 0);

        printf("\n");
    }
}

// Выводит на экран матрицу U, т. е. верхний треугольник
// матрицы коэффициентов с единичной главной диагональю.
void u_matrix_print(int n, const double *A)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
            printf("%.4lf\t", i < j ? A[i * n + j] : i == j ? 1 : 0);

        printf("\n");
    }
}

// Выводит на экран матрицы L и U.
void l_u_matrix_print(int n, const double *A)
{
    printf("L matrix:\n");
    l_matrix_print(n, A);

    printf("\n");

    printf("U matrix:\n");
    u_matrix_print(n, A);

    printf("\n");
}


//// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ:

// Выводит на экран справочное сообщение.
void help_print()
{
    printf("Usage: lss [input_file_name] [output_file_name] [options]\n");
    printf("Where options include:\n");
    printf("\t-d\tprint debug messages [default OFF]\n");
    printf("\t-p\tprint matrix [default OFF]\n");
    printf("\t-e\tprint errors [default OFF]\n");
    printf("\t-t\tprint execution time [default OFF]\n");
    printf("\t-h, -?\tprint help and exit\n");
    printf("Default input_file_name value is lss_28_08_in.txt, default output_file_name value is lss_28_08_out.txt.\n");
}