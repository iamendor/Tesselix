#include "debugmalloc.h"
#include "tesselix.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int w, h;
    printf("Mátrix beolvasás\nSzélesség: ");
    scanf("%d", &w);
    printf("Magasság: ");
    scanf("%d", &h);
    int len = w*h;
    double* arr = (double*)malloc(len*sizeof(double));
    for(int i=0; i<len; i++){
        printf("a%d%d: ", i/w + 1, i%w +1);
        scanf("%lf", &arr[i]);
    }
    Matrix* mtrx = mtrxCreate(h, w, arr);
    if(mtrx == NULL){
        printf("\nHiba történt!");
        return 1;
    }
    printf("\nA mátrixod: ");
    mtrxPrint(mtrx);


    mtrxFree(mtrx);
    free(arr);


    return 0;
}
