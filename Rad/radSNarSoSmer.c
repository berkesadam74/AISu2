// Rad s nárazníkom a so smerníkom na koniec radu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (ATOM *)malloc(sizeof(ATOM))

typedef int TYP; // Definovanie typu udajov ukladaných v ATOMe

typedef struct atom
{
    TYP h;
    struct atom *nasl;
} ATOM;

typedef struct
{
    ATOM *zac, *kon; // smerníky ktoré sledujú pozíciu v rade
} RAD;

// Základné funkcie
void ini(RAD *r);
int empty(RAD r);
void push(RAD *r, TYP x);
void shift(RAD *r);
void hodnota(RAD r, TYP *x);
void destroy(RAD *r);

int main(int argc, char **argv)
{
    RAD a;
    ini(&a);

    char s[] = "skuska";
    int p, len = strlen(s);

    for (int i = 0; i < len; i++)
        push(&a, s[i]);

    while (!empty(a))
    {
        hodnota(a, &p);
        printf("%c ", p);
        shift(&a);
    }
    putchar('\n');

    for (int i = 0; i < 15; i++)
        push(&a, i + 1);

    while (!empty(a))
    {
        hodnota(a, &p);
        printf("%d ", p);
        shift(&a);
    }
    putchar('\n');

    destroy(&a);

    return 0;
}
//--------------------------
void ini(RAD *r)
{
    // Vytvorím nárazník, a nastavím smerníky zac a kon
    r->kon = ML;
    r->kon->nasl = NULL;
    r->zac = r->kon;
}
int empty(RAD r)
{
    // Vieme že rad je prázdny, keď zac->nasl ukazuje na nárazník
    return r.zac->nasl == NULL;
}
void push(RAD *r, TYP x)
{
    // kon ukazuje na nárazník, vložím tam hodnotu, a vytvorím nový narazník po kon, prestavím kon na nový nárazník
    r->kon->h = x;
    r->kon->nasl = ML;
    r->kon = r->kon->nasl;
    r->kon->nasl = NULL;
}
void shift(RAD *r)
{
    // V rade odoberáme zo začiatku, použijem pomocný ATOM, do pomocného nastavím zac, zac posuniem do zac->nasl, vymažem pomocný pointer s funkciou free()
    if (!empty(*r))
    {
        ATOM *p = r->zac;
        r->zac = r->zac->nasl;
        free((void *)p);
    }
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
void hodnota(RAD r, TYP *x)
{
    // do premennej X zapíšem hodnotu so smerníka na začiatok
    if (!empty(r))
        *x = r.zac->h;
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
void destroy(RAD *r)
{
    // pokiaľ rad nie je prázdny, odstraňujem od predu atómy, na konci odstráním nárazník a nastavím smerníky na NULL
    while (!empty(*r))
        shift(r);
    free((void *)r->kon);
    r->kon = r->zac = NULL;
}