// Obojsmerný spájaný zoznam bez nárazníkom na začiatku a na konci a
// so smerníkmy na začiatok a na koniec
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (ATOM *)malloc(sizeof(ATOM))

typedef int TYP; // Typ hodnoty čo ukladáme do zoznamu

typedef struct atom
{
    TYP h;
    struct atom *nasl, *pred;
} ATOM;

typedef struct
{
    ATOM *zac, *kon, *ind;
} ZOZNAM;

// Základné funkcie
void ini(ZOZNAM *z);
int empty(ZOZNAM z);
int isHead(ZOZNAM z);
int isTail(ZOZNAM z);
void add(ZOZNAM *z, TYP x);
void erase(ZOZNAM *z);
void value(ZOZNAM z, TYP *x);
void cw(ZOZNAM *z);  // Posúvanie indexu v smere CLOCKWISE
void ccw(ZOZNAM *z); // Posúvanie indexu v smere COUNTER CLOCKWISE
void head(ZOZNAM *z);
void tail(ZOZNAM *z);
void destroy(ZOZNAM *z);

int main(int argc, char *argv[])
{
    char s[] = "pokusny retazec";
    int p, len = strlen(s);

    ZOZNAM a;
    ini(&a);

    for (int i = 0; i < len; i++)
        add(&a, s[i]);

    head(&a);
    while (!empty(a))
    {
        value(a, &p);
        printf("%c ", p);
        erase(&a);
    }
    putchar('\n');

    destroy(&a);

    return 0;
}

//----------------------------------
void ini(ZOZNAM *z) // Všetky smerníky nastavíme na NULL
{
    z->zac = z->kon = z->ind = NULL;
}
int empty(ZOZNAM z) // Keď z->ind sa rovná NULL, vieme že zoznam je prázdny
{
    return z.ind == NULL;
}
int isHead(ZOZNAM z) // Test či sme na začiatku zoznamu
{
    return z.ind == z.zac;
}
int isTail(ZOZNAM z) // Test či sme na konci zoznamu
{
    return z.ind == z.kon;
}
void add(ZOZNAM *z, TYP x) // 3 typy sa nám môžu vyskytnúť
{
    if (empty(*z)) // Keď zoznam je prázdny, vytvoríme nový ATOM na indexe, smerníky zac a kon nastavíme
                   // na tento ATOM, okolo dáme NULL
    {
        z->ind = ML;
        z->zac = z->kon = z->ind;
        z->ind->h = x;
        z->ind->nasl = NULL;
        z->ind->pred = NULL;
    }
    else if (isTail(*z)) // Keď sme na konci, vytvoríme ATOM po smerniku kon, posunieme smerník na kon
    {
        z->kon->nasl = ML;
        z->kon = z->kon->nasl;
        z->kon->pred = z->ind;
        z->kon->nasl = NULL;
        z->kon->h = x;
        z->ind = z->kon;
    }
    else // keď sme niekde na strede zoznamu, pridávame nový ATOM s použitím pomocného ATOMu
    {
        ATOM *p = ML;
        p->h = x;
        p->nasl = z->ind->nasl;
        p->pred = z->ind;
        p->nasl->pred = p;
        z->ind->nasl = p;
        z->ind = p;
    }
}
void erase(ZOZNAM *z)
{
    if (!empty(*z))
    {
        if (z->zac == z->kon) // Keď zoznam má jeden ATOM, odstránime ten jeden ATOM, všetky smerníky nastavíme na NULL
        {
            free((void *)z->ind);
            z->zac = z->kon = z->ind = NULL;
        }
        else if (isHead(*z)) // Keď sme na začiatku zoznamu, použijeme pomocný ATOM, posunieme zac smerník, odstráníme pomocný ATOM
        {
            ATOM *p = z->zac;
            z->zac = p->nasl;
            z->ind = p->nasl;
            z->zac->pred = NULL;
            free((void *)p);
        }
        else if (isTail(*z)) // Keď sme na konci, posunieme, kon do predu, pomocou indexu odstránime posledný ATOM, posunieme index
        {
            z->kon = z->kon->pred;
            free((void *)z->ind);
            z->ind = z->kon;
            z->kon->nasl = NULL;
        }
        else // Keď sme na strede niekde, použijeme pomocný ATOM
        {
            ATOM *p = z->ind;
            z->ind = z->ind->nasl;
            p->pred->nasl = z->ind;
            z->ind->pred = p->pred;
            free((void *)p);
        }
    }
}
void value(ZOZNAM z, TYP *x)
{
    if (!empty(z)) // Keď zoznam nie je prázdny, zapíšeme do x hodnotu z indexu
        *x = z.ind->h;
}
void cw(ZOZNAM *z)
{
    if (!isTail(*z)) // Keď nie sme na konci zoznamu, posúvame index v smere hodinových ručičiek
        z->ind = z->ind->nasl;
    else
        fprintf(stderr, "Uz sme na konci zoznamu.\n");
}
void ccw(ZOZNAM *z)
{
    if (!isHead(*z)) // Keď nie sme na začiatku zoznamu, posúvame index v proti smere hodinových ručičiek
        z->ind = z->ind->pred;
    else
        fprintf(stderr, "Uz sme na zaciatku zoznamu.\n");
}
void head(ZOZNAM *z)
{
    z->ind = z->zac; // Skočime na začiatok zoznamu
}
void tail(ZOZNAM *z)
{
    z->ind = z->kon; // Skočíme na koniec zoznamu
}
void destroy(ZOZNAM *z)
{
    head(z); // Skočíme na začiatok zoznamu a po jednom odstraňujeme ATOMy, na konci všetky smerníky nastavíme na NULL
    while (!empty(*z))
        erase(z);
    z->ind = z->zac = z->kon = NULL;
}