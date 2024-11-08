#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#include "debugmalloc.h"

/* ervenytelenitjuk ezeket a makrokat, mert nekunk az igazi malloc/free kell */
#ifdef malloc
    #undef malloc
#endif
#ifdef free
    #undef free
#endif
#ifdef calloc
    #undef calloc
#endif
#ifdef realloc
    #undef realloc
#endif

/* a kanari merete, bajtokban */
static size_t const kanari_meret=128;
/* a kanari karakter */
static unsigned char const kanari='K';

/* csak egy kis veletlenszam-generator.
 * direkt van egy sajat, hogy a szabvany rand() belso allapotat
 * ne zavarja meg a sajat malloc.
 * 
 * klasszikus. :D
 */
static unsigned char debugmalloc_random()
{
    static unsigned int seed_1=0x00, seed_2=0x1e;
    unsigned int temp_1, temp_2;
    unsigned int carry, result;
 
    temp_1=(seed_1&0x0001) << 7;
    temp_2=(seed_2 >> 1)&0x007F;
    result=(seed_2)+((seed_2&0x0001) << 7);
    carry=(result >> 8);
    result=result&0x00FF;
    result=result+carry+0x13;
    carry=(result >> 8);
    seed_2=result&0x00FF;
    result=seed_1+carry+temp_1;
    carry=(result >> 8);
    result=result&0x00FF;
    result=result+carry+temp_2;
    seed_1=result&0x00FF;

    return seed_1;
}



/* a lefoglalt teruleteket nyilvantarto lista. */
typedef struct Lefoglalt {
    void *valodi;       /* ezt mallocoltuk mi */
    void *usernek;      /* ezt mutatjuk a juzernek */
    size_t meret;       /* ekkora teruletet kert a juzer. */
    
    char fv[16];        /* foglalo fuggveny */
    char cel[128];      /* a mallocnak ezt a kifejezest adta */
    char file[64];      /* ebben a fajlban tortent a foglalas */
    unsigned line;      /* a fajlnak ebben a soraban */
    
    struct Lefoglalt *prev, *next;  /* duplan lancolt listahoz */
} Lefoglalt;


static Lefoglalt eleje, vege;     /* strazsak. statikusan, hogy ne kelljen freezni :) */
static Lefoglalt *lista=NULL;     /* maga a lista; a pointer az eleje strazsara fog mutatni */

static char logfile[256]="";      /* ide logol */


/* a naplozofajl nevet allitja be. ha ures, stderr-re fog naplozni. */
void debugmalloc_naplofajl(char const *nev)
{
    strncpy(logfile, nev, sizeof(logfile));
    logfile[sizeof(logfile)-1]=0;
}

/* elodeklaracio az init() fv. szamara */
static void debugmalloc_programvegi_dump();

/* letrehozza a listat. a sajat malloc hivja egyszer, az elso meghivasakor.
 * a lista pointer (lista) inditaskori erteke NULL, de lesznek strazsak.
 * innen lehet tudni, hogy mar hivodott-e.
 * a strazsakat statikusan hoztam letre; vagyis ha inicializalva van mar a
 * lista, de a juzer meg nem foglalt memoriat, akkor nincs mallocolva
 * semmi! emiatt biztosan nem memleakel ez a program pluszban, ha a juzer
 * programja nem memleakelt. */
static void debugmalloc_init()
{
    eleje.prev=NULL;
    eleje.next=&vege;
    vege.prev=&eleje;
    vege.next=NULL;
    lista=&eleje;
    eleje.valodi=eleje.usernek=NULL;
    vege.valodi=vege.usernek=NULL;
    
    atexit(debugmalloc_programvegi_dump);
}


/* printfel a megadott fajlba, vagy stderr-re. */
static int debugmalloc_printf(char const *format, ...)
{
    va_list ap;
    int chars;
    FILE *f=stderr;
    
    if (strcmp(logfile, "")!=0) {
        f=fopen(logfile, "at");
        if (f==NULL) {
            f=stderr;
            fprintf(stderr, "debugmalloc: nem tudom megnyitni a %s fajlt irasra!\n", logfile);
        }
    }
    
    va_start(ap, format);
    chars=vfprintf(f, format, ap);
    va_end(ap);
    
    if (f!=stderr)
        fclose(f);
    
    return chars;
}


