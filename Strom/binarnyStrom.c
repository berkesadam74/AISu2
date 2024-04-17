// Prekladač morzeových písmien pomocou binárného stromu
// Potrebujeme načítať vstupný súbor(morze.txt), kďe sa nachádza naša abeceda
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (UZOL *)malloc(sizeof(UZOL)) // Skratka na allokáciu uzľa v halde

typedef struct uzol // Pre stromy potrebujeme takýto rekurzívny dátový typ
{
    char c;             // ukladaná hodnota
    struct uzol *L, *P; // Smerníky na nasledujúci uzoľ, bynárny lebo mame iba 2 dalšie z každého jedného
} UZOL;

// Základné funkcie
void ini(UZOL **t);
void vloz(UZOL *t, char mk[5], char lz);
void hladaj(UZOL *t, char mk[], char *lz);

int main(int argc, char *argv[])
{
    UZOL *st;
    ini(&st);
    char ret[5];
    char l;
    FILE *f = fopen("morze.txt", "r");
    while (!feof(f)) // Načítame morzeovú abecedu do nášho stromu
    {
        fscanf(f, "%c %s\n", &l, ret);
        vloz(st, ret, l);
    }
    fclose(f);

    strcpy(ret, "..."); // Hľadáme nás zakódovaný retazec -> S
    hladaj(st, ret, &l);
    printf("%s -> %c\n", ret, l);

    strcpy(ret, "---"); // Hľadáme nás zakódovaný retazec -> O
    hladaj(st, ret, &l);
    printf("%s -> %c\n", ret, l);

    strcpy(ret, "..."); // Hľadáme nás zakódovaný retazec -> S
    hladaj(st, ret, &l);
    printf("%s -> %c\n", ret, l);

    return 0;
}
//-----------------------
void ini(UZOL **t) // Inicializácia binárneho stromu
{
    *t = ML; // Vytvoríme nový uzoľ
    (*t)->c = ' ';
    (*t)->L = (*t)->P = NULL; // Jeho smerníky nastavíme na NULL
}

void vloz(UZOL *t, char mk[5], char lz)
{
    for (int i = 0; i < strlen(mk); i++) // Prechádzame sa po reťazci
    {
        if (mk[i] == '.') // Retazec[i] môže byť '.' alebo '-'
        {
            if (t->L == NULL) // keď to je '.' ideme do lava, keď z aktuálneho uzľa neexistuje uzoľ na lavo, tak vytvoríme
            {
                t->L = ML;
                t = t->L;
                t->L = t->P = NULL;
            }
            else // Keď existuje, tak sa posunieme
            {
                t = t->L;
            }
        }
        else // keď sa tam nachádza '-' tak posúvame sa do pravého uzľa
        {
            if (t->P == NULL) // Keď neexistuje pravý uzoľ z aktuálného smerníka, tak vytvoríme nový uzoľ
            {
                t->P = ML;
                t = t->P;
                t->L = t->P = NULL;
            }
            else // Keď existuje, tak sa posunieme tam
            {
                t = t->P;
            }
        }
    }
    t->c = lz; // Keď prejdeme celý retazec, zapíšeme do aktualného uzľa na smerník c naše písmeno
}

void hladaj(UZOL *t, char mk[], char *lz)
{
    // Pri hladaní tiež sa prechádza cez binárny strom, podľa aktuálného znaku v reťazci
    int chyba = 0;
    int i = 0;
    while (!chyba && i < strlen(mk))
    {
        if (mk[i] == '.') // Keď je aktuálny znak '.' ideme do ľava
        {
            if (t->L != NULL)
                t = t->L;
            else
                chyba = 1; // Keď neexistuje uzoľ do ľava vieme že takáto kombinácia neexistuje, prepíšeme chybu na 0, aby sme skončili while cyklus
        }
        else // Keď tam je '-', tak ideme do prava
        {
            if (t->P != NULL)
                t = t->P;
            else
                chyba = 1; // Keď ten uzoľ neexistuje, vieme že takáto kombinácia neexituje -> chyba = 1
        }
        i++;
    }
    if (!chyba) // Keď nie je chyba, tak zapíšeme ukladaný znak v uzľe do *lz
        *lz = t->c;
    else // Keď máme chybu, vypíšeme chybovú hlášku
    {
        *lz = '@';
        fprintf(stderr, "Tento kod neexistuje.\n");
    }
}