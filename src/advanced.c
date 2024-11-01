#include "debugmalloc.h"
#include "advanced.h"
#include "crud.h"

//Transponate matrix
Matrix* mtrxTransponate(Matrix* source){
    if(source == NULL) return NULL;
    Matrix* mtrx = mtrxCreate(source->width, source->height, NULL);
    if(mtrx == NULL) return NULL;

    for(int i=0; i<mtrx->height; i++){
        for(int j=0; j<mtrx->width; j++){
            mtrx->data[i][j] = source->data[j][i];
        }
    }

    return mtrx;
};
//Swap two row inside matrix
Matrix* mtrxSwapRow(Matrix* source, int r1, int r2){
    if(source == NULL || r1 < 1 || r2 < 1 || r1 > source->height || r2> source->height) return NULL;
    if(r1 == r2) return source;

    double* temp = source->data[r1-1];
    source->data[r1-1] = source->data[r2-1];
    source->data[r2-1] = temp;

    return source;
}

//Add a tight of a seriesof scalars to another row
Matrix* mtrxAddRow(Matrix* source, int r1, double a, int r2){
    if(source == NULL || r1 < 1 || r2 < 1 || r1 > source->height || r2> source->height) return NULL;
    if(r1 == r2) return source;

    for(int i=0; i<source->width; i++){
        source->data[r1-1][i] += a * source->data[r2-1][i];
    }

    return source;
}

//Multiply row with a constant
Matrix* mtrxMultiplRow(Matrix* source, double a, int r){
    if(source == NULL || r < 1 || r > source->height) return NULL;

    for(int i=0; i<source->width; i++){
        source->data[r-1][i] *= a; 
    }

    return source;
}