/* inicializalja a lefoglalt memoriat.
 * az elejere es a vegere kanari_meret meretben kanari kerul;
 * a kozepere, a juzernek valo reszbe pedig debugmalloc_random szamok. */
static void kanari_letrehoz(Lefoglalt *mem)
{
    unsigned char *teljes=(unsigned char *) mem->valodi;
    unsigned char *kanari1=teljes;
    unsigned char *kanari2=teljes+kanari_meret+mem->meret;
    size_t i;
    
    for (i=0; i<kanari_meret; ++i) {
        kanari1[i]=kanari;
        kanari2[i]=kanari;
    }
}

/* ellenorzi a kanarit.
 * igaz ertekkel ter vissza, ha rendben van. */
static int kanari_rendben(Lefoglalt const *mem)
{
    unsigned char *teljes=(unsigned char *) mem->valodi;
    unsigned char *kanari1=teljes;
    unsigned char *kanari2=teljes+kanari_meret+mem->meret;
    size_t i;
    
    for (i=0; i<kanari_meret; ++i) {
        if (kanari1[i]!=kanari)
            return 0;
        if (kanari2[i]!=kanari)
            return 0;
    }
    return 1;
}

/* memoriateruletet dumpol, a megadott meretben. */
static void debugmalloc_dump_memory(void const *memoria, size_t meret)
{
    unsigned char const *mem=(unsigned char const *) memoria;
    unsigned y, x;

    /* soronkent 16; meret/16-nyi sor lesz, persze felfele kerekitve */
    for (y=0; y<(meret+15)/16; y++) {
        debugmalloc_printf("      %04x  ", y*16);
        
        for (x=0; x<16; x++)
            if (y*16+x<meret)
                debugmalloc_printf("%02x ", mem[y*16+x]);
            else
                debugmalloc_printf("   ");
        debugmalloc_printf("  ");
        for (x=0; x<16; x++)
            if (y*16+x<meret) {
                unsigned char c=mem[y*16+x];
                debugmalloc_printf("%c", isprint(c)?c:'.');
            }
            else
                debugmalloc_printf(" ");

        /* uj sor */
        debugmalloc_printf("\n");
    }
}

/* egy adott lefoglalt tetelhez
 * tartozo adatokat irja ki. foglalas helye, modja;
 * meret, pointer. ad az elejerol dumpot is;
 * illetve a teljes elotte es utana kanarit kiirja,
 * ha kiderul, hogy az serult. */
static void debugmalloc_dump_elem(Lefoglalt const *iter)
{
    int kanari_ok=kanari_rendben(iter);
    
    debugmalloc_printf("  MEMORIATERULET: %p, kanari: %s\n"
                    "    foglalva itt: %s:%u\n"
                    "    foglalas modja: %s(%s) (%u bajt)\n",
        iter->usernek, kanari_ok?"ok":"**SERULT**",
        iter->file, iter->line,
        iter->fv, iter->cel, (unsigned) iter->meret);
    
    if (!kanari_ok) {
        debugmalloc_printf("    ELOTTE KANARI: \n");
        debugmalloc_dump_memory(iter->valodi, kanari_meret);
    }

    /* elso 64 byte dumpolasa */
    debugmalloc_printf("    memoria eleje: \n");
    debugmalloc_dump_memory(iter->usernek, iter->meret>64 ? 64:iter->meret);

    if (!kanari_ok) {
        /* erre a vs miatt van szukseg, mert az nem szereti a void *+size_t
         * kifejezest... trollok */
        unsigned char const *valodi_char=(unsigned char const *) iter->valodi;
        debugmalloc_printf("    UTANA KANARI: \n");
        debugmalloc_dump_memory(valodi_char+kanari_meret+iter->meret, kanari_meret);
    }
    
    debugmalloc_printf("\n");
}

