#include "debugmalloc.h"
#include "advanced.h"
#include "crud.h"
#include <stdio.h>

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

// Szeszlér Dávid Bsz1 jegyzete alapján készített algoritmus
double mtrxGaussElim(Matrix* mtrx){
    double** data = mtrx->data;
    int i = 0, j = 0; // i=sor, j=oszlop
    int rowSwap = 0;

    while(i < mtrx->height){
        if(data[i][j] != 0){
            mtrxMultiplRow(mtrx, (double)1/data[i][j], i+1);
            if(i < mtrx->width){
                int t=i+1; 
                while(t < mtrx->height){
                    mtrxAddRow(mtrx, t+1, -data[t][j], i+1);
                    t++;
                }

                if(i == mtrx->height -1 || j == mtrx->width -1) break;
                i++; j++;
            }
        }else{
            for(int t=i+1; i<mtrx->height; t++){
                if(data[t][j] != 0) {
                    rowSwap++;
                    mtrxSwapRow(mtrx, i+1, t+1);
                    break;
                }
            }
        }
        
    }
    return rowSwap;
};

// A Gauss-elimináció algoritmusa néhány funkcióval kiegészítve
double mtrxDeterminant(Matrix* mtrx){
    Matrix* copy = NULL;
    mtrxCopy(copy, mtrx);
    double D = 1;
    double** data = copy->data;
    int i = 0, j = 0; // i=sor, j=oszlop

    while(i < copy->height){
        if(data[i][j] != 0){
            mtrxMultiplRow(copy, (double)1/data[i][j], i+1);
            D *= data[i][j];
            if(i < copy->width){
                int t=i+1; 
                while(t < copy->height){
                    mtrxAddRow(mtrx, t+1, -data[t][j], i+1);
                    t++;
                }

                if(i == copy->height -1 || j == copy->width -1) break;
                i++; j++;
            }
        }else{
            int t=i+1;
            while(i<copy->height && data[t][j] != 0){
                mtrxSwapRow(mtrx, i+1, t+1);
                D *= -1;
            }
        }
        
    }
    mtrxFree(copy);
    return D;
};