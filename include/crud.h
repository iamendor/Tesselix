#ifndef CRUD_H
#define CRUD_H
#include "debugmalloc.h"
#include "struct.h"
#include <stdbool.h>

Matrix* mtrxCreate(int h, int w, double* data);
Matrix* mtrxCopy(Matrix* target, Matrix* source);
Matrix* mtrxCreateIdentity(int n);
Matrix* mtrxCreateAug(Matrix* s1, Matrix* s2);
Matrix* mtrxShrink(Matrix* mtrx, int h, int w);
Matrix* mtrxExpand(Matrix *mtrx, int h, int w);
double* mtrxUpdateCell(Matrix* mtrx, int row, int col, double update); //TODO:  return the pointer of the cell
bool mtrxCompare(Matrix* m1, Matrix* m2);

void mtrxFree(Matrix* mtrx);
int mtrxToArray(double** target, Matrix* source);

#endif