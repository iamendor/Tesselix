#include "tesselix.h"

void divider() {
    printf("\n");
    for(int i = 0; i< 80; i++) printf("*");
    printf("\n\n");
}

int main(int argc, char const *argv[]){
    double a1[] = {
        2, 1, 5,  
        4, 3, 11 
    }; // x=2, y=1

    double a2[] = {
        1, 2, -1, 0,  
        2, 3, 1, 7,   
        1, 1, 2, 4    
    }; // Nincs megoldás, tilos sor!

    double a3[] = {
        1, -1, 2, 3, 7,   
        2, 1, -1, 1, 2,   
        -1, 2, 3, -1, 4,  
        3, 0, 1, -1, 6    
    }; // x=1.56, y=0.2, z=1.92, v=0.6

    double a4[] = {
        2, -1, 3, 1, -2, 4,  
        1, 3, -2, 1, 1, 3,   
        3, -2, 1, -1, -1, 1, 
        4, 1, 2, -1, 3, 10,  
        -1, 2, -3, 2, 1, -6
    }; // x=0.73, y=3.19, z=2.1, v=-2.26, w=-0.85

    double a5[] = {
        3, 1, -1, 4,   
        1, 2, 2, 7,    
        2, -1, 3, 5    
    }; // x=1.27, y=1.53, z=1.33

    double a6[] = {
        4, 2, 6,  
        1, 3, 7   
    }; // x=0.4 , y=2.2

    double a7[] = {
        1, 2, -3, 4, 5,
        2, -1, 1, 1, 6,
        4, 5, 2, 1, 7,
        -3, 4, -2, 1, 8,
        1, -1, 1, 1, 0 
    }; // Tilos sor

    double a8[] = {
        1,  2, -3,  4, 10,   
        2, -1,  4,  1,  8,   
        3,  1, -1,  2,  7,   
        4,  3,  2, -1, 12
    }; // x=0.41, y=2.95, z=1.94, v=2.38

    divider();

    Matrix* mtrx = mtrxCreate(2, 3, a1);
    mtrxPrint(mtrx);
    double result = mtrxGaussElim(mtrx);
    if(result == -1) printf("TILOS SOR!");
    else mtrxPrint(mtrx);
    mtrxFree(mtrx);
    
    divider();

    mtrx = mtrxCreate(3, 4, a2);
    mtrxPrint(mtrx);
    result = mtrxGaussElim(mtrx);
    if(result == -1) printf("TILOS SOR!");
    else mtrxPrint(mtrx);
    mtrxFree(mtrx);
    
    divider();
    
    mtrx = mtrxCreate(4, 5, a3);
    mtrxPrint(mtrx);
    result = mtrxGaussElim(mtrx);
    if(result == -1) printf("TILOS SOR!");
    else mtrxPrint(mtrx);
    mtrxFree(mtrx);
    
    divider();

    mtrx = mtrxCreate(5, 6, a4);
    mtrxPrint(mtrx);
    result = mtrxGaussElim(mtrx);
    if(result == -1) printf("TILOS SOR!");
    else mtrxPrint(mtrx);
    mtrxFree(mtrx);
    
    divider();

    mtrx = mtrxCreate(3, 4, a5);
    mtrxPrint(mtrx);
    result = mtrxGaussElim(mtrx);
    if(result == -1) printf("TILOS SOR!");
    else mtrxPrint(mtrx);
    mtrxFree(mtrx);
    
    divider();

    mtrx = mtrxCreate(2, 3, a6);
    mtrxPrint(mtrx);
    result = mtrxGaussElim(mtrx);
    if(result == -1) printf("TILOS SOR!");
    else mtrxPrint(mtrx);
    mtrxFree(mtrx);

    divider();

    mtrx = mtrxCreate(5, 5, a7);
    mtrxPrint(mtrx);
    result = mtrxGaussElim(mtrx);
    if(result == -1) printf("TILOS SOR!");
    else mtrxPrint(mtrx);
    mtrxFree(mtrx);

    divider();

    mtrx = mtrxCreate(4, 5, a8);
    mtrxPrint(mtrx);
    result = mtrxGaussElim(mtrx);
    if(result == -1) printf("TILOS SOR!");
    else mtrxPrint(mtrx);
    mtrxFree(mtrx);


}
