// Hashovacie algoritmy pre reťazce, celé čísla a desatinné čísla s rôznymi metódami riešenia kolízií
// Potrebujeme vstupný súbor vstup.txt s hodnotami, ktoré chceme uložiť do hash tabulky
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define M 13    // Veľkosť tabulky - počet prvkov + (počet prvkov * 1/3) => najblizšia prvočiselná hodnota
#define FI 0.6180339887 // Zlatý rez

typedef struct{ // Definícia štruktúry pre prvky tabulky
    char m[20];
    char p[20];
    int v;
    float n;
}RB;

typedef struct atom{    // Definícia štruktúry pre zretazenie
    RB h;
    struct atom *nasl;
}ATOM;

// Hashovacie algoritmy
int hashFloat(float x);
int hashInt1(int x);
int hashInt2(int x);
int hashInt3(int x);
int hashInt4(int x);
int hashString1(char *s);
int hashString2(char *s);
int hashString3(char *s);

// Ostatné funkcie
void vypis(RB *pole[]);

int main(int argc, char **argv){
    // RB *pole[M]; // Pole pre lineárny sondáž a dvojité hashovanie
    ATOM *pole[M];  // Pole pre lineárne zretazenie
    for(int i = 0; i < M; i++)  // Inicializácia pola
        pole[i] = NULL;

    FILE *f = fopen("vstup.txt", "r");  // Otvorenie súboru
    RB x;   // Pomocná premenná pre načítanie hodnôt
    while(!feof(f)){    // Načítanie hodnôt zo súboru
        fscanf(f, "%s %s %d %f\n", x.m, x.p, &x.v, &x.n);   // Načítanie hodnôt do pomocnej premennej

        // ked znikne kolizia, hladam dalsie volne miesto - Lineárny sondáž - vkladanie do hash tabulky
        // int h = hashString1(x.m);    // Výpočet hash hodnoty
        // if(pole[h] == NULL){   // Ak je miesto voľné, vložím hodnotu
        //     pole[h] = (RB*)malloc(sizeof(RB));   // Alokujem pamäť pre nový prvok
        //     (*pole[h]) = x;  // Priradím hodnotu do tabulky
        // }else{   // Ak je miesto obsadené, hľadám ďalšie voľné miesto
        //     int i = (h + 1) % M;  // Výpočet ďalšieho indexu
        //     while(pole[i] != NULL){  // Kým nenájdem voľné miesto
        //         i = (i + 1) % M; // Výpočet ďalšieho indexu
        //     }
        //     pole[i] = (RB*)malloc(sizeof(RB));   // Alokujem pamäť pre nový prvok
        //     (*pole[i]) = x;  // Priradím hodnotu do tabulky
        // }

        //Dvojite hashovanie - vkladanie do hash tabulky
        // int h = hashString1(x.m);    // Výpočet hash hodnoty
        // int krok = hashString2(x.m); // Výpočet kroku
        // if(pole[h] == NULL){  // Ak je miesto voľné, vložím hodnotu
        //     pole[h] = (RB*)malloc(sizeof(RB));       // Alokujem pamäť pre nový prvok
        //     (*pole[h]) = x;  // Priradím hodnotu do tabulky
        // }else{   // Ak je miesto obsadené, hľadám ďalšie voľné miesto
        //     int i = (h + krok) % M;  // Výpočet ďalšieho indexu pomocou kroku (druhý hashovací algoritmus)
        //     while(pole[i] != NULL)   // Kým nenájdem voľné miesto
        //         i = (i + krok) % M;  // Výpočet ďalšieho indexu pomocou kroku (druhý hashovací algoritmus)
        //     pole[i] = (RB*)malloc(sizeof(RB));   // Alokujem pamäť pre nový prvok
        //     (*pole[i]) = x;  // Priradím hodnotu do tabulky
        // }

        // Lineárne zretazenie - vkladanie do hash tabulky
        int h = hashString1(x.m);   // Výpočet hash hodnoty
        if(pole[h] == NULL){    // Ak je miesto voľné, vložím hodnotu
            pole[h] = (ATOM*)malloc(sizeof(ATOM));    // Alokujem pamäť pre nový prvok
            pole[h]->nasl = NULL;      // Nastavím nasledujúci prvok na NULL aby som vedel kde končí zretazenie
            pole[h]->h = x;   // Priradím hodnotu do tabulky
        }else{  // Ak je miesto obsadené, pridám hodnotu na koniec zretazenia
            ATOM *p = pole[h];  // Pomocná premenná pre prechádzanie zretazenia
            while(p->nasl != NULL)  // Kým nenájdem koniec zretazenia
                p = p->nasl;    // Posun na ďalší prvok
            p->nasl = (ATOM*)malloc(sizeof(ATOM));  // Alokujem pamäť pre nový prvok
            p = p->nasl;    // Posun na nový prvok
            p->nasl = NULL; // Nastavím nasledujúci prvok na NULL aby som vedel kde končí zretazenie
            p->h = x;   // Priradím hodnotu do tabulky
        }


    }
    printf("***************************************\n");
    fclose(f);

    // vypis(pole); // Vypísanie tabuľky -> funkcia pre lineárny sondáž a dvojité hashovanie

    // Lineárny sondáž - hľadanie
    // char hodnota[] = "Ruzenka";  // Hľadaná hodnota
    // int h = hashString1(hodnota);    // Výpočet hash hodnoty
    // if(pole[h] == NULL)  // Ak je miesto voľné, hodnota sa v tabulke nenachádza
    //     printf("RB s menom %s sa nenachadza v nasej tabulke.\n", hodnota);
    // else{    // Ak je miesto obsadené, hľadám hodnotu
    //     if(strcmp(hodnota, pole[h]->m) == 0) // Ak sa hodnota nachádza na prvom mieste
    //         printf("Bytost[%d] => %s %s %d %f\n", h, pole[h]->m, pole[h]->p, pole[h]->v, pole[h]->n);    // Vypíšem hodnotu
    //     else{    // Ak sa hodnota nenachádza na prvom mieste, hľadám ďalej
    //         int i = (h + 1) % M;   // Výpočet ďalšieho indexu
    //         while(pole[i] != NULL && i != h && strcmp(hodnota, pole[i]->m) != 0) // Prechádzam našu tabuľku, pokial pole[i] nie je NULL, i nie je rovné h (znamená že som prešiel celú tabuľku a nie je tam ta naša hľadaná hodnota), a hodnota sa nerovná hodnote na indexe i
    //             i = (i + 1) % M;   // Výpočet ďalšieho indexu
    //         if(pole[i] == NULL)  // Ak je pole[i] NULL, hodnota sa v tabulke nenachádza
    //             fprintf(stderr, "RB s menom %s sa nenachadza v nasej tabulke.\n", hodnota);
    //         else if(i == h || strcmp(pole[i]->m, hodnota) != 0)  // Ak i je rovné h alebo hodnota sa nerovná hodnote na indexe i, hodnota sa v tabulke nenachádza
    //             fprintf(stderr, "RB s menom %s sa nenachadza v nasej tabulke.\n", hodnota);
    //         else // Ak sa hodnota nachádza v tabulke
    //             printf("Bytost[%d] => %s %s %d %f\n", i, pole[i]->m, pole[i]->p, pole[i]->v, pole[i]->n);
    //     }
    // }

    // Dvojité hashovanie - hľadanie
    // char hodnota[] = "Cudo";   // Hľadaná hodnota
    // int h = hashString1(hodnota);    // Výpočet hash hodnoty
    // int krok = hashString2(hodnota); // Výpočet kroku (druhá hashovacia funkcia)
    // if(pole[h] == NULL)  // Ak je miesto voľné, hodnota sa v tabulke nenachádza
    //     printf("RB s menom %s sa nenachadza v nasej tabulke.\n", hodnota);
    // else{    // Ak je miesto obsadené, hľadám hodnotu
    //     if(strcmp(hodnota, pole[h]->m) == 0) // Ak sa hodnota nachádza na prvom mieste, vypíšem hodnotu
    //         printf("Bytost[%d] => %s %s %d %f\n", h, pole[h]->m, pole[h]->p, pole[h]->v, pole[h]->n);
    //     else{    // Ak sa hodnota nenachádza na prvom mieste, hľadám ďalej
    //         int i = (h + krok) % M;  // Výpočet ďalšieho indexu
    //         while(pole[i] != NULL && strcmp(pole[i]->m, hodnota) != 0 && i != h) // Prechádzam našu tabuľku, pokial pole[i] nie je NULL, hodnota sa nerovná hodnote na indexe i a i nie je rovné h (znamená že som prešiel celú tabuľku a nie je tam ta naša hľadaná hodnota)
    //             i = (h + krok) % M;  // Výpočet ďalšieho indexu
    //         if(pole[i] == NULL)  // Ak je pole[i] NULL, hodnota sa v tabulke nenachádza
    //             printf("RB s menom %s sa nenachadza v nasej tabulke.\n", hodnota);
    //         else if(i == h)  // Ak i je rovné h, hodnota sa v tabulke nenachádza
    //             printf("RB s menom %s sa nenachadza v nasej tabulke.\n", hodnota);
    //         else // Ak sa hodnota nachádza v tabulke, vypíšem hodnotu
    //             printf("Bytost[%d] => %s %s %d %f\n", i, pole[i]->m, pole[i]->p, pole[i]->v, pole[i]->n);
    //     }
    // }

    // Linearne zretazenie - vypis
    for(int i = 0; i < M; i++){ // Prechádzam celú tabuľku
        if(pole[i] == NULL) // Ak je pole[i] NULL, vypíšem NULL
            printf("Bytost[%d] => NULL\n", i);
        else{   // Ak pole[i] nie je NULL, vypíšem hodnoty
            printf("Bytost[%d] ", i);
            if(pole[i]->nasl != NULL){  // Ak nasledujúci prvok nie je NULL, vypíšem všetky hodnoty
                ATOM *p = pole[i];
                while(p != NULL){
                    printf("=> %s %s %d %f ", p->h.m, p->h.p, p->h.v, p->h.n);
                    p = p->nasl;
                }
            }
            putchar('\n');
        }
    }
    printf("***************************************\n");

    // Linearne zretazenie - vyhladavanie
    char hodnota[] = "Vali";    // Hľadaná hodnota
    int h = hashString1(hodnota);   // Výpočet hash hodnoty
    if(pole[h] == NULL || (strcmp(pole[h]->h.m, hodnota) != 0 && pole[h]->nasl == NULL))    // Ak je pole[h] NULL alebo hodnota sa nerovná hodnote na indexe h a nasledujúci prvok je NULL, hodnota sa v tabulke nenachádza
        printf("RB s menom %s sa nenachadza v nasej tabulke.\n", hodnota);
    else{   // Ak pole[h] nie je NULL alebo hodnota sa rovná hodnote na indexe h alebo nasledujúci prvok nie je NULL, hľadám hodnotu
        if(strcmp(pole[h]->h.m, hodnota) == 0)  // Ak sa hodnota nachádza na indexe h, vypíšem hodnotu
            printf("Bytost[%d] => %s %s %d %f\n", h, pole[h]->h.m, pole[h]->h.p, pole[h]->h.v, pole[h]->h.n);
        else{   // Ak sa hodnota nenachádza na indexe h, hľadám ďalej
            ATOM *p = pole[h];  // Nastavím ukazovateľ na pole[h]
            while(strcmp(p->h.m, hodnota) != 0 && p->nasl != NULL)  // Prechádzam tabuľku, pokial sa hodnota nerovná hodnote na indexe h a nasledujúci prvok nie je NULL
                p = p->nasl;
            if(strcmp(p->h.m, hodnota) == 0)    // Ak sa hodnota nachádza v tabulke, vypíšem hodnotu
                printf("Bytost[%d] => %s %s %d %f\n", h, p->h.m, p->h.p, p->h.v, p->h.n);
            else    // Ak sa hodnota nenachádza v tabulke, vypíšem, že sa nenachádza
                printf("RB s menom %s sa nenachadza v nasej tabulke.\n", hodnota);
        }
    }
    printf("***************************************\n");

    // Lineárny sondáž a dvojite hashovanie - vymazanie pamäte
    // for(int i = 0; i < M; i++){  // Prechádzam celú tabuľku
    //     if(pole[i] != NULL)  // Ak pole[i] nie je NULL, uvoľním pamäť
    //         free((void*)pole[i]);    // Uvoľnenie pamäte
    // }

    // Lineárne zretazenie - vymazanie pamäte
    for(int i = 0; i < M; i++){ // Prechádzam celú tabuľku
        if(pole[i] != NULL){    // Ak pole[i] nie je NULL, uvoľním pamäť
            ATOM *current = pole[i];    // Nastavím ukazovateľ na pole[i]
            ATOM *nasl; // Nastavím ukazovateľ na nasledujúci prvok

            while(current != NULL){ // Prechádzam celý zoznam
                nasl = current->nasl;   // Nastavím ukazovateľ na nasledujúci prvok
                free((void*)current);   // Uvoľním pamäť
                current = nasl; // Nastavím ukazovateľ na nasledujúci prvok
            }
            pole[i] = NULL; // Nastavím pole[i] na NULL
        }
    }

    return 0;
}

