#pragma once

#include "math.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"

extern size_t debug_print;
extern size_t errors_print;
extern size_t matrix_print;
extern size_t time_print;

size_t lss_memsize_28_08(int n);
int lss_28_08(int n, double *A, double *B, double *X, double *tmp);

double l_sum(int n, size_t i, size_t k, const double *A);
double u_sum(int n, size_t i, size_t k, const double *A);
void lu_decomposition(int n, double *A);

double x_sum(int n, size_t i, const double *A, const double *X);
double y_sum(int n, size_t i, const double *A, const double *Y);
void solve(int n, const double *A, const double *B, double *X);

void print_matrix(int n, const double *matrix);