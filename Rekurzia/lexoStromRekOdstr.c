// Lexograficky usporiadaný strom s rekurzívnym odstraňovaním
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (UZOL*)malloc(sizeof(UZOL))
#define MAX ('Z' - 'A')

typedef struct uzol{
    char ss[15];
    struct uzol *pole[MAX];
}UZOL;

void ini(UZOL **t);
void vloz(UZOL *t, char as[], char ss[]);
void hladaj(UZOL *t, char as[], char ss[]);
void destroy(UZOL **t);

int main(int argc, char *argv[]){
    UZOL *sl;
    ini(&sl);

    vloz(sl, "DOOR", "DVERE");
    vloz(sl, "DOG", "PES");
    vloz(sl, "GOLD", "ZLATO");

    // char ret1[15], ret2[15];
    // strcpy(ret1, "DOG");
    // hladaj(sl, ret1, ret2);
    // printf("%s -> %s\n", ret1, ret2);

    destroy(&sl);

    return 0;
}
//----------------------------------------
void ini(UZOL **t){
    *t = ML;
    strcpy((*t)->ss, "");
    for(int i = 0; i < MAX;i++)
        (*t)->pole[i] = NULL;
}
void vloz(UZOL *t, char as[], char ss[]){
    for(int i = 0; i < strlen(as); i++){
        if(t->pole[as[i] - 'A'] == NULL){
            t->pole[as[i] - 'A'] = ML;
            t = t->pole[as[i] - 'A'];
            strcpy(t->ss, "none");
            for(int j = 0; j < MAX; j++)
                t->pole[j] = NULL;
        }else{
            t = t->pole[as[i] - 'A'];
        }
    }
    strcpy(t->ss, ss);
}
void hladaj(UZOL *t, char as[], char ss[]){
    int i = 0, chyba = 0;
    while(!chyba && i < strlen(as)){
        if(t->pole[as[i] - 'A'] != NULL)
            t = t->pole[as[i] - 'A'];
        else{
            chyba = 1;
            fprintf(stderr, "Slovo sa nenachadza v slovniku.\n");
        }
        i++;
    }
    if(!chyba && strcmp(t->ss, "none") != 0)
        strcpy(ss, t->ss);
    else{
        fprintf(stderr, "Slovo sa nenachadza v slovniku.\n");
        strcpy(ss, "???");
    }
}
void destroy(UZOL **t){ // Rekurzívne odstraňovanie
    if(*t == NULL)  // Ak je uzol prázdny,
        return; // skonči rekurziu
    for(int i = 0; i < MAX; i++)    // Prejdi všetky podstromy
        if((*t)->pole[i] != NULL)   // Ak je podstrom neprázdny,
            destroy(&(*t)->pole[i]);    // rekurzivne ho odstran
    printf("Odoberam uzol so slovom: %s\n", (*t)->ss);  // Vypíš slovo ktoré sa odstraňuje
    free((void*) *t);   // Uvolni pamäť
    *t = NULL;  // Nastav ukazovatel na NULL
}
