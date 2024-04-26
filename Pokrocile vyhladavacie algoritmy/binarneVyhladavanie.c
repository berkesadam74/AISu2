// Binárne vyhľadávanie v poli reťazcov
// Treba vytvoriť súbor vstup.txt, kde na prvom riadku bude počet mien a na ďalších riadkoch budú jednotlivé mená
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vypis(char **pole, int _pole); // Funkcia na výpis pola

int main(int argc, char *argv[]){
    FILE *f = fopen("vstup.txt", "r");  // Otvorenie súboru na čítanie
    int max;
    fscanf(f, "%d\n", &max);    // Načítanie počtu mien

    char **mena;    // Pole reťazcov s menami
    mena = (char**)malloc(sizeof(char*) * max); // Alokácia pamäte pre pole reťazcov
    for(int i = 0; i < max; i++)
        mena[i] = (char*)malloc(sizeof(char) * 10); // Alokácia pamäte pre jednotlivé reťazce

    char ret[10];   // Pomocný reťazec pre načítanie mien
    int j;  // Pomocná premenná pre cyklus
    max = 0;    // Nastavenie počítadla na 0
    while(!feof(f)){    //  Načítanie mien zo súboru
        fscanf(f, "%s\n", ret); //  Načítanie reťazca
        if(max == 0)    //  Ak je počet mien 0, pridáme meno na začiatok poľa
            strcpy(mena[max], ret);
        else{   //  Ak nie, tak ho zaradíme na správne miesto do zoradeného poľa
            j = max - 1;    //  Nastavenie pomocnej premennej na predposledný prvok
            while(j >= 0 && strcmp(ret, mena[j]) < 0){  //  Cyklus na zoradenie poľa
                strcpy(mena[j + 1], mena[j]);   //  Posunutie mena na ďalšie miesto
                j--;    //  Dekrementácia pomocnej premennej
            }
            strcpy(mena[j + 1], ret);   //  Pridanie mena na správne miesto
        }
        max++;  //  Inkrementácia počítadla
    }
    fclose(f);

    vypis(mena, max);

    char kluc[] = "MIKULAS";    // Hľadaný reťazec
    int nasiel = 0, pocet_porovnani = 0, l, p, m;   // Premenné pre binárne vyhľadávanie
    l = 0;  // Nastavenie ľavého okraja
    p = max - 1;    // Nastavenie pravého okraja

    while(!nasiel && l <= p){   // Cyklus na binárne vyhľadávanie
        pocet_porovnani++;  // Inkrementácia počítadla porovnaní
        printf("Hladam medzi meno[%d] %s a meno[%d] %s\n", l, mena[l], p, mena[p]); // Výpis hľadaného intervalu
        m = (l + p) / 2;    // Výpočet stredného indexu
        printf("Stred je meno[%d] %s\n", m, mena[m]);   // Výpis stredného indexu
        if(strcmp(mena[m], kluc) == 0)  // Porovnanie reťazcov, či sú rovnaké hľadané meno a meno na strednom indexe
            nasiel = 1; // Nastavenie nájdeného reťazca
        else if(strcmp(mena[m], kluc) < 0)  // Porovnanie reťazcov, či je hľadané meno menšie ako meno na strednom indexe
            l = m + 1;  // Nastavenie ľavého okraja ak je hľadané meno menšie ako meno na strednom indexe
        else
            p = m - 1;  // Nastavenie pravého okraja ak je hľadané meno väčšie ako meno na strednom indexe
    }

    if(nasiel)  //  Výpis výsledku, či sa hľadaný reťazec nachádza v poli, keď našiel == 1 -> retazec sa našiel
        printf("Meno %s sa nachadza v zozname.\n", kluc);
    else    // Výpis výsledku, či sa hľadaný reťazec nachádza v poli, keď našiel == 0 -> retazec sa nenasiel
        printf("Meno %s sa nenachadza v zozname.\n", kluc);

    return 0;
}
//----------------------------------------
void vypis(char **pole, int _pole){
    for(int i = 0; i < _pole; i++)
        printf("%s\n", pole[i]);
}