//-------------------------------------------------------------------

int hashFloat(float x){ // Hashovacia funkcia pre float
    float min = 0, max = 100;   // Minimálna a maximálna hodnota
    return ceil(((x - min) / (max - min)) * (M - 1));   // Výpočet hash hodnoty => (x - min)/(max -min) = hodnota medzi 0 a 1, * (M -1) = hodnota medzi 0 a M - 1, ceil() = zaokrúhlenie nahor
}

int hashInt1(int x){    // Hashovacia funkcia pre int
    float min = 0, max = 1000;  // Minimálna a maximálna hodnota
    return ceil(((x - min) / (max - min)) * (M - 1));   // Výpočet hash hodnoty => (x - min)/(max -min) = hodnota medzi 0 a 1, * (M -1) = hodnota medzi 0 a M - 1, ceil() = zaokrúhlenie nahor
}

int hashInt2(int x){    // Hashovacia funkcia pre int
    float max = 1000;   // Maximálna hodnota
    int w = ceil(log2(max));    // 1. krok => výpočet log2(max) a zaokrúhlenie nahor => 2^w => najbližšia mocnina dvojky čize pri max = 1000 nám vyjde 1024
    w = pow(2, w);  // Výpočet w => 1024
    return ceil((x / (float)w) * (M - 1));  // Výpočet hash hodnoty => x / w = hodnota medzi 0 a 1, * (M -1) = hodnota medzi 0 a M - 1, ceil() = zaokrúhlenie nahor
}

