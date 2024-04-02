// Obojsmerný spájaný zoznam bez nárazníkov a bez smerníkov na koniec a začiatok
// Cyklicky spravené, ATOM na konci ukazuje na začiatok
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (ATOM *)malloc(sizeof(ATOM))

typedef int TYP;

typedef struct atom
{
    TYP h;
    struct atom *pred, *nasl;
} ATOM;

// Základné funkcie
void ini(ATOM **z);
int empty(ATOM *z);
void add(ATOM **z, TYP x);
void erase(ATOM **z);
void hodnota(ATOM *z, TYP *x);
void cw(ATOM **z);  // Posúva index v smere dozadu CLOCKWISE
void ccw(ATOM **z); // Posúva index v smere dopredu COUNTER CLOCKWISE
void destroy(ATOM **z);

int main(int argc, char **argv)
{
    char s[] = "retazec";
    int len = strlen(s), p;

    ATOM *a;
    ini(&a);

    for (int i = 0; i < len; i++)
        add(&a, s[i]);

    cw(&a); // Posúvám index na začiatok, keďže je to cyklický spravené o jeden ďalej od konca je začiatok

    for (int i = 0; i < 7; i++)
    {
        hodnota(a, &p);
        printf("%c ", p);
        cw(&a);
    }
    putchar('\n');

    destroy(&a);

    return 0;
}
//-------------------------------
void ini(ATOM **z)
{
    *z = NULL; // Inicializácia zoznamu
}
int empty(ATOM *z)
{
    return z == NULL; // Zoznam je prázdny, keď z ukazuje na NULL
}
void add(ATOM **z, TYP x)
{
    ATOM *tmp = ML;
    tmp->h = x;

    if (empty(*z)) // Keď zoznam je prázdny, vytvorím nový ATOM na indexe, prepojím nasl a pred aby ukazovalo na seba, zoznam bude cyklický, čize konec ukazuje na začiatok
    {
        tmp->nasl = tmp->pred = tmp;
        *z = tmp;
    }
    else // Pridám nový ATOM s hodnotou z X po indexe, nastavím smerníky pred a nasl, prestavím index na nový ATOM
    {
        tmp->nasl = (*z)->nasl;
        tmp->nasl->pred = tmp;
        tmp->pred = *z;
        (*z)->nasl = tmp;
        *z = tmp;
    }
}
void erase(ATOM **z)
{
    if (!empty(*z))
    {
        if ((*z)->nasl == (*z)->pred) // Keď zoznam má jeden ATOM
        {
            free((void *)*z);
            *z = NULL;
        }
        else // Keď zoznam má viacero ATOMov
        {
            ATOM *tmp = *z;
            (*z)->pred->nasl = (*z)->nasl;
            (*z)->nasl->pred = (*z)->pred;
            *z = (*z)->nasl;
            free((void *)tmp);
        }
    }
}
void hodnota(ATOM *z, TYP *x)
{
    if (!empty(z)) // Vrátim hodnotu z indexu do premennej X
        *x = z->h;
}
void cw(ATOM **z)
{
    if (!empty(*z)) // Posúvám index v smere hodinových ručičiek
        *z = (*z)->nasl;
}
void ccw(ATOM **z)
{
    if (!empty(*z)) // Posúvam index v smere proti hodinových ručičiek
        *z = (*z)->pred;
}
void destroy(ATOM **z)
{
    while (!empty(*z)) // Pokial zoznam nie je prázdny, odstránim ATOMy, smerník na zoznam nastavím na NULL
        erase(z);
    *z = NULL;
}
