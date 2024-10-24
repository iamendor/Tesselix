#include "tesselix.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    double test[9] = {1, 2, 3, 4, 5, 6, 7, 8};
    double test2[1] = { 1 };
    Matrix *mtrx = mtrxCreate(2, 4, test);
    Matrix *mtrx4 = mtrxCreate(2, 4, NULL);
    Matrix *mtrx3 = mtrxCreate(1, 1, test2);
    
    Matrix *mtrx2 = mtrxCreateIdentity(2);
    mtrxPrint(mtrx4);


    Matrix* mtrxes[3] = {mtrx, mtrx3, mtrx4};
    for(int i=0; i<3; i++){
        mtrxPrint(mtrxes[i]);
        printf("\n");
    }
    printf("\n\n");
    Matrix* augmented = mtrxCreateAug(mtrx, mtrx2);
    Matrix* transponated = mtrxTransponate(mtrx);
    

    mtrxShrink(mtrx, 1, 2);
    mtrxExpand(mtrx, 3, 5);

    mtrxOpMtrx(mtrx, '+', mtrx);
    mtrxPrint(mtrx);
    mtrxOpMtrx(mtrx, '-', mtrx4);
    mtrxPrint(mtrx);

    FILE* file = fopen("test.txt", "w");
    FILE* file2 = fopen("test2.txt", "w");
    mtrxExportArray(file, mtrxes, 2);
    mtrxExport(file2, mtrx);
    fclose(file);
    fclose(file2);

    mtrxFree(transponated);
    mtrxFree(mtrx);
    mtrxFree(mtrx2);
    mtrxFree(augmented);
    mtrxFree(mtrx3);
    mtrxFree(mtrx4);


    file = fopen("test.txt", "r");
    Matrix** target = NULL;
    int len = mtrxImport(&target, file);

    for(int i=0; i<len; i++){
        mtrxPrint(target[i]);
    }
    for(int i=0; i<len; i++){
        mtrxFree(target[i]);
    }
    free(target);
    fclose(file);

    return 0;
}