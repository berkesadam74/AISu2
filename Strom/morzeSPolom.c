// Prekladač morzeových písmien pomocou binárného stromu vytvorený s polom
// Potrebujeme načítať vstupný súbor(morze.txt), kďe sa nachádza naša abeceda
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32 // Definujem maximálnu velikosť pola

typedef struct // Vytvoríme štruktúru strom s polom
{
    char pole[MAX];
} STROM;

// Základné funkcie
void ini(STROM *st);
void vloz(STROM *st, char mk[], char z);
void hladaj(STROM st, char mk[], char *z);

int main(int argc, char *argv[])
{
    STROM a;
    ini(&a);
    char mk[5], c;
    FILE *f = fopen("morze.txt", "r");
    while (!feof(f)) //  Načítame morze abecedu do nášho stromu
    {
        fscanf(f, "%c %s\n", &c, mk);
        vloz(&a, mk, c);
    }
    fclose(f);

    // for (int i = 0; i < MAX; i++)
    //     printf("%c ", a.pole[i]);
    // putchar('\n');

    strcpy(mk, "..."); // vyhľadáme aké písmeno je zakódované do morze reťazcu -> S
    hladaj(a, mk, &c);
    printf("%s -> %c\n", mk, c);

    strcpy(mk, "---"); // -> O
    hladaj(a, mk, &c);
    printf("%s -> %c\n", mk, c);

    strcpy(mk, "..."); // -> S
    hladaj(a, mk, &c);
    printf("%s -> %c\n", mk, c);

    return 0;
}
//----------------------------
void ini(STROM *st) // Inicializuje naše pole, nastavý všetky znaky na " ", aby sme tam nemali nič
{
    for (int i = 0; i < MAX; i++)
        st->pole[i] = ' ';
}
void vloz(STROM *st, char mk[], char z)
{
    int i = 0;
    for (int j = 0; j < strlen(mk); j++) // Prejdeme náš retazec
    {
        if (mk[j] == '.') // Keď aktuálny znak v našom reťazci je '.', tak index posúvame o + 1
            i = 2 * i + 1;
        else // Keď aktuálny znak v našom reťazci je '-', tak index posúvame o + 2
            i = 2 * i + 2;
        //               0
        //            /     \               .
        //           1       2
        //          / \    /   \            .
        //         3  4    5     6
        //       / \  /\  /  \   / \        .
        //      7  8 9 10 11 12 13 14
        //              atď...
    }
    st->pole[i] = z; // Zapíšeme písmeno čo je zakódované do morze do pola na index po prejdení reťazca
}
void hladaj(STROM st, char mk[], char *z) // Na vyhľadávanie použijeme ten istý princíp ako pri vložení do binárneho stromu
{
    int i = 0;
    for (int j = 0; j < strlen(mk); j++)
    {
        if (mk[j] == '.')
            i = 2 * i + 1;
        else
            i = 2 * i + 2;
    }
    *z = st.pole[i]; // Zapíšeme do *z naše písmeno z indexu čo je priradené k morze reťazcu
}