/* kiirja a lefoglalt memoriateruletek listajat. */
void debugmalloc_dump()
{
    Lefoglalt *iter;
    
    debugmalloc_printf("** DEBUGMALLOC DUMP ************************************\n\n");
    for (iter=lista->next; iter!=&vege; iter=iter->next)
        debugmalloc_dump_elem(iter);
    debugmalloc_printf("** DEBUGMALLOC DUMP VEGE *******************************\n");
}






/* ez lefoglal egy megadott meretu memoriat;
 * pontosabban annal nagyobbat. elotte-utana kanarit inicializal,
 * a juzernek jaro reszt pedig random szamokkal tolti fel.
 * visszaterni a juzernek jaro terulet cimevel ter vissza. */
void *debugmalloc_malloc_full(size_t meret, char const *fv, char const *cel, char const *file, unsigned line, int zero)
{
    Lefoglalt *uj;
    void *valodi;
    unsigned char *usernek;
    
    /* lefoglalunk egy adag memoriat; elotte-utana tobblet hellyel. */
    valodi=malloc(meret+2*kanari_meret);
    if (valodi==NULL) {
        debugmalloc_printf("debugmalloc: %s @ %s:%u: nem sikerult %u meretu memoriat foglalni!\n",
                            fv, file, line, (unsigned) meret);
        /* mint az igazi malloc, nullpointert adunk */
        return NULL;
    }

    uj=(Lefoglalt *) malloc(sizeof(Lefoglalt));
    if (uj==NULL) {
        debugmalloc_printf("debugmalloc: %s @ %s:%u: le tudtam foglalni %u memoriat, de utana a sajatnak nem, sry\n",
                            fv, file, line, (unsigned) meret);
        abort();
    }
    uj->valodi=valodi;
    usernek=(unsigned char *) valodi+kanari_meret;
    uj->usernek=usernek;
    uj->meret=meret;

    strcpy(uj->fv, fv);
    strncpy(uj->cel, cel, sizeof(uj->cel));
    uj->cel[sizeof(uj->cel)-1]=0;
    strncpy(uj->file, file, sizeof(uj->file));
    uj->file[sizeof(uj->file)-1]=0;
    uj->line=line;

    kanari_letrehoz(uj);
    if (zero)
        memset(usernek, 0, meret);
    else {
        size_t i;
        for (i=0; i<meret; ++i)
            usernek[i]=debugmalloc_random();
    }
        
    /* lista elejere beszurja */
    if (lista==NULL)
        debugmalloc_init();
    uj->prev=lista;         /* elotte a strasza */
    uj->next=lista->next;   /* utana az eddigi elso */
    lista->next->prev=uj;   /* az eddigi elso elott az uj */
    lista->next=uj;         /* a strazsa utan az uj */
    
    return uj->usernek;
}

/* ez felszabaditja a memoriateruletet, amit a debugmalloc
 * foglalt. mivel a listaban megvannak az epp lefoglalt
 * teruletek, ezert ellenorizni tudja, helyes-e a free hivas.
 * ellenorzi a kanarit is, es kiirja az adatokat, ha helytelen.
 */
void debugmalloc_free_full(void *mem, char const *fv, char const *file, unsigned line)
{
    Lefoglalt *iter;
    unsigned char *usernek;
    size_t i;

    /* NULL pointerre nem csinalunk semmit */
    if (mem==NULL)
        return;

    /* ha meg sose mallocolt, a lista nincs inicializalva. a free-je se lehet helyes */
    if (lista==NULL) {
        debugmalloc_printf("debugmalloc: %s @ %s:%u: meg egyszer se hivtal mallocot!\n", fv, file, line);
        abort();
    }

    /* megkeressuk */
    for (iter=lista->next; iter!=&vege; iter=iter->next)
        if (iter->usernek==mem)
            break;
    
    /* ezt nyilvan ne engedjuk, mert akkor olyan pointer van, amit nem kene
     * free()-ni; ezt a rendes free() se birna */
    if (iter->usernek==NULL) {
        debugmalloc_printf("debugmalloc: %s @ %s:%u: olyan teruletet akarsz felszabaditani, ami nincs lefoglalva!\n", fv, file, line);
        abort();
    }
    
    /* szoval megtalaltuk. iter mutat a torlendo teruletre. */
    if (!kanari_rendben(iter)) {
        debugmalloc_printf("debugmalloc: %s @ %s:%u: a %p memoriateruletet tulindexelted!\n", fv, file, line, mem);
        debugmalloc_dump_elem(iter);
    }
    
    /* torles elott kitoltjuk randommal, ha esetleg dereferalna, akkor tuti fajjon */
    usernek=(unsigned char *) iter->usernek;
    for (i=0; i<iter->meret; ++i)
        usernek[i]=debugmalloc_random();
    /* memoria torlese; juzer memoriaja, es listabol */
    free(iter->valodi);
    iter->next->prev=iter->prev;
    iter->prev->next=iter->next;
    free(iter);
}


