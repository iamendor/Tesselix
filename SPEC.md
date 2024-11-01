# Mátrixkezelő könyvtár

#### Version: 1.0

A mátrixok széleskörű alkalmazási lehetőségekkel bírnak, például többismeretlenes egyenletek reprezentálására és megoldására. A könyvtár célja, hogy alapvető műveleteket hajtson végre mátrixokkal.

# Specifikáció

## Struktúra

Készíts egy struktúrát, amely tárolja a mátrix méreteit (szélesség és magasság) és a mátrixot egy kétdimenziós tömbben, valós számokkal.

### Funkcionalitás

1. **Mátrix Létrehozás:**
   - Készíts egy függvényt, amivel betöltesz egy tömböt egy új struktúrába
   - Készíts egy függvényt, ami létrehoz egy n\*n méretű egységmátrixot.
   - Legyen lehetőség cellák frissítésére és mátrixok felszabadítására a memóriából
   - Hozz létre függvényt, amivel másolni tudsz mátrixot.
   - Készíts funkciót a mátrixok kiterjesztésére, üres sorok és oszlopok hozzáadásával
   - Ennek az ellentétére is legyen alkalmas függvény
2. **Alapműveletek:**
   - Alapműveletek konstans és mátrixok között
   - Valósíts meg konstanssal való szorzást.
   - Implementálj egy mátrix-egyenlőség ellenőrző függvényt.
3. **Mátrixok Műveletei:**
   - Készíts egy függvényt két mátrix szorzására. Ellenőrizd az összeszorzás feltételeit (A oszlopainak száma = B sorainak száma).
   - Implementáld két mátrix összeadását és kivonását, de csak egyező dimenziójú mátrixok esetén, máshogy nem értelmezhető

## Haladó Funkciók

### Gauss-elimináció

Implementálj egy Gauss-eliminációs algoritmust a többismeretlenes egyenletrendszerek megoldására.

- Készíts egy függvényt az “augmented matrix” létrehozására két mátrix összeforrasztásával.
- Valósíts meg funkciókat a sorok szorzására, hozzáadására és cseréjére.
- A függvény térjen vissza a sorcserék számával, fontos lehet determináns számolásnál

<div style="page-break-after: always;"></div>

### Determináns

Hozz létre egy függvényt, amely a mátrix determinánsát számolja, célszerűen a Gauss-eliminációs módszer alkalmazásával.

### Transzponálás

Implementálj egy függvényt, amely a mátrix transzponálását végzi el új mátrix létrehozásával.

## I/O Műveletek

- Készíts egy exportáló függvényt, amely egy vagy több mátrixot ki tud írni egy fájlba, a mátrix legfontosabb jellemzőinek átlátható megjelenítésében.
- Ahhoz, hogy értelme legyen az exportáló függvényünknek, vice versa, be is kell tudnunk importálni fájlból, implementálj egy függvényt ennek érdekében, ami térjen vissza egy mátrix tömbbel.
- Implementálj egy függvényt a mátrixok standard kimenetre történő kiírására, jól látható formátumban. Az cellák mellett írja ki a mátrix szélességét és magasságát.

## Főprogram

Valósíts meg egy főprogramot, amely bemutatja a könyvtár funkcionalitását, példákkal illusztrálva az összes említett funkció használatát.
