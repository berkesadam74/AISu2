// Rad bez nárazníka a so smerníkom na koniec radu
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
    ATOM *kon, *zac;
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
    // Inicializujem smerníky na NULL
    r->kon = r->zac = NULL;
}
int empty(RAD r)
{
    // Keď zac ukazuje na NULL, tak vieme že rad je prázdny
    return r.zac == NULL;
}
void push(RAD *r, TYP x)
{
    // Keď rad je prázdny, musíme vytvoriť prvý ATOM
    if (empty(*r))
    {
        r->kon = ML;
        r->zac = r->kon;
        r->kon->h = x;
        r->kon->nasl = NULL;
    }
    else // Keď nie je prázdny, tak vkladáme nový atom na koniec, a posúvame smerník na koniec
    {
        r->kon->nasl = ML;
        r->kon = r->kon->nasl;
        r->kon->h = x;
        r->kon->nasl = NULL;
    }
}
void shift(RAD *r)
{
    // Odstraňujeme zo začiatku radu, posunieme smerník zac o jedno ďalej
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
    // Keď rad nie je prázdny, zapíšem hodnotu so smernika na zac do X
    if (!empty(r))
        *x = r.zac->h;
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
void destroy(RAD *r)
{
    // Od začiatku po jednom vymažem všetky atómy
    while (!empty(*r))
        shift(r);
    r->zac = r->kon = NULL;
    r = NULL;
}