int hashInt3(int x){    // Hashovacia funkcia pre int
    float pom = x * FI; // Výpočet x * FI, FI = zlatý rez
    pom = pom - (int)pom;   // Výpočet zvyšku po delení, celá čast nás nezaujíma, budeme mať hodnotu medzi 0 a 1
    return ceil(pom * (M - 1)); // Výpočet hash hodnoty => pom * (M - 1) = hodnota medzi 0 a M - 1, ceil() = zaokrúhlenie nahor
}

int hashInt4(int x){    // Hashovacia funkcia pre int
    return x % M;   // Výpočet hash hodnoty => x % M = zvyšok po delení, hodnota medzi 0 a M - 1
}

int hashString1(char *s){   // Hashovacia funkcia pre string => 5 bitov na znak
    // 'A' = 65 0100 0001 'a' = 97 0110 0001
    long long int x;    // Potrebujeme velmi velké číslo, pretože budeme ukladať 5 bitov na znak
    int c;  // Pomocná premenná
    x = s[0] & 31;  // Uložím si prvý znak, & 31 = 0001 1111, získam prvých 5 bitov zo nášho znaku
    for(int i = 1; i < strlen(s); i++){ // Prechádzam všetky znaky
        x = x << 5;   // Posunutie o 5 bitov doľava, aby som mohol pridať ďalší znak
        c = s[i] & 31;  // Uložím si ďalší znak, & 31 = 0001 1111, získam prvých 5 bitov zo nášho znaku
        x = x | c;  // Pridám ďalší znak na miesto kďe som mal nuly po posunutí
    }
    long double pom = x * FI;   // Výpočet x * FI, FI = zlatý rez
    pom = pom - (long long int)pom; // Výpočet zvyšku po delení, celá čast nás nezaujíma, budeme mať hodnotu medzi 0 a 1
    return ceil(pom * (M - 1)); // Výpočet hash hodnoty => pom * (M - 1) = hodnota medzi 0 a M - 1, ceil() = zaokrúhlenie nahor
}

