// Binárny vyhľadávací strom
// Treba vytvoriť súbor vstup.txt, kde na riadkoch budú jednotlivé mená
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (UZOL*)malloc(sizeof(UZOL))  // Makro pre alokáciu pamäte

typedef struct uzol{    // Štruktúra uzol, ktorá obsahuje meno a ukazatele na ľavého a pravého potomka
    char meno[10];
    struct uzol *L, *P;
}UZOL;

// Základné funkcie
void ini(UZOL **st);    // Inicializácia stromu
void vloz(UZOL **st, char x[]); // Vloženie do stromu
void vloz_rekurzivne(UZOL **st, char x[]);  // Vloženie do stromu rekurzívne
int hladaj(UZOL *st, char kluc[]);  // Hľadanie v strome
int hladaj_rekurzivne(UZOL *st, char kluc[]);   // Hľadanie v strome rekurzívne

int main(int argc, char *argv[]){
    UZOL *strom;    // Inicializácia stromu
    ini(&strom);
    char ret[10];   // Pomocná premená pre načítanie mena

    FILE *f = fopen("vstup.txt", "r");  // Otvorenie súboru
    while(!feof(f)){    // Načítanie mena zo súboru a vloženie do stromu
        fscanf(f, "%s\n", ret);
        // vloz(&strom, ret);   // Vloženie do stromu (iteratívne)
        vloz_rekurzivne(&strom, ret);   // Vloženie do stromu (rekurzívne)
    }
    fclose(f);

    char kluc[] = "MIKULAS";  //  Hľadané meno
    // printf("Meno %s -> %d\n", kluc, hladaj(strom, kluc));    // Hľadanie v strome (iteratívne), ak sa nájde -> 1, ak sa nenájde -> -1
    printf("Meno %s -> %d\n", kluc, hladaj_rekurzivne(strom, kluc));    // Hľadanie v strome (rekurzívne), ak sa nájde -> 1, ak sa nenájde -> -1

    return 0;
}
//------------------------------------------------------------------------
void ini(UZOL **st){    // Inicializácia stromu
    *st = NULL;
}
void vloz(UZOL **st, char x[]){ // Vloženie do stromu (iteratívne)
    if(*st == NULL){    // Ak je strom prázdny, tak vložíme prvý prvok
        *st = ML;
        strcpy((*st)->meno, x);
        (*st)->L = (*st)->P = NULL; // Ľavý a pravý potomok je NULL
    }else{  // Ak strom nie je prázdny, tak hľadáme miesto pre vloženie
        UZOL *p = *st;  // Pomocná premenná pre prechádzanie stromom
        int zapis = 0;  // Premenná pre zápis
        while(!zapis){  // Cyklus pre zápis
            if(strcmp(p->meno , x) < 0){    // Ak je meno menšie ako meno v uzle, tak sa presunieme na ľavého potomka
                if(p->L == NULL){   // Ak je ľavý potomok NULL, tak vložíme meno
                    p->L = ML;
                    p = p->L;
                    strcpy(p->meno, x);
                    p->L = p->P = NULL;
                    zapis = 1;  // Zápis sa vykonal, tak ukončíme cyklus
                }else{  // Ak ľavý potomok nie je NULL, tak sa presunieme na ľavého potomka
                    p = p->L;
                }
            }else{  // Ak je meno väčšie ako meno v uzle, tak sa presunieme na pravého potomka
                if(p->P == NULL){   // Ak je pravý potomok NULL, tak vložíme meno
                    p->P = ML;
                    p = p->P;
                    strcpy(p->meno, x);
                    p->L = p->P = NULL;
                    zapis = 1;  // Zápis sa vykonal, tak ukončíme cyklus
                }else{  // Ak pravý potomok nie je NULL, tak sa presunieme na pravého potomka
                    p = p->P;
                }
            }
        }
    }
}
int hladaj(UZOL *st, char kluc[]){  // Hľadanie v strome (iteratívne)
    while(1){   // Cyklus pre hľadanie, kým nenájdeme alebo nájdeme hľadané meno
        if(strcmp(st->meno, kluc) == 0) // Ak sa nájde hľadané meno, tak vrátime 1
            return 1;
        if(strcmp(st->meno, kluc) < 0){ // Ak je meno menšie ako meno v uzle, tak sa presunieme na ľavého potomka
            if(st->L == NULL)   // Ak je ľavý potomok NULL, tak vrátime -1 -> hľadané meno sa nenašlo
                return -1;
            st = st->L; // Ak ľavý potomok nie je NULL, tak sa presunieme na ľavého potomka
        }else{  // Ak je meno väčšie ako meno v uzle, tak sa presunieme na pravého potomka
            if(st->P == NULL)   // Ak je pravý potomok NULL, tak vrátime -1 -> hľadané meno sa nenašlo
                return -1;
            st = st->P; // Ak pravý potomok nie je NULL, tak sa presunieme na pravého potomka
        }
    }
}
//------------------------------------------------------------------------
void vloz_rekurzivne(UZOL **st, char x[]){  // Vloženie do stromu (rekurzívne)
    if(*st == NULL){    // Ak je strom prázdny, tak vložíme prvý prvok
        *st = ML;
        strcpy((*st)->meno, x);
        (*st)->L = (*st)->P = NULL;
    }else{  // Ak strom nie je prázdny, tak hľadáme miesto pre vloženie
        if(strcmp((*st)->meno, x) < 0)  // Ak je meno menšie ako meno v uzle, tak sa presunieme na ľavého potomka
            vloz_rekurzivne(&(*st)->L, x);  // Rekurzívne volanie funkcie, na ľavého potomka
        else    // Ak je meno väčšie ako meno v uzle, tak sa presunieme na pravého potomka
            vloz_rekurzivne(&(*st)->P, x);  // Rekurzívne volanie funkcie, na pravého potomka
    }
}
int hladaj_rekurzivne(UZOL *st, char kluc[]){   // Hľadanie v strome (rekurzívne)
    if(strcmp(st->meno, kluc) == 0) // Ak sa nájde hľadané meno, tak vrátime 1
        return 1;
    if(strcmp(st->meno, kluc) < 0){ // Ak je meno menšie ako meno v uzle, tak sa presunieme na ľavého potomka
        if(st->L == NULL)   // Ak je ľavý potomok NULL, tak vrátime -1 -> hľadané meno sa nenašlo
            return -1;
        else    // Ak ľavý potomok nie je NULL, tak sa presunieme na ľavého potomka
            return hladaj_rekurzivne(st->L, kluc);  // Rekurzívne volanie funkcie, na ľavého potomka
    }else{  // Ak je meno väčšie ako meno v uzle, tak sa presunieme na pravého potomka
        if(st->P == NULL)   // Ak je pravý potomok NULL, tak vrátime -1 -> hľadané meno sa nenašlo
            return -1;
        else    // Ak pravý potomok nie je NULL, tak sa presunieme na pravého potomka
            return hladaj_rekurzivne(st->P, kluc);  // Rekurzívne volanie funkcie, na pravého potomka
    }
}