/* a megadott memoriat meretezi at.
 * a sajat free/malloc paros segitsegevel valositom meg. */
void *debugmalloc_realloc_full(void *oldmem, size_t newsize, char const *fv, char const *cel, char const *file, unsigned line)
{
    Lefoglalt *iter;
    void *ujmem;
    int masolni;
    
    /* ha null az oldmem, akkor ez ekvivalens egy malloc hivassal */
    if (oldmem==NULL)
        return debugmalloc_malloc_full(newsize, fv, cel, file, line, 0);
    
    /* ha az uj meret 0, akkor pedig egy free hivassal */
    if (newsize==0) {
        debugmalloc_free_full(oldmem, fv ,file, line);
        return NULL;
    }

    /* megkeressuk a regi memoriat, mert kell a meret */
    for (iter=lista->next; iter!=&vege; iter=iter->next)
        if (iter->usernek==oldmem)
            break;
    if (iter->usernek==NULL) {
        debugmalloc_printf("debugmalloc: %s @ %s:%u: olyan teruletet akarsz atmeretezni, ami nincs lefoglalva!\n", fv, file, line);
        abort();
    }
    
    ujmem=debugmalloc_malloc_full(newsize, fv, cel, file, line, 0);
    if (ujmem==NULL) {
        debugmalloc_printf("debugmalloc: %s @ %s:%u: nem sikerult uj memoriat foglalni az atmeretezeshez!\n", fv, file, line);
        /* ilyenkor nullal ter vissza, es a regit meghagyja */
        return NULL;
    }
    /* melyik kisebb? annyi bajtot kell masolni. */
    masolni=iter->meret < newsize? iter->meret : newsize;
    memcpy(ujmem, oldmem, masolni);
    debugmalloc_free_full(oldmem, fv, file, line);
    
    return ujmem;
}


/* ez hivodik meg a program vegen, az atexit() altal. */
static void debugmalloc_programvegi_dump()
{
    /* just in case */
    if (lista==NULL)
        return;
    
    /* ha nem ures a lista */
    if (lista->next->next!=NULL) {
        debugmalloc_printf("********************************************************\n"
                           "*\n"
                           "* MEMORIASZIVARGAS VAN A PROGRAMBAN!!!\n"
                           "*\n"
                           "********************************************************\n");
        debugmalloc_dump();
    }
}



/* ha szukseg lenne egy, az eredeti fuggvennyel prototipusban
 * kompatibilis valtozatra, ezek hasznalhatoak. */
void *debugmalloc_malloc(size_t meret)
{
    return debugmalloc_malloc_full(meret, "malloc", "ismeretlen", "(ismeretlen)", 0, 0);
}

void *debugmalloc_calloc(size_t nmemb, size_t meret)
{
    return debugmalloc_malloc_full(meret, "calloc", "ismeretlen", "(ismeretlen)", 0, 1);
}

void debugmalloc_free(void *mem)
{
    debugmalloc_free_full(mem, "free", "(ismeretlen)", 0);
}

void *debugmalloc_realloc(void *oldmem, size_t meret)
{
    return debugmalloc_realloc_full(oldmem, meret, "realloc", "ismeretlen", "(ismeretlen)", 0);
}