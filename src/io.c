#include "debugmalloc.h"

#include "io.h"
#include "crud.h"
#include <stdio.h>
#include <string.h>

void mtrxPrint(Matrix* mtrx){
    for(int i=0; i<mtrx->height; i++){
        if(mtrx->height != 1){
            if(i == 0) printf("/");
            else if(i == mtrx->height -1) printf("\\");
            else printf("|");   
        }  else printf("|");

        for(int j=0; j<mtrx->width; j++){
            printf("%6.2f ", mtrx->data[i][j]);
        }
        if(mtrx->height != 1){
            if(i == 0)printf("\\");
            else if(i == mtrx->height -1) printf("/ %dx%d", mtrx->height, mtrx->width);
            else printf("|");

        }else if(mtrx->height == 1) printf("| %dx%d", mtrx->height, mtrx->width);
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
    if(mtrx == NULL || file == NULL) return 0;

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
int mtrxImport(Matrix*** target, FILE* file){
    if(file == NULL) return -1;
    int MIN_LEN = 10 + 1; // 1x1 mátrix tárolási minimum ('\0' karakterekre, '\n' nem tárolom)
    char* line = (char*)malloc(MIN_LEN * sizeof(char));
    char ch;
    int n = 0, matrixN = 0; // hány chart scanneltem // hány mátrixot scanneltem
    *target = (Matrix**)malloc(sizeof(Matrix*));

    while((ch = fgetc(file)) != -1){
        if(n >= MIN_LEN) {
            line = (char*)realloc(line, (n+1)*sizeof(char));
            if(line == NULL) return -1;
        }
        if(ch == '\n'){
            line[n] = '\0';
            // Vége a sornak, lezárjuk, mehet a scan!
            int h, w;
            if(sscanf(line, "[%d %d]", &h, &w) == 2){
                // Beolvastunk, ha nem akkor szabadítsa fel a sort és mehet a következő
                int cLen = h * w;
                int scanned = 0;
                double* arr = (double*)malloc(cLen * sizeof(double));
                int index = 6; // String index
                while(sscanf(line+index, "%lf", &(arr[scanned])) == 1 && scanned < cLen){
                    scanned++;
                    index += 5;
                }

                //Megvan a tömb
                Matrix* mtrx = mtrxCreate(h, w, arr);
                if(mtrx == NULL) continue; //Nem sikerült létrehozni a mátrixot
                if(matrixN != 0){
                     *target = (Matrix**)realloc(*target, (matrixN+1)*sizeof(Matrix*));
                     if(*target == NULL) return -1;
                }
                (*target)[matrixN++] = mtrx;

                free(arr);
            }

            free(line);
            line = (char*) malloc(MIN_LEN * sizeof(char));
            n = 0;
        }else line[n++] = ch;
    }
    free(line);
    return matrixN;
};