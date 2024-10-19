#ifndef STRUCT_H
#define STRUCT_H
#include "debugmalloc.h"


typedef struct Matrix{
    int width;
    int height;
    double** data;
} Matrix;

#endif