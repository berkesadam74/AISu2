// Rad s nárazníkom bez smerníka na koniec radu
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

// Základné funkcie
void ini(ATOM **r);
int empty(ATOM *r);
void push(ATOM *r, TYP x);
void shift(ATOM **r);
void hodnota(ATOM *r, TYP *x);
void destroy(ATOM **r);

int main(int argc, char **argv)
{
    ATOM *a;
    ini(&a);

    char s[] = "skuska";
    int p, len = strlen(s);

    for (int i = 0; i < len; i++)
        push(a, s[i]);

    while (!empty(a))
    {
        hodnota(a, &p);
        printf("%c ", p);
        shift(&a);
    }
    putchar('\n');

    for (int i = 0; i < 15; i++)
        push(a, i + 1);

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

//-------------------------
void ini(ATOM **r)
{
    // Vytvorím nárazník
    *r = ML;
    (*r)->nasl = NULL;
}
int empty(ATOM *r)
{
    // Rad je prázdny, keď som na nárazniku
    return r->nasl == NULL;
}
void push(ATOM *r, TYP x)
{
    // Vytvorím pomocný atom, posúvam ho až pokiaľ nedôjdem k nárazníku
    // do nárazníka vložím hodnotu z X, vytvorím nový nárazník na p->nasl
    ATOM *p = r;
    while (p->nasl != NULL)
        p = p->nasl;
    p->h = x;
    p->nasl = ML;
    p = p->nasl;
    p->nasl = NULL;
}
void shift(ATOM **r)
{
    // Vytvorím pomocný atom, kde vložím začiatok radu (*r), začiatok posuniem o jedno (r = r->nasl)
    // Vymažem pomocný atom, čo aktuálne ukazuje na starý začiatok radu
    if (!empty(*r))
    {
        ATOM *p = *r;
        *r = (*r)->nasl;
        free((void *)p);
    }
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
void hodnota(ATOM *r, TYP *x)
{
    // Keď rad nie je prázdny, tak hodím do X hodnotu zo začiatku radu
    if (!empty(r))
        *x = r->h;
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
void destroy(ATOM **r)
{
    // Vymažem atómy pokial nedôjdem k nárazníku, potom vymažem aj nárazník
    while (!empty(*r))
        shift(r);
    free((void *)*r);
    *r = NULL;
}