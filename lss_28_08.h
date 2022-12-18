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