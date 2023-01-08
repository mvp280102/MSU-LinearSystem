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

double l_sum(int n, int i, int k, const double *A);
double u_sum(int n, int i, int k, const double *A);
void lu_decomposition(int n, double *A);

double x_sum(int n, int i, const double *A, const double *X);
double y_sum(int n, int i, const double *A, const double *Y);
void solve(int n, const double *A, const double *B, double *X);

void l_matrix_print(int n, const double *A);
void u_matrix_print(int n, const double *A);
void l_u_matrix_print(int n, const double *A);