int hashString2(char *s){   // Hashovacia funkcia pre string => použijeme XOR
    int x, c;   // Pomocné premenné
    x = s[0] & 31;  // Uložím si prvý znak, & 31 = 0001 1111, získam prvých 5 bitov zo nášho znaku
    for(int i = 1; i < strlen(s); i++){ // Prechádzam všetky znaky
        c = s[i] & 31;  // Uložím si ďalší znak, & 31 = 0001 1111, získam prvých 5 bitov zo nášho znaku
        x = x ^ c;  // XOR medzi x a c
    }
    float pom = x * FI; // Výpočet x * FI, FI = zlatý rez
    pom = pom - (int)pom;   // Výpočet zvyšku po delení, celá čast nás nezaujíma, budeme mať hodnotu medzi 0 a 1
    return ceil(pom * (M - 1)); // Výpočet hash hodnoty => pom * (M - 1) = hodnota medzi 0 a M - 1, ceil() = zaokrúhlenie nahor
}

int hashString3(char *s){   // Hashovacia funkcia pre string => použijeme XOR + posunutie bitov
    long long int x;    // Potrebujeme velmi velké číslo lebo za každý znak budeme mať o 1 bit viac
    int c;  // Pomocná premenná
    x = s[0] & 31;  // Uložím si prvý znak, & 31 = 0001 1111, získam prvých 5 bitov zo nášho znaku
    for(int i = 1; i < strlen(s); i++){ // Prechádzam všetky znaky
        x <<= 1;    // Posunutie o 1 bit doľava, aby som mohol pridať ďalší znak
        c = s[i] & 31;  // Uložím si ďalší znak, & 31 = 0001 1111, získam prvých 5 bitov zo nášho znaku
        x = x ^ c;  // XOR medzi x a c
    }
    long double pom = x * FI;   // Výpočet x * FI, FI = zlatý rez
    pom = pom - (long long int)pom; // Výpočet zvyšku po delení, celá čast nás nezaujíma, budeme mať hodnotu medzi 0 a 1
    return ceil(pom * (M - 1)); // Výpočet hash hodnoty => pom * (M - 1) = hodnota medzi 0 a M - 1, ceil() = zaokrúhlenie nahor
}

void vypis(RB *pole[]){ // Vypíše všetky bytosti v poli pre lineárny sondáž a dvojité hashovanie
    for(int i = 0; i < M; i++){ // Prechádzam celé pole
        if(pole[i] == NULL) // Ak je bytosť NULL
            printf("Bytost[%d] = NULL\n", i);   // Vypíšem NULL
        else    // Ak nie je NULL
            printf("Bytost[%d] = %s %s %d %f\n", i, pole[i]->m, pole[i]->p, pole[i]->v, pole[i]->n);    // Vypíšem bytosť
    }
    printf("***************************************\n");
}
