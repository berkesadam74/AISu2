// Linearne vyhladavanie v poli reťazcov s menami
// Treba vytvoriť súbor vstup.txt, kde na prvom riadku bude počet mien a na ďalších riadkoch budú jednotlivé mená
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vypis(char **pole, int _pole); // Funkcia na výpis pola

int main(int argc, char *argv[]){
    int max;
    FILE *f = fopen("vstup.txt", "r");  // Otvorenie súboru na čítanie
    fscanf(f, "%d\n", &max);    // Načítanie počtu mien
    // printf("V subore je %d mien.\n", max);

    char **mena;    // Pole reťazcov s menami
    mena = (char**)malloc(sizeof(char*) * max); // Alokácia pamäte pre pole reťazcov
    for(int i = 0; i < max; i++)    // Alokácia pamäte pre jednotlivé reťazce
        mena[i] = (char*)malloc(sizeof(char) * 10);

    int i = 0;
    while(!feof(f)){    // Načítanie mien zo súboru
        fscanf(f, "%s\n", mena[i]);
        i++;
    }
    fclose(f);

    int nasiel = 0, pocet_porovnani = 0;
    i = 0;
    char kluc[] = "BARNA";

    while(!nasiel && i < max){  // Hľadanie mena v poli lineárne, prechádzaním od začiatku po koniec -> O(n)
        if(strcmp(mena[i], kluc) == 0)  // Porovnanie reťazcov, ak sa rovnajú, nastavíme nasiel na 1 -> koniec cyklu
            nasiel = 1;
        pocet_porovnani++;  // Počet porovnaní sa zvýši o 1
        i++;    // Posunutie na ďalší prvok
    }
    if(nasiel) // Výpis výsledku, či sa meno nachádza v zozname alebo nie
        printf("Meno %s sa nachadza v zozname.\n", kluc);
    else
        printf("Meno %s sa nenachadza v zozname.\n", kluc);

    return 0;
}
//----------------------------------------
void vypis(char **pole, int _pole){
    for(int i = 0; i < _pole; i++)
        printf("%s\n", pole[i]);
}
