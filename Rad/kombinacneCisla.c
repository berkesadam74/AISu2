// Kombinačné čísla pomocou radu s nárazníkom a bez smerníka
#include <stdio.h>
#include <stdlib.h>
#define ML (ATOM *)malloc(sizeof(ATOM))

typedef struct atom
{
    long long c;
    struct atom *nasl;
} ATOM;

// Základné funkcie radu
void ini(ATOM **);
int empty(ATOM *);
void push(ATOM **, int);
void shift(ATOM **);
void hodnota(ATOM *, long long int *);
void destroy(ATOM **);

int main(int argc, char **argv)
{
    ATOM *a;
    ini(&a);
    push(&a, 1); // Nastavím prvý riadok Pascalovho trojuholníka
    int poc = 1; // Ráta počet prvkov v rade

    int n, k;
    printf("Zadaj n: ");
    scanf("%d", &n);
    printf("Zadaj k: ");
    scanf("%d", &k);

    // Zostrojím n-tý riadok pascalovho torjuholníka
    for (int i = 0; i < n; i++)
    {
        long long int curr, prev = 0;
        push(&a, 0);
        poc++;
        for (int j = 0; j < poc; j++)
        {
            hodnota(a, &curr);
            shift(&a);
            poc--;
            push(&a, curr + prev);
            poc++;
            prev = curr;
        }
    }

    // Keďže potrebujeme k-ty člen z radu, tak odstráním čisla pokiaľ nedôjdem na k-tie čislo
    for (int i = 0; i < k; i++)
        shift(&a);

    // Teraz mám k-ty člen ako prvý v rade, zapíšem ho do vysledku a vypíšem
    long long int vysledok;
    hodnota(a, &vysledok);
    printf("Vysledok je: %lld\n", vysledok);

    destroy(&a);

    return 0;
}
//----------------------------
void ini(ATOM **r)
{
    *r = ML;
    (*r)->nasl = NULL;
}
int empty(ATOM *r)
{
    return r->nasl == NULL;
}
void push(ATOM **r, int x)
{
    ATOM *p = *r;
    while (p->nasl != NULL)
        p = p->nasl;
    p->c = x;
    p->nasl = ML;
    p = p->nasl;
    p->nasl = NULL;
}
void shift(ATOM **r)
{
    if (!empty(*r))
    {
        ATOM *p = *r;
        *r = (*r)->nasl;
        free((void *)p);
    }
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
void hodnota(ATOM *r, long long int *x)
{
    if (!empty(r))
    {
        *x = r->c;
    }
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
void destroy(ATOM **r)
{
    while (!empty(*r))
        shift(r);
    free((void *)*r);
    *r = NULL;
}