#include "advanced.h"
#include "crud.h"


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
