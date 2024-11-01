# Tesselix példa program

Próbáld ki a könyvtár adottságait az `example.c` fájlban.

## Fordítás

Először is le kell fordítani a könyvtárat, majd a programfájlt. A legegyszerűbben ezt a `make`-el lehetséges.

```
make bin/example
```

---

Ha `gcc`-t szeretnél csak használni, akkor a következő lépések szükségesek:<br>

#### 1. Object fájlok generálása

Először a könyvtár fájlokat

```
gcc -c -Iinclude -Wall -Werror src/*.c
```

Utána a főprogramot

```
gcc -c -Iinclude -Wall -Werror example.c
```

#### 2. Linkelés

```
gcc -o example *.o
```

## Futtatás

```
./example
```

## A program

A bemutató program egy egyszerű mátrix bekérő a standard bemenetről, amit utána akár tovább is lehet írni, ez a program egy megfelelő alap, hogy használhassuk a könyvtár adta lehetőségeket, részletesebb használatért nézdd meg a **README** fájlt, vagy a **main.c** forráskódot, ahol részletesen minden függvényt láthatsz éles tesztelés alatt.
