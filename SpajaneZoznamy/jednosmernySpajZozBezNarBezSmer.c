// Jednosmerny spajany zoznam bez nárazníka bez smerníkov na koniec a začiatok
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

// Základné funkcie
void ini(ATOM **z);
int empty(ATOM *z);
void cw(ATOM **z);
void ccw(ATOM **z);
void add(ATOM **z, TYP x);
void erease(ATOM **z);
void hodnota(ATOM *z, TYP *x);
void destroy(ATOM **z);

int main(int argc, char **argv)
{
    char s[] = "pokusny retazec";
    int len = strlen(s), p;

    ATOM *a;
    ini(&a);

    for (int i = 0; i < len; i++)
        add(&a, s[i]);

    while (!empty(a))
    {
        cw(&a);
        hodnota(a, &p);
        erease(&a);
        printf("%c ", p);
    }
    putchar('\n');

    destroy(&a);

    return 0;
}
//--------------------------------
void ini(ATOM **z) // Inicializujem prvý ATOM
{
    *z = NULL;
}
int empty(ATOM *z) // Zoznam je prázdny, keď smerník na ATOM sa rovná NULL
{
    return z == NULL;
}
void add(ATOM **z, TYP x)
{
    if (empty(*z)) // Keď zoznam je prázdny, vytvorím nový ATOM kde ukazuje náš smerník, a z->nasl nastavým na sám seba
    {
        *z = ML;
        (*z)->h = x;
        (*z)->nasl = *z;
    }
    else // Keď zoznam nie je prázdny, tak vytvorím pomocný ATOM, a postupujem ako pri radoch, hodím hodnotu do pomocného ATOMu
         // pomocný ATOM hodím medzi existujucími ATOMy, index posuniem na nový ATOM (*z = p)
    {
        ATOM *p = ML;
        p->h = x;
        p->nasl = (*z)->nasl;
        (*z)->nasl = p;
        *z = p;
    }
}
void erease(ATOM **z)
{
    if (!empty(*z))
    {
        if (*z == (*z)->nasl) // Keď mám iba jeden ATOM, tak (*z)->nasl ukazuje na seba, iba uvolním pamäť na *z, a nastavím *z na NULL (dôležité pri teste či je zoznam prázdny)
        {
            free((void *)*z);
            *z = NULL;
        }
        else
        {
            ATOM *p = *z; // Keď mám viacero ATOMov, tak vytvorím pomocný ATOM, a posúvam ho pokiaľ neukazuje na ATOM pred indexom
                          // Prehodím smerníky nasl, aby vynechal indexovaný ATOM, odstránim z pamäti index a prehodím index na predchádzajúci ATOM, čiže na pomocný ATOM p
            while (p->nasl != *z)
                p = p->nasl;
            p->nasl = (*z)->nasl;
            free((void *)*z);
            *z = p;
        }
    }
    else
        fprintf(stderr, "Zoznam je prazdny.\n");
}
void cw(ATOM **z)
{
    // Posúvám index dopredu
    if (!empty(*z))
        *z = (*z)->nasl;
    else
        fprintf(stderr, "Zoznam je prazdny.\n");
}
void ccw(ATOM **z)
{
    // Posúvám index dozadu
    if (!empty(*z))
    {
        ATOM *p = *z;
        while (p->nasl != *z)
            p = p->nasl;
        *z = p;
    }
    else
        fprintf(stderr, "Zoznam je prazdny.\n");
}
void hodnota(ATOM *z, TYP *x)
{
    // Keď zoznam nie je prázdny, tak vrátim hodnotu čo je práve v ATOMe na indexe
    if (!empty(z))
        *x = z->h;
    else
        fprintf(stderr, "Zoznam je prazdny.\n");
}
void destroy(ATOM **z)
{
    // Vymažem všetky ATOMy z pamäte
    while (!empty(*z))
        erease(z);
}