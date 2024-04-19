// Binárny strom na preklad z morzeovky do znakov + rekurzívne odstránenie
// Treba načítať súbor morze.txt, ktorý obsahuje našu abecedu
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (UZOL*)malloc(sizeof(UZOL))

typedef struct uzol{
    char s;
    struct uzol *l, *p;
}UZOL;

void ini(UZOL **t);
void vloz(UZOL *t, char mk[5], char lz);
void hladaj(UZOL *t, char mk[], char *lz);
void destroy(UZOL **t);

int main(int argc, char *argv[]){
    UZOL *strom;
    ini(&strom);
    char mk[5], lz;

    FILE *f = fopen("morze.txt", "r");
    while(!feof(f)){
        fscanf(f, "%c %s\n", &lz, mk);
        vloz(strom, mk, lz);
    }
    fclose(f);

    // strcpy(mk, "...");
    // hladaj(strom, mk, &lz);
    // printf("%s -> %c\n", mk, lz);

    destroy(&strom);

    return 0;
}
//----------------------------------------
void ini(UZOL **t){
    *t = ML;
    (*t)->s = ' ';
    (*t)->l = (*t)->p = NULL;
}
void vloz(UZOL *t, char mk[5], char lz){
    for(int i = 0; i < strlen(mk); i++){
        if(mk[i] == '.'){
            if(t->l == NULL){
                t->l = ML;
                t = t->l;
                t->l = t->p = NULL;
            }else{
                t = t->l;
            }
        }else{
            if(t->p == NULL){
                t->p = ML;
                t = t->p;
                t->l = t->p = NULL;
            }else{
                t = t->p;
            }
        }
    }
    t->s = lz;
}
void hladaj(UZOL *t, char mk[], char *lz){
    int i = 0, chyba = 0;
    while(!chyba && i < strlen(mk)){
        if(mk[i] == '.'){
            if(t->l == NULL)
                chyba = 1;
            else
                t = t->l;
        }else{
            if(t->p == NULL)
                chyba = 1;
            else
                t = t->p;
        }
        i++;
    }
    if(!chyba)
        *lz = t->s;
    else{
        *lz = '#';
        printf("Tento kod neexistuje\n");
    }
}
void destroy(UZOL **t){ // rekurzívne odstránenie stromu
    if(*t == NULL)  // ak je už strom prázdny, tak skončí rekurziu
        return;
    printf("Som v uzle so znakom: %c\n", (*t)->s);
    if((*t)->l != NULL) // ak ľavý podstrom existuje, tak rekurzívne zavoláme destroy
        destroy(&(*t)->l);
    if((*t)->p != NULL) // ak pravý podstrom existuje, tak rekurzívne zavoláme destroy
        destroy(&(*t)->p);
    printf("Odstranujem uzol so znakom: %c\n", (*t)->s);    // vypíšeme, že práve ktorý uzol odstraňujeme
    free((void*)*t);    // uvoľníme pamäť
    *t = NULL;  // nastavíme ukazovateľ na NULL
}
