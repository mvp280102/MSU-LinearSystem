#pragma once


#include "math.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"


// Машинный ноль.
#define EPS 1e-8


// Флаги опций.
extern size_t debug_print;              // Флаг вывода отладочных сообщений.
extern size_t errors_print;             // Флаг вывода сообщений об ошибках.
extern size_t matrix_print;             // Флаг вывода промежуточных матриц.
extern size_t time_print;               // Флаг вывода времени исполнения.


//// ОСНОВНЫЕ ФУНКЦИИ:
size_t lss_memsize_28_08(int n);
int lss_28_08(int n, double *A, double *B, double *X, double *tmp);


//// ФУНКЦИИ LU-РАЗЛОЖЕНИЯ МАТРИЦЫ:
double l_sum(int n, int i, int k, const double *A);
double u_sum(int n, int i, int k, const double *A);
void lu_decomposition(int n, double *A);


//// ФУНКЦИИ РЕШЕНИЯ СИСТЕМЫ ЛИНЕЙНЫХ УРАВНЕНИЙ:

/*
 * ОПИСАНИЕ:
 * Возвращает сумму произведений вычисленных на данный момент
 * значений неизвестных переменных на их коэффициенты, используя
 * обратный ход метода Гаусса на верхней треугольной матрице U.
 *
 * ПАРАМЕТРЫ:
 * int n - размерность матрицы LU-разложения и вектора неизвестных переменных
 * int i - индекс вычисляемого значения неизвестной переменной
 * const double *A - LU-разложение матрицы коэффициентов
 * const double *X - вектор значений неизвестных переменных
 */
double x_sum(int n, int i, const double *A, const double *X);

/*
 * ОПИСАНИЕ:
 * Возвращает сумму произведений вычисленных на данный момент
 * значений неизвестных переменных на их коэффициенты, используя
 * прямой ход метода Гаусса на нижней треугольной матрице L.
 *
 * ПАРАМЕТРЫ:
 * int n - размерность матрицы LU-разложения и вектора неизвестных переменных
 * int i - индекс вычисляемого значения неизвестной переменной
 * const double *A - LU-разложение матрицы коэффициентов
 * const double *Y - вектор значений неизвестных переменных
 */
double y_sum(int n, int i, const double *A, const double *Y);

/*
 * ОПИСАНИЕ:
 * Решает систему линейных уравнений, используя LU-разложение матрицы коэффициентов.
 * После выполнения массив значений неизвестных переменных X содержит решение системы.
 *
 * ПАРАМЕТРЫ:
 * int n - размерность матрицы LU-разложения и вектора неизвестных переменных
 * const double *A - LU-разложение матрицы коэффициентов
 * const double *B - вектор значений свободных членов
 * const double *X - вектор значений неизвестных переменных
 */
void solve(int n, const double *A, const double *B, double *X);


//// ФУНКЦИИ ВЫВОДА ВЕКТОРОВ И МАТРИЦ LU-РАЗЛОЖЕНИЯ:

/*
 * ОПИСАНИЕ:
 * Выводит на экран в одной строке вектор значений.
 *
 * ПАРАМЕТРЫ:
 * int n - длина вектора значений
 * const double *X - вектор значений
 */
void vector_print(int n, const double *X);

/*
 * ОПИСАНИЕ:
 * Выводит на экран матрицу L, т. е. нижний треугольник
 * матрицы коэффициентов с ее главной диагональю.
 *
 * ПАРАМЕТРЫ:
 * int n - размерность матрицы коэффициентов
 * const double *A - матрица коэффициентов
 */
void l_matrix_print(int n, const double *A);

/*
 * ОПИСАНИЕ:
 * Выводит на экран матрицу U, т. е. верхний треугольник
 * матрицы коэффициентов с единичной главной диагональю.
 *
 * ПАРАМЕТРЫ:
 * int n - размерность матрицы коэффициентов
 * const double *A - матрица коэффициентов
 */
void u_matrix_print(int n, const double *A);

/*
 * ОПИСАНИЕ:
 * Выводит на экран матрицы L и U.
 *
 * ПАРАМЕТРЫ:
 * int n - размерность матрицы коэффициентов
 * const double *A - матрица коэффициентов
 */
void l_u_matrix_print(int n, const double *A);


//// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ:

/*
 * ОПИСАНИЕ:
 * Выводит на экран справочное сообщение.
 */
void help_print();