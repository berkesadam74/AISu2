// Rad bez nárazníka a bez smerníka na koniec radu
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
void push(ATOM **r, TYP x);
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
void ini(ATOM **r)
{
    // Nastavím r aby ukazoval na NULL, ešte tu nemáme žiadny ATOM
    *r = NULL;
}
int empty(ATOM *r)
{
    // keď r ukazuje na NULL, tak viem že rad je prázdny
    return r == NULL;
}
void push(ATOM **r, TYP x)
{
    // Keď je rad prázdny, musím vytvoriť prvý ATOM
    if (empty(*r))
    {
        *r = ML;
        (*r)->h = x;
        (*r)->nasl = NULL;
    }
    else // keď rad nie je prázdny, postupujem ako pri rade s narazníkom bez smerníka
         // Vytvorím pomocný ATOM, nastavím ho na prvý ATOM kde ukazuje r a posúvám ho pokial
         // nenájdem p->nasl == NULL, tu vytvorím nový atóm a vložím tam hodnotu z X
    {
        ATOM *p = *r;
        while (p->nasl != NULL)
            p = p->nasl;
        p->nasl = ML;
        p = p->nasl;
        p->h = x;
        p->nasl = NULL;
    }
}
void shift(ATOM **r)
{
    // Pomocou pomocného atómu, čo nastavým ako začiatok radu, začiatok posuniem o jedno
    // pomocný atóm vymažem s použitím free()
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
    // Ak rad nie je prázdny, vrátim hodnotu do X zo smerníka kde ukazuje r
    if (!empty(r))
        *x = r->h;
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
void destroy(ATOM **r)
{
    // Pokial nedôjdem na koniec radu, tak stále po jednom vymažem atómy, nárazník tu nie je, netreba ešte raz použit free()
    while (!empty(*r))
        shift(r);
    *r = NULL;
}