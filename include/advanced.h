#ifndef ADVANCED_H
#define ADVANCED_H
#include "debugmalloc.h"
#include "struct.h"

Matrix* mtrxTransponate(Matrix* source);
Matrix* mtrxSwapRow(Matrix* source, int r1, int r2);
Matrix* mtrxAddRow(Matrix* source, int r1, double a, int r2);
Matrix* mtrxMultiplRow(Matrix* source, double a, int r);
double mtrxDeterminant(Matrix* mtrx);
double mtrxGaussElim(Matrix* mtrx);
#endif
