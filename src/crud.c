#include "debugmalloc.h"
#include "crud.h"
#include <stdlib.h>

Matrix *mtrxCreate(int h, int w, double* data){
    Matrix* mtrx = (Matrix*) malloc(sizeof(Matrix));
    if(mtrx == NULL) return NULL;
    
    mtrx->height = h;
    mtrx->width = w;

    mtrx->data = (double**) malloc(h * sizeof(double*)); // Sorfoglalás
    if(mtrx->data == NULL){
        free(mtrx);
        return NULL;
    }

    for(int i=0; i<h; i++){
        mtrx->data[i] = (double*)calloc(w, sizeof(double)); // Oszlopfoglalás
        if(mtrx->data[i] == NULL) {
            mtrxFree(mtrx);
            return NULL;
        }
        if(data != NULL){
            for(int j=0; j<w; j++){
                mtrx->data[i][j] = data[i*w + j];
            }
        }
    }
    return mtrx;
};

Matrix *mtrxCreateIdentity(int n){
    double* data = (double*)calloc(n*n, sizeof(double));
    if(!data) return NULL;

    for(int i=0; i<n*n; i++){
        if(i == 0 || i % (n+1) == 0) data[i] = 1;
        else data[i] = 0;
    }


    Matrix* mtrx = mtrxCreate(n, n, data);
    free(data);

    return mtrx;
}

// 2D -> 1D: index = row*k + col (k = oszlopok száma)
Matrix* mtrxCreateAug(Matrix* s1, Matrix* s2){
    if(s1 == NULL || s2 == NULL || s1->height != s2->height) return NULL;

    int augWidth = s1->width + s2->width;
    double* data = (double*) calloc((augWidth) * s1->height, sizeof(double));

    for(int i=0; i<s1->height; i++){
        for(int j=0; j<s1->width; j++){
            data[i*(augWidth) + j] = s1->data[i][j];
        }
        for(int k=s1->width; k<augWidth; k++){
            data[i*(augWidth) + k] = s2->data[i][k-s1->width];
        }

    }

    Matrix* mtrx = mtrxCreate(s1->height, augWidth, data);
    free(data);
    return mtrx;
};



Matrix* mtrxUpdateCell(Matrix* mtrx, int row, int col, double update){
    if(row > (mtrx->height) || col > (mtrx->width)) return NULL;
    mtrx->data[row-1][col-1] = update;
    return mtrx;
}

Matrix* mtrxCopy(Matrix* target, Matrix* source){
    if(source == NULL) return NULL;

    double *toArray = NULL;

    int len = mtrxToArray(&toArray, source);
    if(len == -1) return NULL;

    target = mtrxCreate(source->height, source->width, toArray);
    if(target == NULL) return NULL;

    free(toArray);
    
    return target;
}

Matrix* mtrxShrink(Matrix* mtrx, int h, int w){
   if((mtrx->height == h && mtrx->width == w) || \
        (mtrx->height < h) || (mtrx->width < w) || mtrx == NULL) return NULL;

    //Először az oszlopokat
    for(int i=0; i<mtrx->height; i++){
        mtrx->data[i] = (double*) realloc(mtrx->data[i], w * sizeof(double));
        if(mtrx->data[i] == NULL) return NULL;
    }
    //Sorok
    for(int i=(mtrx->height)-1; i>=w-1; i--){
        free(mtrx->data[i]);
    }
    mtrx->width = w;
    mtrx->height = h;
    return mtrx;
}

Matrix* mtrxExpand(Matrix *mtrx, int h, int w){
    if((mtrx->height == h && mtrx->width == w) || \
        (mtrx->height > h) || (mtrx->width > w) || mtrx == NULL) return NULL;

    //Oszlopbővítés
    for(int i=0; i<mtrx->height; i++){
        mtrx->data[i] = (double*)realloc(mtrx->data[i], w * sizeof(double));
        if(mtrx->data[i] == NULL) return NULL;
        for(int j=mtrx->width; j<w; j++){
            mtrx->data[i][j] = 0;
        }
    }
    //Sorbővítés
    mtrx->data = (double**) realloc(mtrx->data, h * sizeof(double*));
    if(mtrx->data == NULL) return NULL;

    for(int i=mtrx->height; i<h; i++){
        mtrx->data[i] = (double*)malloc(w * sizeof(double));
        if(mtrx->data[i] == NULL) return NULL;
        for(int j=0; j<w; j++){
            mtrx->data[i][j] = 0;
        }
    }

    mtrx->width = w;
    mtrx->height = h;
    return mtrx;
}


void mtrxFree(Matrix* mtrx){
    if(mtrx == NULL) return;

    for(int i=0; i<mtrx->height; i++){
        free(mtrx->data[i]);
    }
    free(mtrx->data);
    free(mtrx);
}

int mtrxToArray(double** target, Matrix* source){
    if(source == NULL) return -1;

    int len = source->width * source->height;
    double *temp = (double*) malloc(len * sizeof(double));
    if(temp == NULL) return -1;
    *target = temp;

    for(int i=0; i<source->height; i++){
        for(int j=0; j<source->width; j++){
            (*target)[i*(source->width) + j] = source->data[i][j];
        }
    }

    return len;
}