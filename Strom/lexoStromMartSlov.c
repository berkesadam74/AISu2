// Lexografický strom - program na vkladanie a vyhladávanie slov v slovníku
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (UZOL*)malloc(sizeof(UZOL))
#define MAX 4   // A, b, *, 3

typedef struct uzol{
    char ss[15];
    struct uzol *pole[MAX]; // Pole ukazovatelov na nasledujúce uzly
}UZOL ;

// Základné funkcie
int posun(char z);
void ini(UZOL **ls);
void vloz(UZOL *ls, char ms[], char ss[]);
void hladaj(UZOL *ls, char ms[], char ss[]);

int main(int argc, char *argv[]){
    UZOL *lst;
    ini(&lst);

    vloz(lst, "Ab*", "PES");
    vloz(lst, "**", "ROBIT");
    vloz(lst, "*3A", "DVERE");
    vloz(lst, "AbA", "ZLATO");

    char ret1[15], ret2[15];

    strcpy(ret1, "Ab*");
    hladaj(lst, ret1, ret2);
    printf("%s -> %s\n", ret1, ret2);

    strcpy(ret1, "AbA");
    hladaj(lst, ret1, ret2);
    printf("%s -> %s\n", ret1, ret2);

    strcpy(ret1, "***");
    hladaj(lst, ret1, ret2);
    printf("%s -> %s\n", ret1, ret2);

    return 0;
}
//---------------------------------------
int posun(char z){  // Funkcia pre posun v poli
    switch (z){ // Podľa znaku vráti pozíciu v poli
        case 'A': return 0;
        case 'B': return 1;
        case '*': return 2;
        case '3': return 3;
        default: return -1;
    }
}
void ini(UZOL **ls){    // Inicializácia stromu
    *ls = ML;
    strcpy((*ls)->ss, "");  // Priradenie prázdneho reťazca do prvého uzla
    for(int i = 0; i < MAX; i++)    // Inicializácia všetkých ukazovateľov na NULL
        (*ls)->pole[i] = NULL;
}
void vloz(UZOL *ls, char ms[], char ss[]){  // Vloženie slova do stromu
    for(int i = 0 ; i < strlen(ms); i++){   // Prejdenie všetkých znakov slova
        if(ls->pole[posun(ms[i])] == NULL){ // Ak je ukazovateľ NULL vytvorí sa nový uzol
            ls->pole[posun(ms[i])] = ML;
            ls = ls->pole[posun(ms[i])];
            strcpy(ls->ss, "none");
            for(int j = 0; j < MAX; j++)    // Ostatné ukazovatele nastavíme na NULL
                ls->pole[j] = NULL;
        }else{  // Ak ukazovateľ nie je NULL prejde sa na nasledujúci uzol
            ls = ls->pole[posun(ms[i])];
        }
    }
    strcpy(ls->ss, ss);
}
void hladaj(UZOL *ls, char ms[], char ss[]){    // Hľadanie slova v strome
    int i = 0, chyba = 0;
    while(!chyba && i < strlen(ms)){    // Prejdenie všetkých znakov slova
        if(ls->pole[posun(ms[i])] != NULL)  // Ak ukazovateľ nie je NULL prejde sa na nasledujúci uzol
            ls = ls->pole[posun(ms[i])];
        else    // Ak ukazovateľ je NULL slovo nebolo nájdené (chyba = 1)
            chyba = 1;
        i++;
    }
    if(!chyba && strcmp(ls->ss, "none") != 0)   // Ak slovo bolo nájdené a nie je "none" zkopíruje sa do ss
        strcpy(ss, ls->ss);
    else{   // Ak slovo nebolo nájdené alebo je "none" vypíše sa chybová hláška a do ss sa zkopíruje "???"
        fprintf(stderr, "Slovo nebolo najdene\n");
        strcpy(ss, "???");
    }
}
