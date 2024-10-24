#ifndef IO_H
#define IO_H
#include "debugmalloc.h"
#include "struct.h"
#include <stdio.h>


void mtrxPrint(Matrix* mtrx);
int mtrxExportArray(FILE* file, Matrix** mtrx, int size);
int mtrxExport(FILE* file, Matrix* mtrx);
int mtrxImport(Matrix*** target, FILE* file);

#endif