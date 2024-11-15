#ifndef ARITHMETIC_H
#define ARITHMETIC_H
#include <stdbool.h>
#include "debugmalloc.h"
#include "struct.h"

Matrix* mtrxOp(double with, char op, Matrix* mtrx);
Matrix* mtrxOpMtrx(Matrix* m1, char op, Matrix* m2);
Matrix* mtrxMultiplMtrx(Matrix* m1, Matrix* m2);

#endif
