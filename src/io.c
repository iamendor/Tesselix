#include "debugmalloc.h"

#include "io.h"
#include "crud.h"
#include <stdio.h>

void mtrxPrint(Matrix* mtrx){
    for(int i=0; i<mtrx->height; i++){
        
        if(i == 0 && mtrx->height != 1) printf("/");
        else if(i==mtrx->height -1 &&  mtrx->height != 1) printf("\\");
        else printf("|");

        for(int j=0; j<mtrx->width; j++){
            printf(" %.2f ", mtrx->data[i][j]);
        }

        if(i == 0 && mtrx->height != 1) printf("\\");
        else if(i == mtrx->height -1 && mtrx->height != 1) printf("/ %dx%d", mtrx->height, mtrx->width);
        else if(mtrx->height == 1) printf("| %dx%d", mtrx->height, mtrx->width);
        else printf("|");

        printf("\n");
    }
}

int mtrxExportArray(FILE *file, Matrix** mtrx, int size){
    int inserted = 0;
    if(file == NULL) return false;

    for(int i=0; i<size; i++){
        Matrix* mtrxI = mtrx[i];
        if(mtrxI == NULL) continue;

        int success = mtrxExport(file, mtrxI);
        
        if(success == 1)inserted++;

    }
    return inserted;
};

int mtrxExport(FILE* file, Matrix* mtrx){
    if(mtrx == NULL) return 0;

    double* matrixArray;
    int len = mtrxToArray(&matrixArray, mtrx);

    if(len == -1) return 0;

    fprintf(file, "[%d %d] ", mtrx->height, mtrx->width);
    for(int k=0; k<len; k++){
            fprintf(file, "%.2f ", matrixArray[k]);
        }
    fprintf(file, "\n");

    free(matrixArray);
    return 1;

}
Matrix** mtrxImport(FILE* file){return false;};