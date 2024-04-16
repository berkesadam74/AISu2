// Obojsmerný spájaný zoznam s nárazníkom na začiatku a na konci
// so smerníkmy na začiatok a na koniec
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ML (ATOM *)malloc(sizeof(ATOM))

typedef int TYP; // typ hodnoty čo sa ukladá do ATOMu

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
int isTail(ZOZNAM z);
int isHead(ZOZNAM z);
void add(ZOZNAM *z, TYP x);
void erase(ZOZNAM *z);
void value(ZOZNAM z, TYP *x);
void cw(ZOZNAM *z);
void ccw(ZOZNAM *z);  // Posúvanie indexu CLOCKWISE
void head(ZOZNAM *z); // Posúvanie indexu COUNTER CLOCKWISE
void tail(ZOZNAM *z);
void destroy(ZOZNAM *z);

int main(int argc, char *argv[])
{
    ZOZNAM a;
    ini(&a);

    char s[] = "skuska";
    int len = strlen(s), p;

    for (int i = 0; i < len; i++)
        add(&a, s[i]);

    head(&a);
    cw(&a);
    while (!empty(a))
    {
        // ccw(&a);
        value(a, &p);
        printf("%c ", p);
        erase(&a);
    }
    putchar('\n');

    destroy(&a);

    return 0;
}

//-----------------------------------
void ini(ZOZNAM *z) // Vyrobia sa nárazníky
{
    z->zac = ML;
    z->kon = ML;
    z->zac->nasl = z->kon;
    z->zac->pred = NULL;
    z->kon->nasl = NULL;
    z->kon->pred = z->zac;
    z->ind = z->kon;
}
int empty(ZOZNAM z) // Keď zac->nasl ukazuje na kon vieme že zoznam je prázdny
{
    return z.zac->nasl == z.kon;
}
int isTail(ZOZNAM z) // Check či sme na konci
{
    return z.ind == z.kon;
}
int isHead(ZOZNAM z) // Check či sme na začiatku
{
    return z.ind == z.zac;
}
void add(ZOZNAM *z, TYP x) // Keď sme na konci pridáva nový ATOM do nárazníka a vytvorí nový konečný nárazník
{
    if (isTail(*z))
    {
        z->kon->h = x;
        z->kon->nasl = ML;
        z->kon->nasl->pred = z->kon;
        z->kon = z->kon->nasl;
        z->kon->nasl = NULL;
        z->ind = z->kon;
    }
    else // Keď sme na strede tak pomocou pomocného ATOMu doložím nový ATOM do zoznamu
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
    if (!empty(*z)) // Odoberiem ATOM na indexe, ale kontrolujem či nie som na nárazníkoch
    {
        if (!isHead(*z))
        {
            if (!isTail(*z))
            {
                ATOM *p = z->ind;
                z->ind = z->ind->nasl;
                z->ind->pred = p->pred;
                p->pred->nasl = z->ind;
            }
            else
            {
                fprintf(stderr, "Pokus o odobranie koncoveho naraznika.\n");
            }
        }
        else
        {
            fprintf(stderr, "Pokus o odobranie zaciatocneho naraznika.\n");
        }
    }
    else
    {
        fprintf(stderr, "Pokus o odobranie z prazdneho zoznamu.\n");
    }
}
void value(ZOZNAM z, TYP *x) // Vrátím hodnotu do X, kontrolujem či nie som na nárazníkoch a či nie je zoznam prázdny
{
    if (!isHead(z))
    {
        if (!isTail(z))
        {
            *x = z.ind->h;
        }
        else
        {
            *x = '#';
        }
    }
    else
    {
        *x = '#';
    }
}
void cw(ZOZNAM *z) // Posúvam index v smere ku konci
{
    if (!isTail(*z))
        z->ind = z->ind->nasl;
    else
        fprintf(stderr, "Sme na konci zoznamu.\n");
}
void ccw(ZOZNAM *z) // Posúvam index v smere ku začiatku
{
    if (!isHead(*z))
        z->ind = z->ind->pred;
    else
        fprintf(stderr, "Sme na zaciatku zoznamu.\n");
}
void head(ZOZNAM *z) // Skočím na začiatok zoznamu
{
    z->ind = z->zac;
}
void tail(ZOZNAM *z) // Skočím na koniec zoznamu
{
    z->ind = z->kon;
}
void destroy(ZOZNAM *z) // Skočim na začiatok zoznamu a pojednom odstraňujem ATOMy, na konci odstránim nárazníky
{
    head(z);
    while (!empty(*z))
        erase(z);
    free((void *)z->zac);
    free((void *)z->kon);
    z->kon = z->zac = z->ind = NULL;
}