# Tesselix

Egy mátrix kezelő könyvtár C nyelven.

## Fordítás

### Könyvtár

```
make
```

### Bemutató program

```
make bin/main
```

### Importálás

```c
#include "tesselix.h"
```

## Struktúra

Minden függvény ezzel a struktúrával dolgozik, magában foglalja a szélességét és hosszúságát, valamint magát a mátrixot.

```c
typedef struct {
    int height;
    int width;
    double** data;
} Matrix;
```

<div style="page-break-after: always;"></div>

## Függvények

### [Létrehozás, olvasás, frissítés](#létrehozás-olvasás-frissítés)

[mtrxCreate](#matrix-mtrxcreateint-h-int-w-double-data) <br>
[mtrxCreateAug](#matrix-mtrxcreateaugmatrix-s1-matrix-s2) <br>
[mtrxCreateIdentity](#matrix-mtrxcreateidentityint-n) <br>
[mtrxUpdateCell](#int-mtrxupdatecellmatrix-mtrx-int-row-col-double-update) <br>
[mtrxCopy](#matrix-mtrxcopymatrix-target-matrix-source)<br>
[mtrxShrink](#matrix-mtrxshrinkmatrix-mtrx-int-h-int-w)<br>
[mtrxExpand](#matrix-mtrxexpandmatrix-mtrx-int-h-int-w)<br>
[mtrxFree](#void-mtrxfreematrix-mtrx)<br>
[mtrxToArray](#int-mtrxtoarraydouble-target-matrix_-source)<br>

### [Műveletek](#műveletek)

[mtrxCompare](#bool-mtrxcomparematrix-m1-matrix-m2) <br>
[mtrxOp](#matrix-mtrxopdouble-alpha-char-op-matrix-mtrx) <br>
[mtrxOpMtrx](#matrix-mtrxopmtrxmatrix-m1-matrix-m2) <br>

### [I/O](#io)

[mtrxPrint](#void-mtrxprintmatrix-mtrx) <br>
[mtrxExport](#int-mtrxexportfile-file-matrix-mtrx) <br>
[mtrxExportArray](#int-mtrxexportarrayfile-file-matrix-mtrx-int-size)<br>

### [Haladó](#haladó)

[mtrxTransponate](#matrix-mtrxtransponatematrix-source)<br>
[mtrxSwapRow](#matrix-mtrxswaprowmatrix-source-int-r1-int-r2)<br>
[mtrxAddRow](#matrix-mtrxaddrowmatrix-source-int-r1-double-a-int-r2)<br>
[mtrxMultiplRow](#matrix-mtrxmultiplrowmatrix-source-double-a-int-r)<br>

<div style="page-break-after: always;"></div>

## Létrehozás, olvasás, frissítés

### <code>Matrix\* mtrxCreate(int h, int w, double\* data)</code>

Létrehozunk egy mátrixot egy _h \* w_ hosszú tömbből, feltételezzük, hogy legalább ekkora a tömb. Az adatokat soronként töltjük fel. Ha a megadott dimenzióknál több érték van a tömbben, nem fognak megjelenni a mátrixban. A visszatérési érték a **mátrixra mutató pointer**, a többi függvény is így tér vissza. Ha **NULL**-t helyettesítünk a tömb helyére, a mátrixot 0-val fogja feltölteni.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
Matrix* matrix2 = mtrxCreate(4, 1, tomb);
/*
matrix{                 matrix2{
    width: 2;               width: 1;
    height: 2;              height: 4;
    data: [ [ 1, 2 ],       data: [ [ 1 ],
            [ 3, 4 ] ]              [ 2 ],
}                                   [ 3 ],
                                    [ 4 ] ]
                        }
*/
```

### <code>Matrix\* mtrxCreateIdentity(int n)</code>

Az identitás mátrix fontos eleme a mátrixok témájának, a függvénnyel létrehozhatunk egy _n_ széles, magas identitás mátrixot _(A főátló cellái 1, minden más 0)_.

```c
Matrix* identity = mtrxCreateIdentity(2);
/*
[   [1, 0],
    [0, 1] ]
*/
```

<div style="page-break-after: always;"></div>

### <code>Matrix* mtrxCreateAug(Matrix* s1, Matrix\* s2)</code>

Két mátrixot tudunk _"összeforrasztani"_. Ez különösen fontos például Gauss-elimináció során, vagy egyenletrendszerek két oldalának összecsatolására. Visszatérési értéke az **új mátrix pointere**(másik memóriacímen). Ha nem egyezik a a két mátrix magassága, **NULL pointer**-t ad vissza.

```c
double tomb[4] = { 1, 2, 3, 4 };
double tomb[6] = { 1, 2, 3, 4, 5, 6 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
Matrix* matrix2 = mtrxCreate(2, 3, tomb);
Matrix* matrix3 = mtrxCreate(4, 1, tomb);
Matrix* augmented = mtrxCreateAug(matrix, matrix2);
Matrix* augmented2 = mtrxCreateAug(matrix, matrix3); // NULL

/*
/ 1 2 | 1 2 3 \
\ 3 4 | 4 5 6 /
 mtx1   mtx2
*/

```

### <code>int* mtrxUpdateCell(Matrix* mtrx, int row, col, double update)</code>

Frissíteni tudjuk a cellát a megadott pozícióban, ha túl lépne a mátrix határain, **NULL pointer**-t ad vissza, egyébként a cella memóriacímét. Az indexelés **1**-től keződik.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
mtrxUpdateCell(matrix, 5,1, 2.5); // NULL
mtrxUpdateCell(matrix, 1,1, 2.5); // [ [2.5, 2], [3, 4] ]
```

### <code>Matrix* mtrxCopy(Matrix* target, Matrix\* source)</code>

Átmásolja a mátrixot egy másik memóriacímre. Visszatér a **target**-el, ha sikeres volt a művelet, ellenkező esetben **NULL**.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
Matrix* trgtMtrx;

mtrxCopy(trgtMtrx, matrix);
mtrxPrint(trgtMtrx);
/*  / 1 2 \
    \ 3 4 / 2x2  */
```

<div style="page-break-after: always;"></div>

### <code>Matrix* mtrxShrink(Matrix* mtrx, int h, int w)</code>

Csökkenteni tudjuk a mátrix szélességét és hosszát. A csökkentés a jobb alsó sarokból indul. A mátrix értékei, amelyek nem férnek bele az új szélbe és hosszba elvesznek. Sikeres elvégzés esetén visszatér a mátrix pointerével, ha nem sikerülne, vagy magasabb értékeket adtunk meg, mint a mátrix széle és hossza, **NULL pointer**-el tér vissza.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
mtrxShrink(matrix, 1, 2);
mtrxPrint(matrix);
/* | 1 2 | 1x2 */
```

### <code>Matrix* mtrxExpand(Matrix* mtrx, int h, int w)</code>

Lényegében a <code>mtrxShrink</code> ellentettje, ugyanígy viselkedik, viszont a másik irányba, tehát növelni tudja a mátrix méreteit, és az új cellákat nullával tölti fel.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
mtrxExpand(matrix, 3, 3);
mtrxPrint(matrix);
/*
/ 1 2 0 \
| 3 4 0 |
\ 0 0 0 / 3x3
*/
```

### <code>void mtrxFree(Matrix\* mtrx)</code>

Ezzel tudjuk biztonságosan felszabadítani a memóriából a mátrixunkat, elkerülve a _memory leak_-et. A programunk végén mindenképpen szabadítsuk fel az összes létrehozott mátrixot!

```c
int main(void){
    double tomb[4] = { 1, 2, 3, 4 };
    Matrix* matrix = mtrxCreate(2, 2, tomb);
    mtrxPrint(matrix);

    mtrxFree(matrix);
    return 0;
}
```

<div style="page-break-after: always;"></div>

### <code>int mtrxToArray(double\*\* target, Matrix\_ source)</code>

A kétdimenziós mátrixot vissza tudjuk konvertálni egydimenziós tömbbé is úgy, hogy a sorokat egymás mellé helyezzük. Visszatérési értéke a tömb hossza.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
double *tomb;
int len = mtrxToArray(&tomb, matrix);
for(int i=0; i<len; i++){
    printf("%.2f", tomb[i]); // 1.00 2.00 3.00 4.00
}
```

## Műveletek

### <code>bool mtrxCompare(Matrix* m1, Matrix* m2)</code>

Két mátrix összehasonlítására alkalmas függvény.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix1 = mtrxCreate(2, 2, tomb);
Matrix* matrix2 = mtrxCreate(2, 2, tomb);
Matrix* matrix3 = mtrxCreate(2, 2, NULL);
printf("%d", mtrxCompare(matrix1, matrix2) ); // 1
printf("%d", mtrxCompare(matrix1, matrix3) ); // 0
```

### <code>Matrix* mtrxOp(double alpha, char op, Matrix* mtrx)</code>

Konstans számmal és mátrixxal való műveletre alkalmas függvény. Az átadott mátrixot frissíti. Visszatér a mátrix pointerével.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
mtrxOp(2, '+', matrix); // matrix[i][j] += 2 minden elemre
mtrxOp(2, '.', matrix); // matrix[i][j] -= 2
mtrxOp(2, '*', matrix); // matrix[i][j] *= 2
mtrxOp(2, '/', matrix); // matrix[i][j] /= 2
```

<div style="page-break-after: always;"></div>

### <code>Matrix* mtrxOpMtrx(Matrix* m1, Matrix\* m2)</code>

Két mátrixot tudunk összeadni és kivonni egymásból elemenként. Az **m1** mátrixot fogja frissíteni, és ezzel is tér vissza a függvény. Csak megegyező paraméterekkel rendelkező mátrixokat tudja elvégezni a műveleteket.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
Matrix* matrix2 = mtrxCreate(2, 2, tomb);
mtrxOpMtrx(matrix, '+', matrix2); // matrix[i][j] += matrix2[i][j]
mtrxOpMtrx(matrix, '.', matrix2); // matrix[i][j] -= matrix2[i][j]
```

## I/O

### <code>void mtrxPrint(Matrix\* mtrx)</code>

Formázott kiíratás a standard kimenetre.

```c
double tomb[4] = { 1, 2, 3, 4 };
double tomb2[2] = { 1, 2 };
double tomb3[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
Matrix* matrix2 = mtrxCreate(1, 2, tomb2);
Matrix* matrix3 = mtrxCreate(3, 3, tomb3);

mtrxPrint(matrix);
mtrxPrint(matrix2);
mtrxPrint(matrix3);
/*
                                / 1 2 3 \
                / 1 2 \         | 4 5 6 |
| 1 2 | 1x2     \ 3 4 / 2x2     \ 7 8 9 / 3x3
*/
```

### <code>int mtrxExport(FILE \*file, Matrix\* mtrx)</code>

Kiexportálhatunk egy darab mátrixot. A visszatérési érték a kiexportált mátrixok száma(0 vagy 1). A függvény **nem zárja le a fájlt**!

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
FILE* file = fopen("mtrx.txt", "w");
mtrxExport(file, matrix);
fclose(file);
```

<div style="page-break-after: always;"></div>

### <code>int mtrxExportArray(FILE \*file, Matrix\*\* mtrx, int size)</code>

Kiexportálhatunk egy tömb mátrixot a megadott fájlba. Visszatérési értéke a a kiexportált mátrixok száma. A függvény **nem zárja le a fájlt**!

```c
double tomb[4] = { 1, 2, 3, 4 };
double tomb2[2] = { 1, 2 };
double tomb3[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
Matrix* matrix2 = mtrxCreate(1, 2, tomb2);
Matrix* matrix3 = mtrxCreate(3, 3, tomb3);

Matrix* matrixTomb[3] = {matrix, matrix2, ma}
FILE* file = fopen("mtrx.txt", "w");
mtrxExportArray(file, matrixTomb, 3);
fclose(file);

/* `mtrx.txt`
[2 2] 1.00 2.00 3.00 4.00
[1 2] 1.00 2.00
[3 3] 1.00 2.00 3.00 4.00 5.00 6.00 7.00 8.00 9.00
*/
```

### <code>int mtrxImport(Matrix*\*\* target, FILE* file) </code>

Ennek segítségével tudjuk importálni az általunk kiexportált mátrixokat egy fájlból. A függvény paraméterként kér egy **NULL** Matrix\*\*\* típust(A memóriacíme annak a tömbnek, amely mátrix pointereket tárol). **A fájlt nem zárja le a függvény**. A függvény megpróbál minden sorból beolvasni, de ha nem sikerül ugrik a következő sorra. A függvény a beolvasott mátrixok darabszámával tér vissza.

```c
Matrix** target = NULL;
FILE* file = fopen("matrix.txt", "r");
int len = mtrxImport(&target, file);

for(int i=0; i<len; i++) mtrxPrint(target[i]);
for(int i=0; i<len; i++) mtrxFree(target[i]);
free(target);
```

<div style="page-break-after: always;"></div>

## Haladó

### <code>Matrix* mtrxTransponate(Matrix* source)</code>

A **source** transzponáltját készíti el új helyre. A főátlóra tükrözi minden elemét. Visszatér az új mátrix pointerével, hiba esetén **NULL**.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
Matrix* transponated = mtrxTransponate(matrix);
mtrxPrint(transponated);

/* Output:
/ 1 3 \
\ 2 4 / 2x2
*/
```

### <code>Matrix* mtrxSwapRow(Matrix* source, int r1, int r2)</code>

Megcserél két sort a mátrixban. Ez leginkább a Gauss-eliminációhoz szükséges, de ha esetleg valamilyen új algoritmust építenénk, akkor adott a lehetőség ezzel a függvénnyel is. A sorszámozás **1**-től kezdődik. **NULL**-al tér vissza hibás bemenet esetén.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
mtrxSwapRow(matrix, 1, 2);
mtrxPrint(matrix);
/* Output:
/ 3 4 \
\ 1 2 / 2x2 */
```

### <code>Matrix* mtrxAddRow(Matrix* source, int r1, double a, int r2)</code>

Hozzáadjuk az **r1** sorhoz az **r2** **a**-szorosát. Ez is a Gauss-eliminációhoz szükséges(és determináns számoláshoz). A sorszámozás **1**-től kezdődik. **NULL**-al tér vissza hibás bemenet esetén(nem létező sor).

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
mtrxAddRow(matrix, 2, -3, 1); // sor2 = sor2 + (-3) * sor1
mtrxPrint(matrix);
/* Output:
/ 1  2 \
\ 0 -2 / 2x2 */
```

<div style="page-break-after: always;"></div>

### <code>Matrix* mtrxMultiplRow(Matrix* source, double a, int r)</code>

Egy sort szorzunk **"a"** skalárral. Gauss-elimináció egyik alaplépése. **NULL**-al tér vissza hibás bemenet esetén.

```c
double tomb[4] = { 1, 2, 3, 4 };
Matrix* matrix = mtrxCreate(2, 2, tomb);
mtrxSwapRow(matrix, 1, 2);
mtrxMultiplRow(matrix, (double)1/3, 1);
mtrxPrint(matrix);
/* Output:
/ 1.00  1.33 \
\ 1.00  2.00 / 2x2 */
```
