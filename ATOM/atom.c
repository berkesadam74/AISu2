#include <stdio.h>
#include <stdlib.h>
#define ML (ATOM *)malloc(sizeof(ATOM))

// Štruktúra ATOM
typedef struct atom
{
    int h;
    struct atom *nasl;
} ATOM;

int main(int argc, char **argv)
{
    ATOM *a;
    a = ML;
    a->nasl = NULL;
    a->h = 1;

    fprintf(stdout, "%d\n", a->h);

    a->nasl = ML;
    a->nasl->nasl = NULL;
    a->nasl->h = 2;

    // Aby som nemusel stále písat a->nasl->nasl-> .... tak vytvorím pomocný pointer a posúvam na koniec.
    ATOM *p = a;
    while (p->nasl != NULL)
        p = p->nasl;

    p->nasl = ML;
    p = p->nasl;
    p->nasl = NULL;
    p->h = 3;

    // Výpis pomocou pomocného pointera.
    p = a;
    while (p != NULL)
    {
        fprintf(stdout, "%d ", p->h);
        p = p->nasl;
    }
    putchar('\n');

    return 0;
}