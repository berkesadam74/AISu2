// Zásobník s nárazníkom
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (ATOM *)malloc(sizeof(ATOM))

// Definujem že aký typ hodnoty bude v zásobníku
typedef int TYP;

// Štruktúra ATOM
typedef struct atom
{
    TYP h;
    struct atom *nasl;
} ATOM;

// Základné funkcie
void ini(ATOM **zas);
int empty(ATOM *zas);
void push(ATOM **zas, TYP x);
void hodnota(ATOM *zas, TYP *x);
void pop(ATOM **zas);
void destroy(ATOM **zas);

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
        pop(&a);
    }
    putchar('\n');

    destroy(&a);

    return 0;
}

//-------------------------------------
void ini(ATOM **zas)
{
    // Vytvorím nárazník, aby som vedel kde je spodok zásobníka
    *zas = ML;
    (*zas)->nasl = NULL;
}
int empty(ATOM *zas)
{
    // Keď som pri nárazniku, viem že zásobník je prázdny
    return zas->nasl == NULL;
}
void push(ATOM **zas, TYP x)
{
    // Vytvorím pomocný ATOM, kde hodim hodnotu z X, pomocný ATOM bude ukazovať na vrch zásobníka a potom prehodím vrch na pomocný ATOM
    ATOM *p = ML;
    p->h = x;
    p->nasl = *zas;
    *zas = p;
}
void hodnota(ATOM *zas, TYP *x)
{
    // Keď zásobník nie je prázdny, tak zapíšem hodnotu, čo je na vrchu do X
    if (!empty(zas))
        *x = zas->h;
    else
        fprintf(stderr, "Zasobnik je prazdny.\n");
}
void pop(ATOM **zas)
{
    // Vytvorím pomocný ATOM, nastavím ho ako vrch zásobnika, potom vrch zásobnika prehodim na vrch->nasl a odstránim pomocný ATOM s použitím free, tým pádom vymažem original vrch zásobníka
    if (!empty(*zas))
    {
        ATOM *p = *zas;
        *zas = (*zas)->nasl;
        free((void *)p);
    }
    else
        fprintf(stderr, "Zasobnik je prazdny.\n");
}
void destroy(ATOM **zas)
{
    // Odstránim všetky atomy, a potom nárazník
    while (!empty(*zas))
        pop(zas);
    free((void *)*zas);
    *zas = NULL;
}