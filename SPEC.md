# Mátrixkezelő könyvtár

#### Version: 0.1

A mátrixoknak széleskörű alkalmazási lehetőségei vannak, ilyen például többismeretlenes egyenletek reprezentálása és jóval egyszerűbb megoldása, de a mindennapi életben is szembefuthatnak velünk.

# Specifikáció

Készíts egy függvénykönyvtárat, amivel mátrixokat tudsz kezelni. A könyvtár képes legyen alapműveleteket elvégezni konstans számmal, valamint más mátrixokkal is.

## Struktúra és kezelés

Készíts egy fő struktúrát, amiben tárolod a mátrix méreteit(szélesség, magasság), valamint magát a mátrixot, ami egy kétdimenziós tömb, valós számokkal feltöltve, és ezt is használdd.

Legyen egy külön függvény is, amivel létre tudsz hozni egy n\*n méretű egységmátrixot.

A könyvtárban legyen olyan függvény, amivel létre tudsz hozni egy mátrixot egy tömbből dinamikus memóriakezeléssel, frissíteni tudsz egy-egy cellát, valamint felszabadítani a már nem szükséges mátrixokra, emellett legyen egy függvény, amivel másolni is tudsz egy mátrixot.

## Alapműveletek

A könyvtár tudjon konstans számot hozzáadni és kivonni a mátrixból, konstanssal tudjon szorozni, emellett legyen függvény arra is, hogy ellenőrizzük két mátrix egyenlőségét.

## Műveletek mátrixok között

Készíts egy függvényt, amivel két mátrixot össze tudsz szorozni. Fontos, hogy ellenőrizd a mátrixok összeszorzásának feltételét, ami:

<aside>

egy _n_ \* _k_ méretű **A** mátrixot akkor szorzhatjuk egy össze egy **B** mátrixxal, amennyiben *k*m\* méretű, vagyis az **A** mátrix oszlopainak száma meg kell egyezzen a **B** mátrix sorainak számával.

</aside>

Fontos azt is hozzátenni, hogy mátrixok szorzata valós számokkal ellentétben a **legtöbb esetben nem kommutatív**.

A mátrixok **diadikus szorzata** mellett a **skaláris** szorzatát is legyen képes kiszámolni, ami a diadikus szorzatból létrejött mátrix főátlóin lévő valós számok összege.

A mátrix szorzása mellett legyen lehetőség két mátrixot összeadni és kivonni egymásból, ezeket csak egyező dimenziójú mátrixokkal lehet megtenni, így fontos ezt ellenőrizni.

## Haladó

### Gauss-elimináció

A Gauss-eliminációval többismeretlenes egyenletrendszereket tudunk megoldani úgy, hogy az ismeretlenek együtthatóit egy oszlopba rendezzük, majd addig végzünk a sorokkal műveleteket, míg nem formáljuk át egy felsőháromszög mátrix formába, ezzel leegyszerűsítve a dolgunkat az egyenletrendszerrel.

A Gauss-eliminációhoz szükséges, hogy a mátrix két oldalát össze tudjuk “forrasztani”, ez az úgynevezett “augmented matrix”. Hozz létre egy függvényt, amely létrehoz egy új mátrixot, amivel két mátrixot össze tud tenni egymás mellé.

A Gauss-elimináció során a következő műveleteket végezhetjük soronként: nem nulla konstans számmal szorozhatunk, másik sor nem nulla konstans számmal való szorzatát hozzáadhatjuk, valamint felcserélhetünk két sort. **Fontos, hogy amennyiben a Gauss-elimináció során sort cserélünk, a determináns előjele változik**(páratlan számű sorcsere esetén). A műveleteket szervezd ki külön függvényekbe, a Gauss-elimináció függvénye pedig térjen vissza a sorcserék számával.

### Determináns

Hozz létre egy függvényt, amivel determinánst tudsz számolni. Célszerű először Gauss-eliminációt alkalmazni, mivel ilyenkor a mátrix determinánsa egyszerűen a főátlón lévő számok szorzata

### Transzponálás

A transzponálás egy viszonylag egyszerű, mégis fontos eleme a mátrixok kezelésének. Implementálj egy függvényt, ami ezt megteszi egy új mátrixot létrehozva.

## I/O műveletek

A függvénykönyvtár tartalmazzon egy export függvényt, amivel ki tudsz exportálni egy tömbnyi, vagy egy darab mátrixot. A mátrixokat egy egy sorba írja ki egy fájlba, a sor tartalmazza a mátrix szélességét és magasságát.

Legyen emellett egy függvény, amivel ki tudsz íratni a standard kimenetre egy mátrixot jól látható formában.

---

Végezetül hozz létre egy főprogramot, amelyben megmutatod a könyvtár adta lehetőségeket.
