// Lexografický strom - program na vkladanie a vyhladávanie slov v slovníku
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (UZOL*)malloc(sizeof(UZOL))
#define MAX ('Z' - 'A')

typedef struct uzol{
    char ss[15];
    struct uzol *pole[MAX]; // Pole ukazovatelov na nasledujúce uzly
}UZOL;

// Základné funkcie
void ini(UZOL **ls);
void vloz(UZOL *lt,char as[],char ss[]);
void hladaj(UZOL *lt, char as[], char ss[]);

int main(int argc, char *argv[]){
    UZOL *lst;
    ini(&lst);

    vloz(lst, "DOG", "PES");
    vloz(lst, "DO", "ROBIT");
    vloz(lst, "DOOR", "DVERE");
    vloz(lst, "GOLD", "ZLATO");

    char ret[15], ret2[15];

    strcpy(ret, "DOG");
    hladaj(lst, ret , ret2);
    printf("%s -> %s\n", ret, ret2);

    strcpy(ret, "GOLD");
    hladaj(lst, ret , ret2);
    printf("%s -> %s\n", ret, ret2);

    strcpy(ret, "FISH");
    hladaj(lst, ret , ret2);
    printf("%s -> %s\n", ret, ret2);

    return 0;
}
//---------------------------------------
void ini(UZOL **ls){    // Inicializácia stromu
    *ls = ML;
    strcpy((*ls)->ss, "");  // Na prvom uzle pridám prázdny reťazec
    for(int i = 0; i < MAX; i++)    // Inicializácia všetkých ukazovateľov na NULL
        (*ls)->pole[i] = NULL;
}
void vloz(UZOL *lt,char as[],char ss[]){    // Vloženie slova do stromu
    for(int i = 0; i < strlen(as); i++){    // Prechádzam všetky znaky slova
        if(lt->pole[as[i] - 'A'] == NULL){  // Ak je ukazovateľ NULL, alokujem nový uzol
            lt->pole[as[i] - 'A'] = ML;     // A priradím ho do poľa ukazovateľov na nasledujúce uzly, as[i] - 'A' -> 'A' - 'A' == 0, 'B' - 'A' == 1, atď.
            lt = lt->pole[as[i] - 'A'];
            strcpy(lt->ss, "none");
            for(int j = 0; j < MAX; j++)    // Ostávajúce ukazovatele priradím NULL
                lt->pole[j] = NULL;
        }else{    // Ak ukazovateľ nie je NULL, prejdem na nasledujúci uzol
            lt = lt->pole[as[i] - 'A'];
        }
    }
    strcpy(lt->ss, ss); // Na poslednom uzle priradím slovo
}
void hladaj(UZOL *lt, char as[], char ss[]){    // Hľadanie slova v strome
    int i = 0, chyba = 0;
    while(i < strlen(as) && !chyba){    // Prechádzam všetky znaky slova, ak narazím na NULL ukazovateľ, slovo nie je v slovníku (chyba = 1)
        if(lt->pole[as[i] - 'A'] != NULL)
            lt = lt->pole[as[i] - 'A'];
        else
            chyba = 1;
        i++;
    }
    if(!chyba && strcmp(lt->ss, "none") != 0)   // Ak som prešiel všetky znaky a slovo nie je "none" a nenašla sa chyba, priradím slovo do ss
        strcpy(ss, lt->ss);
    else{
        fprintf(stderr, "Slovo %s nie je v slovniku.\n", as);   // Ak sa slovo nenašlo, vypíšem chybovú hlášku
        strcpy(ss, "???");
    }
}
