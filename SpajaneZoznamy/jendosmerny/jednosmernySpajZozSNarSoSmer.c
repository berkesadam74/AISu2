// Jednosmerny spajany zoznam s nárazníkom na konci i na začiatku a so smerníkmy na koniec a začiatok
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
    ATOM *zac, *kon, *ind;
} ZOZNAM;

// Základné funkcie
void ini(ZOZNAM *z);
int empty(ZOZNAM z);
int isHead(ZOZNAM z);
int isTail(ZOZNAM z);
void add(ZOZNAM *z, TYP x);
void erase(ZOZNAM *z);
void hodnota(ZOZNAM z, TYP *x);
void head(ZOZNAM *z);
void tail(ZOZNAM *z);
void cw(ZOZNAM *z);
void ccw(ZOZNAM *z);
void destroy(ZOZNAM *z);

int main(int argc, char **argv)
{
    ZOZNAM a;
    ini(&a);

    char s[] = "pokusny retazec";
    int p, len = strlen(s);

    for (int i = 0; i < len; i++)
        add(&a, s[i]);

    head(&a);
    cw(&a);
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
//------------------------
void ini(ZOZNAM *z)
{
    // Inicializujem nárazníky na začiatku a na konci
    z->zac = ML;
    z->kon = ML;
    z->kon->nasl = NULL;
    z->zac->nasl = z->kon;
    z->ind = z->kon;
}
int empty(ZOZNAM z)
{
    // Vtedy je zoznam prázdny, keď smernik zac->nasl ukazuje na naraznik na konci
    return z.zac->nasl == z.kon;
}
int isHead(ZOZNAM z)
{
    // index ukazuje na zaciatok
    return z.ind == z.zac;
}
int isTail(ZOZNAM z)
{
    // index ukazuje na koniec
    return z.ind == z.kon;
}
void add(ZOZNAM *z, TYP x)
{
    // keď som na konci zoznamu, vyrobím nový nárazník, dá sa spraviť aj tak, že nový ATOM pridám pred nárazníkom na koniec
    if (isTail(*z))
    {
        z->kon->h = x;
        z->kon->nasl = ML;
        z->kon = z->kon->nasl;
        z->kon->nasl = NULL;
        z->ind = z->kon;
    }
    else
    {
        // Pomocou pomocného atómu pridávam do stred zoznamu
        ATOM *p = ML;
        p->h = x;
        p->nasl = z->ind->nasl;
        z->ind->nasl = p;
    }
}
void erase(ZOZNAM *z)
{
    // Pomocou pomocného ATOMu odstraňujem zo zoznamu
    if (!empty(*z))
    {
        if (!isHead(*z))
        {
            if (!isTail(*z))
            {
                ATOM *p = z->zac;
                while (p->nasl != z->ind)
                    p = p->nasl;
                p->nasl = z->ind->nasl;
                free((void *)z->ind);
                z->ind = p->nasl;
            }
            else
                fprintf(stderr, "Sme na konecnom narazniku.\n");
        }
        else
            fprintf(stderr, "Sme na narazniku na zaciatku zoznamu.\n");
    }
    else
        fprintf(stderr, "Zaznam je prazdny.\n");
}
void hodnota(ZOZNAM z, TYP *x)
{
    if (!empty(z))
    {
        // Zapíšem hodnotu kde ukazuje index do X
        if (!isHead(z))
        {
            if (!isTail(z))
            {
                *x = z.ind->h;
            }
            else
                fprintf(stderr, "Sme na konecnom narazniku.\n");
        }
        else
            fprintf(stderr, "Sme na narazniku na zaciatku zoznamu.\n");
    }
    else
        fprintf(stderr, "Zaznam je prazdny.\n");
}
void head(ZOZNAM *z)
{
    if (!isHead(*z))
        z->ind = z->zac;
    else
        fprintf(stderr, "Sme na zaciatku zaznamu.\n");
}
void tail(ZOZNAM *z)
{
    if (!isTail(*z))
        z->ind = z->kon;
    else
        fprintf(stderr, "Sme na konci zaznamu.\n");
}
void cw(ZOZNAM *z)
{
    // posúvám index Clock wise
    if (!isTail(*z))
        z->ind = z->ind->nasl;
    else
        fprintf(stderr, "Sme na konci zaznamu.\n");
}
void ccw(ZOZNAM *z)
{
    // Posúvám index Counter clock wise
    if (!isHead(*z))
    {
        ATOM *p = z->zac;
        while (p->nasl != z->ind)
            p = p->nasl;
        z->ind = p;
    }
    else
        fprintf(stderr, "Sme na zaciatku zaznamu.\n");
}
void destroy(ZOZNAM *z)
{
    // Odstránim ATOMy po jednom, a na koniec odstránim nárazníky
    while (!empty(*z))
        erase(z);
    free((void *)z->zac);
    free((void *)z->kon);
    z->kon = z->zac = z->ind = NULL;
}