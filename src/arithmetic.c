#include "debugmalloc.h"
#include "arithmetic.h"
#include <stdbool.h>


Matrix* mtrxOp(double alpha, char op, Matrix* mtrx){
    if(mtrx == NULL) return NULL;
    for(int i=0; i<mtrx->height; i++){
        for(int j=0; j<mtrx->width; j++){
            switch(op){
                case '+':
                    mtrx->data[i][j] += alpha;
                    break;
                case '-':
                    mtrx->data[i][j] -= alpha;
                    break;
                case '/':
                    mtrx->data[i][j] /= alpha;
                    break;
                case '*':
                    mtrx->data[i][j] *= alpha;
                    break;
                default: 
                    break;
            }
        }
    }
    return mtrx;
};

bool mtrxCompare(Matrix* m1, Matrix* m2){
    if(m1 == NULL || m2 == NULL ||\
        m1->height != m2->height ||\
        m1->width != m2->width) return false;
    
    for(int i=0; i<m1->height; i++){
        for(int j=0; j<m1->width; j++){
            if(m1->data[i][j] != m2->data[i][j]) return false;
        }
    }

    return true;
}

Matrix* mtrxOpMtrx(Matrix* m1, char op, Matrix* m2){
    if(m1->width != m2->width || m1->height != m2->height || m1 == m2) return NULL;
    for(int i=0; i<m1->height; i++){
        for(int j=0; j<m2->width; j++){
            switch (op) {
                case '+':
                    m1->data[i][j] += m2->data[i][j]; 
                    break;
                case '-':
                    m1->data[i][j] -= m2->data[i][j]; 
                    break;
                default:
                    break;
            }
        }
    }
    return m1;
}