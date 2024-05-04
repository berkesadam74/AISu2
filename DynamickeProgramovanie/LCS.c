// Najdlhší spoločný podreťazec
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50  // Maximálna dľžka reťazca

char a[MAX] = "BDCABA", b[MAX] = "ABCBDAB", x[MAX + 1] = " ", y[MAX + 1] = " "; // Reťazce, ktoré porovnávame + pomocné reťazce
int **tabulka; // Tabuľka, ktorá obsahuje hodnoty pre porovnávanie

void ini(int ***t, int _x, int _y);
void vystup(int **t, int _x, int _y);
int max(int a, int b);
void lcs(int **t, int _x, int _y, char *x, char *y);
char* lcs_string(int **t, int _x, int _y, char *x, char *y);

int main(int argc, char *argv[]){
    int i, j;
    strcat(x, a); // Spojenie pomocného reťazca s reťazcom a aby sme mohli pracovať s indexom 1
    strcat(y, b);   // Spojenie pomocného reťazca s reťazcom b aby sme mohli pracovať s indexom 1

    int _x = strlen(x); // Dľžka reťazca x
    int _y = strlen(y); // Dľžka reťazca y
    ini(&tabulka, _x, _y);  // Inicializácia tabuľky

    lcs(tabulka, _x, _y, x, y); // Vytvorenie tabuľky s hodnotami po porovnaní reťazcov
    vystup(tabulka, _x, _y);    // Výpis tabuľky

    printf("Najdlhsi spolocny retazec sa sklada zo %d znakov.\n", tabulka[_x - 1][_y - 1]);

    char *retazec = (char*)malloc(sizeof(char) * tabulka[_x - 1][_y - 1]);  // Alokovanie pamäte pre najdlhší spoločný reťazec
    if(retazec == NULL){    // Kontrola chyby pri alokácii
        fprintf(stderr, "Chyba pri alokacii.\n");
        exit(1);
    }

    retazec = lcs_string(tabulka, _x, _y, x, y);    // Vytvorenie najdlhšieho spoločného reťazca
    printf("Najdlhsi spolocny retazec je: %s\n", retazec);

    // Uvoľnenie pamäte
    for(i = 0; i < _x; i++)
        free((void*)tabulka[i]);
    free((void*)tabulka);
    tabulka = NULL;
    free((void*)retazec);
    retazec = NULL;

    return 0;
}
//----------------------------------------------

void ini(int ***t, int _x, int _y){ // Inicializácia tabuľky
    int i, j;
    *t = (int**)malloc(sizeof(int*) * _x);  // Alokácia pamäte pre tabuľku pre stľpce
    if(*t == NULL){ // Kontrola chyby pri alokácii
        fprintf(stderr, "Chyba pri alokacii.\n");
        exit(1);
    }
    for(i = 0; i < _x; i++){
        (*t)[i] = (int*)malloc(sizeof(int) * _y); // Alokácia pamäte pre znaky v riadkoch
        if((*t)[i] == NULL){    // Kontrola chyby pri alokácii
            fprintf(stderr, "Chyba pri alokacii.\n");
            exit(1);
        }
    }
}

void vystup(int **t, int _x, int _y){   // Výpis tabuľky
    int i, j;
    printf("   ");  // Prázdny riadok a stľpec
    for(i = 0; i < _x; i++) // Výpis znakov reťazca x
        printf("%3c", x[i]);
    printf("\n");
    for(i = 0; i < _y; i++){    // Výpis tabuľky
        printf("%3c", y[i]);    // Výpis znakov reťazca y
        for(j = 0; j < _x; j++) // Výpis hodnôt v riadkoch
            printf("%3d", t[j][i]);
        printf("\n");
    }
}

int max(int a, int b){  // Funkcia na zistenie maximálnej hodnoty
    return a > b ? a : b;   // Ak je a väčšie ako b, vráti a, inak vráti b
}

void lcs(int **t, int _x, int _y, char *x, char *y){    // Funkcia na vytvorenie tabuľky s hodnotami
    int i, j;
    for(i = 1; i < _x; i++){    // Cyklus prechádzajúci reťazec x
        for(j = 1; j < _y; j++){    // Cyklus prechádzajúci reťazec y
            if(x[i] == y[j])    // Ak sa znaky rovnajú, priradí hodnotu z predchádzajúceho riadku a stľpca + 1
                t[i][j] = t[i - 1][j - 1] + 1;
            else
                t[i][j] = max(t[i - 1][j], t[i][j - 1]);    // Inak priradí maximálnu hodnotu z predchádzajúceho riadku alebo stľpca
        }
    }
}

char* lcs_string(int **t, int _x, int _y, char *x, char *y){    // Funkcia na vytvorenie najdlhšieho spoločného reťazca
    int i = _x - 1, j = _y - 1; // Indexy prechádzajúce reťazce x a y od konca
    int k = t[i][j];    // Dĺžka najdlhšieho spoločného reťazca
    char *retazec = (char*)malloc(sizeof(char) * k);    // Alokácia pamäte pre najdlhší spoločný reťazec
    if(retazec == NULL){    // Kontrola chyby pri alokácii
        fprintf(stderr, "Chyba pri alokacii.\n");
        exit(1);
    }
    while(k > 0){   // Cyklus prechádzajúci tabuľku od konca
        // Ak sa hodnota v tabuľke rovná hodnote v predchádzajúcom riadku a stľpci + 1, tak vieme že znak je súčasťou najdlhšieho spoločného reťazca
        if(tabulka[i][j] == tabulka[i - 1][j - 1] + 1){
            retazec[k - 1] = x[i];  // Priradí znak do reťazca
            i--;
            j--;
            k--;
        }
        else if(tabulka[i][j] == tabulka[i - 1][j]) // Ak prvý if neplatí, tak sa pohybuje po riadku, kontroluje či sa vie pohnút hore v tabuľke
            i--;
        else    // keď sa nevie pohnúť hore tak ide do ľava
            j--;
    }
    return retazec; // vráti reťazec
}
