#include "debugmalloc.h"
#include "advanced.h"
#include "crud.h"
#include "io.h"
#include "util.h"
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
}

//Swap two row inside matrix
Matrix* mtrxSwapRow(Matrix* source, int r1, int r2){
    if(source == NULL || r1 < 1 || r2 < 1 || r1 > source->height || r2> source->height) return NULL;
    if(r1 == r2) return source;

    double* temp = source->data[r1-1];
    source->data[r1-1] = source->data[r2-1];
    source->data[r2-1] = temp;

    return source;
}

//Add a tight of a series of scalars to another row
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
      if(!equal(data[i][j], 0)){
        mtrxMultiplRow(mtrx, (double)1/(data[i][j]), i+1);

        if(i+1 < mtrx->height){
            for(int t=i+1; t<mtrx->height; t++){
                mtrxAddRow(mtrx, t+1, -data[t][j], i+1);
            }
        }

        if(i+1 == mtrx->width || j+1 == mtrx->height) break;
        i++; j++;
      }else{
        if(i+1 < mtrx->height){
            int t = i+1;
            while(t+1 < mtrx->height){
                t++;
            }
            if(!equal(data[t][j], 0)){
                mtrxSwapRow(mtrx, i+1, t+1);
                rowSwap++;
                continue;
            }else{
                if(j+1 == mtrx->width){
                    i--;
                    break;
                }else j++;
            }
        }
      }
    }
    return rowSwap;
}

// A Gauss-elimináció algoritmusa néhány funkcióval kiegészítve
double mtrxDeterminant(Matrix* mtrx){
    if(mtrx->width != mtrx->height) return 0;
    Matrix* copy = mtrxCopy(mtrx);
    if(copy == NULL) return 0;

    double** data = copy->data;
    int i = 0; // i=sor
    double D = 1;

    while(i < copy->height){
        double ok = data[i][i];
      if(!equal(ok, 0)){
        mtrxMultiplRow(copy, (double)1/(data[i][i]), i+1);
        D *= data[i][i];

        if(i+1 < copy->height){
            for(int t=i+1; t<copy->height; t++){
                mtrxAddRow(copy, t+1, -data[t][i], i+1);
            }
        }

        if(i+1 == copy->width) break;
        i++;
      }else{
        if(i+1 < copy->height){
            int t = i+1;
            while(t+1 < copy->height){
                t++;
            }
            if(!equal(data[t][i], 0)){
                mtrxSwapRow(copy, i+1, t+1);
                continue;
            }else return 0;
        }
      }
    }
    mtrxFree(copy);

    return D;
}
