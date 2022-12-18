#pragma once

#include "math.h"
#include "stdio.h"
#include "stdlib.h"

extern size_t debug;
extern size_t errors;
extern size_t print;
extern size_t time;

size_t lss_memsize_28_08(int n);

int lss_28_08(int n, double *A, double *B, double *X, double *tmp);