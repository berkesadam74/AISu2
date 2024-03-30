// MSD/LSD sort použitím radu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4
#define ML (ATOM *)malloc(sizeof(ATOM))

typedef struct atom
{
    char h[MAX];
    struct atom *nasl;
} ATOM;

typedef struct
{
    ATOM *zac, *kon;
} RAD;

// Základné funkcie
void ini(RAD *);
int empty(RAD);
void push(RAD *, char *x);
void shift(RAD *);
void hodnota(RAD, char *x);
void destroy(RAD *);

int main(int argc, char **argv)
{
    char s[5][MAX] = {"BCA", "CCD", "DDA", "ACD", "BAC"}; // Tieto reťazce budeme sortovať
    char ret[MAX];

    RAD a;
    ini(&a);

    for (int i = 0; i < 5; i++)
        push(&a, s[i]); // Vložím reťazce do radu

    printf("Nezoradene: \n");
    for (int i = 0; i < 5; i++)
        printf("%s ", s[i]);
    printf("\n************************************************\n\n");

    RAD b[MAX]; // Vyrobim 4 rady, lebo máme 4 pismená rôzneho typu
    for (int i = 0; i < MAX; i++)
        ini(&b[i]);

    // Maximálnu dľžku reťazca máme 3, takže budeme triediť tri krát, MSD triedi od zadu, LSD triedi od predu
    for (int i = 2; i >= 0; i--) // Toto je MSD, keby som triedil podla LSD tak for cyklus vyzerá takto => for(int i = 0; i < 3; i++)
    {
        printf("---------------------%d.znak---------------------\n", i + 1);
        while (!empty(a))
        {
            // Vyberiem retazec z radu a pridávam podľa písmena => A je rad[0], B je rad[1], aťd.
            hodnota(a, ret);
            shift(&a);
            push(&b[ret[i] - 'A'], ret); // 'A' - 'A' sa rovná 0, 'B' - 'A' sa rovná 1, aťd. Toto využijeme pri pridávaní do radu podľa písmena.
            printf("Triedim retazec %s podle znaku %c do %d\n", ret, ret[i], ret[i] - 'A');
        }
        for (int i = 0; i < MAX; i++)
        {
            // Zozbieram všetky retazce z pomocných radov do hlavného radu od písmena A po D
            while (!empty(b[i]))
            {
                hodnota(b[i], ret);
                shift(&b[i]);
                push(&a, ret);
            }
        }
    }

    printf("\n************************************************\n");
    printf("Zoradene: \n");

    // Keď mám retazce zoradené, tak po jednom vyberem z hlavného radu a vypíšem ich v poradí
    while (!empty(a))
    {
        hodnota(a, ret);
        shift(&a);
        printf("%s ", ret);
    }
    putchar('\n');

    // Oslobodím pamäť čo som allokoval pre rady
    destroy(&a);
    for (int i = 0; i < MAX; i++)
        destroy(&b[i]);

    return 0;
}
//-----------------------------
void ini(RAD *r)
{
    r->zac = r->kon = NULL;
}
int empty(RAD r)
{
    return r.zac == NULL;
}
void push(RAD *r, char *x)
{
    if (empty(*r))
    {
        r->kon = ML;
        strcpy(r->kon->h, x);
        r->kon->nasl = NULL;
        r->zac = r->kon;
    }
    else
    {
        r->kon->nasl = ML;
        r->kon = r->kon->nasl;
        strcpy(r->kon->h, x);
        r->kon->nasl = NULL;
    }
}
void shift(RAD *r)
{
    if (!empty(*r))
    {
        ATOM *p = r->zac;
        r->zac = r->zac->nasl;
        free((void *)p);
    }
    else
    {
        fprintf(stderr, "Rad je prazdny.\n");
    }
}
void hodnota(RAD r, char *x)
{
    if (!empty(r))
        strcpy(x, r.zac->h);
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
void destroy(RAD *r)
{
    while (!empty(*r))
        shift(r);
    r->zac = r->kon = NULL;
}
