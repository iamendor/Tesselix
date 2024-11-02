#include "debugmalloc.h"
#include "tesselix.h"
#include <stdio.h>


int main(){
    Matrix *mtrx1, *mtrx2 = NULL, *mtrx3, *identity, *augmented, **import;
    FILE* fp;
    int success;

    double a1[6] = {1, 0, 2, -1, 3, 1};
    double a2[6] = {3, 1, 2, 1, -1, 0};
    double a3[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};


    //CRUD

    printf("3 magas, 2 széles mátrix ebből a tömbből: ");
    for(int i=0; i<6; i++)printf("%.1f", a1[i]);
    mtrx1 = mtrxCreate(3, 2, a1);
    printf("\n");
    mtrxPrint(mtrx1);
    printf("\n");

    printf("3x3 identitás mátrix:");
    identity = mtrxCreateIdentity(3);
    mtrxPrint(identity);
    printf("\n");

    printf("Augmented mátrix az előző kettőből:");
    augmented = mtrxCreateAug(mtrx1, identity);
    mtrxPrint(augmented);
    printf("\n");

    printf("Cella frissítés 1. sor 2. oszlopban(1. mátrix)");
    double* updated = mtrxUpdateCell(mtrx1, 2, 1, 9.00);
    printf("Frissített cella: %p %.2f\n", updated, *updated);
    mtrxPrint(mtrx1);
    printf("\n");

    printf("Mátrix szűkítés jobb alsó sarokból(augmented mátrix)");
    augmented = mtrxShrink(augmented, 3, 3);
    mtrxPrint(augmented);
    printf("\n");

    printf("Mátrix bővítés jobb alsó sarokból(augmented mátrix)");
    augmented = mtrxExpand(augmented, 4, 4);
    mtrxPrint(augmented);
    printf("\n");

    printf("Mátrix konvertálás tömbbé(augmented mátrix)\n");
    double* toArray;
    int len = mtrxToArray(&toArray, augmented);
    printf("Hossza: %dx%d = %d\n", augmented->width, augmented->height, len);
    for(int i=0; i<len; i++) printf("%.1f ", toArray[i]);
    printf("\n");

    printf("Mátrix másolás");
    mtrx2 = mtrxCopy(mtrx2, mtrx1);
    mtrxPrint(mtrx2);

     //Felszabadítás
    printf("Mátrix felszabadítás...");
    mtrxFree(mtrx1);
    mtrxFree(mtrx2);
    mtrxFree(identity);
    mtrxFree(augmented);
    free(toArray);
    printf("\n");

    // Arithmetic
    mtrx1 = mtrxCreate(2, 3, a2);
    printf("Eredeti mátrix: \n");
    mtrxPrint(mtrx1);
    
    printf("\nMátrix összeadás konstanssal (+2)");
    mtrx1 = mtrxOp(2, '+', mtrx1);
    mtrxPrint(mtrx1);
    printf("\nMátrix kivonás kosntanssal (-2)");
    mtrx1 = mtrxOp(2, '-', mtrx1);
    mtrxPrint(mtrx1);
    printf("\nMátrix szorzás konstanssal (5)");
    mtrx1 = mtrxOp(5, '*', mtrx1);
    mtrxPrint(mtrx1);
    printf("\nMátrix osztás konstanssal (5)");
    mtrx1 = mtrxOp(5, '/', mtrx1);
    mtrxPrint(mtrx1);

    printf("\nMátrix összehasonlítás");
    mtrx2 = mtrxCreate(2, 3, a2);
    mtrx3 = mtrxCreate(2, 3, a1);
    printf("\nElső mátrix: ");
    mtrxPrint(mtrx1);
    printf("Második mátrix: ");
    mtrxPrint(mtrx2);
    printf("Harmadik mátrix: ");
    mtrxPrint(mtrx3);
    printf("\n");
    printf("%s\n", mtrxCompare(mtrx1, mtrx2) ? "Mátrix1 egyezik Mátrix2-vel\n" : "Mátrix1 nem egyezik Mátrix2-vel\n");
    printf("%s\n", mtrxCompare(mtrx1, mtrx3) ? "Mátrix1 egyezik Mátrix3-al\n" : "Mátrix1 nem egyezik Mátrix3-al\n");


    printf("Két mátrix összeadása(Mátrix1 + Mátrix3)");
    mtrx1 = mtrxOpMtrx(mtrx1, '+', mtrx3);
    mtrxPrint(mtrx1);
    printf("Két mátrix kivonása(Mátrix1 + Mátrix3)");
    mtrx1 = mtrxOpMtrx(mtrx1, '-', mtrx3);
    mtrxPrint(mtrx1);

    printf("\nKét mátrix összeszorzása (Mátrix1 * Mátrix2(3x3-ra alakítva)");
    mtrxFree(mtrx3);
    mtrxExpand(mtrx2, 3, 3);
    mtrx3 = mtrxMultiplMtrx(mtrx1, mtrx2);
    mtrxPrint(mtrx3);
    printf("\n");
    //Felszabadítás
    mtrxFree(mtrx1);
    mtrxFree(mtrx2);
    mtrxFree(mtrx3);

    //I/O
    printf("Mátrix exportálás(egyetlen darabot és tömbben)\n");
    mtrx1 = mtrxCreate(3, 2, a1);
    mtrx2 = mtrxCreate(2, 3, a2);
    mtrx3 = mtrxCreate(3, 3, a3);

    Matrix* mtrxArray[3] = {mtrx1, mtrx2, mtrx3};
    fp = fopen("mtrxExport1.txt", "w");
    success = mtrxExport(fp, mtrx1);
    printf("%s\n", success == 1 ? "Sikeres exportálás!" : "Sikertelen!");
    fclose(fp);
    fp = fopen("mtrxExport2.txt", "w");
    success = mtrxExportArray(fp, mtrxArray, 3);
    printf("%s\n", success == 3 ? "Minden mátrixot sikeresen exportált!" : "Sikertlen!");
    fclose(fp);

    //Felszabadítás
    for(int i=0; i<3; i++) mtrxFree(mtrxArray[i]);

    printf("\nMátrix importálás\n");
    fp = fopen("mtrxExport2.txt", "r");
    import =  mtrxImport(fp);
    if(import != NULL)printf("Sikeres importálás\n");
    else printf("Hiba az importálássál\n");

    for(int i=0; import[i] != NULL; i++) mtrxPrint(import[i]);

    for(int i=0; import[i] != NULL; i++) mtrxFree(import[i]);
    free(import);
    fclose(fp);

    // Advanced
    printf("\nTranszponálás\n");
    mtrx1 = mtrxCreate(3, 2, a1);
    printf("Eredeti");
    mtrxPrint(mtrx1);
    mtrx2 = mtrxTransponate(mtrx1);
    printf("Transzponált");
    mtrxPrint(mtrx2);

    printf("\nSorcsere(Mátrix1)");
    mtrx1 = mtrxSwapRow(mtrx1, 1, 2);
    mtrxPrint(mtrx1);

    printf("\nSor skalárszoros hozzáadás(s1 = s1 + 2*s2)");
    mtrx1  = mtrxAddRow(mtrx1, 1, 2, 2);
    mtrxPrint(mtrx1);

    printf("\nSor skalárszoros szorzás(s1 = (1/4) * s1)");
    mtrx1 = mtrxMultiplRow(mtrx1, (double)1/4, 1);
    mtrxPrint(mtrx1);


    mtrxFree(mtrx2);
    mtrxFree(mtrx1);
   
    return 0;
}