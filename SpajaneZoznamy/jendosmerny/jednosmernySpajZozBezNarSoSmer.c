// Jednosmerný spájaný zoznam bez nárazníkov a so smerníkmy na koniec a začiatok
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ML (ATOM *)malloc(sizeof(ATOM))

typedef int TYP;

typedef struct atom
{
    TYP h;
    struct atom *nasl;
} ATOM;

typedef struct
{
    ATOM *zac, *ind, *kon;
} ZOZNAM;

// Základné funkcie
void ini(ZOZNAM *z);
int empty(ZOZNAM z);
int isHead(ZOZNAM z);
int isTail(ZOZNAM z);
void add(ZOZNAM *z, TYP x);
void erase(ZOZNAM *z);
void hodnota(ZOZNAM z, TYP *x);
void cw(ZOZNAM *z);  // posúvanie indexu CLOCKWISE
void ccw(ZOZNAM *z); // posúvanie indexu COUNTER CLOCKWISE
void head(ZOZNAM *z);
void tail(ZOZNAM *z);
void destroy(ZOZNAM *z);

int main()
{
    char s[] = "pokusny retazec";
    int len = strlen(s), p;

    ZOZNAM a;
    ini(&a);

    for (int i = 0; i < len; i++)
        add(&a, s[i]);

    head(&a);
    while (!empty(a))
    {
        hodnota(a, &p);
        printf("%c ", p);
        erase(&a);
    }
    putchar('\n');

    destroy(&a);

    return 0;
}
//---------------------------
void ini(ZOZNAM *z)
{
    z->ind = z->zac = z->kon = NULL; // Inicializácia zoznamu
}
int empty(ZOZNAM z)
{
    return z.zac == NULL; // Keď smerník zac ukazuje na NULL tak zoznam je prázdny
}
int isHead(ZOZNAM z)
{
    return z.ind == z.zac; // Keď index ukazuje na smerník zac tak som na začiatky (head)
}
int isTail(ZOZNAM z)
{
    return z.ind == z.kon; // Keď index ukazuje na smerník kon tak som na konci zoznamu (tail)
}
void add(ZOZNAM *z, TYP x)
{
    ATOM *tmp = ML;
    tmp->h = x;
    tmp->nasl = NULL;

    if (empty(*z)) // Keď zoznam je prázdny, tak vytvorím nový ATOM na indexe (čo je teraz NULL), z->zac a z->kon budú ukazovať na tento ATOM
    {
        z->ind = tmp;
        z->zac = z->kon = z->ind;
    }
    else if (isTail(*z)) // Keď som na konci tak pridám nový ATOM za ATOMom čo je na konci teraz, prehodím smerník kon na nový ATOM
    {
        z->kon->nasl = tmp;
        z->kon = z->ind = tmp;
    }
    else // keď pridávam do stredu alebo na začiatok, tak pridávam nový ATOM po ATOMe kďe ukazuje index
    {
        tmp->nasl = z->ind->nasl;
        z->ind->nasl = tmp;
        z->ind = tmp;
    }
}
void erase(ZOZNAM *z)
{
    if (!empty(*z)) // Toto môžem spraviť iba vtedy keď zoznam nie je prázdny
    {
        if (isHead(*z)) // Keď som na začiatku, použijem pomocný ATOM, smerník zac prehodím na zac->nasl, odstránim pomocný ATOM, index posuniem
        {
            ATOM *tmp = z->zac;
            z->zac = z->zac->nasl;
            free((void *)tmp);
            z->ind = z->zac;
        }
        else if (isTail(*z)) // Keď som na konci, použijem pomocný ATOM aby som našiel ATOM pred koncom, vymažem ATOM na konci, konečný smerník prehodím na ATOM čo je teraz v pomocnom ATOMe
        {
            ATOM *tmp = z->zac;
            while (tmp->nasl != z->kon)
                tmp = tmp->nasl;
            free((void *)z->kon);
            tmp->nasl = NULL;
            z->kon = tmp;
        }
        else // Tiež použijem pomocný ATOM, aby som našiel ATOM pred indexom, prehodím smerník nasl z ATOMU na index do predošlého ATOMu, odstránim ATOM na indexe, a prehodím index na predošlý ATOM
        {
            ATOM *tmp = z->zac;
            while (tmp->nasl != z->ind)
                tmp = tmp->nasl;
            tmp->nasl = z->ind->nasl;
            free((void *)z->ind);
            z->ind = tmp;
        }
    }
}
void hodnota(ZOZNAM z, TYP *x)
{
    if (!empty(z)) // Keď zoznam nie je prázdny, zapíšem hodnotu na indexe do premennej X
        *x = z.ind->h;
}
void cw(ZOZNAM *z)
{
    if (!isTail(*z)) // Keď nie som na konci zoznamu, tak posúvám index o jeden ATOM k smeru na koniec
        z->ind = z->ind->nasl;
}
void ccw(ZOZNAM *z)
{
    if (!isHead(*z)) // Ked nie som na začiatku, posúvam index k smeru na začiatok, použijem pomocný ATOM aby som našiel predošlý ATOM
    {
        ATOM *tmp = z->zac;
        while (tmp->nasl != z->ind)
            tmp = tmp->nasl;
        z->ind = tmp;
    }
}
void head(ZOZNAM *z)
{
    z->ind = z->zac; // Nastavím index na začiatok
}
void tail(ZOZNAM *z)
{
    z->ind = z->kon; // Nastavím index na koniec
}
void destroy(ZOZNAM *z)
{
    head(z);           // Nastavím index na začiatok
    while (!empty(*z)) // Pokial zoznam nie je prázdny, odstraňujem ATOMy po jednom
    {
        erase(z);
    }
    z->ind = z->kon = z->zac = NULL; // Všetky smerníky nastavím na NULL
}