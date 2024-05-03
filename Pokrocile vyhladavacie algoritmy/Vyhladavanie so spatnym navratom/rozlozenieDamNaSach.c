// Rozloženie n dám na n x n šachovnici tak, aby sa žiadne dve dámy neohrozovali.
#include <stdio.h>
#include <stdlib.h>

#define POCET_DAM 8  // Definuje veľkosť šachovnice ako POCET_DAM x POCET_DAM, t.j. počet dám, ktoré umiestňujeme.
#define DIAGONALA ((POCET_DAM * 2) - 1)    // Vypočíta celkový počet diagonál na šachovnici.

int sachovnica[POCET_DAM][POCET_DAM]; // Dvojrozmerné pole predstavujúce šachovnicu.
int stlpec_hrozba[POCET_DAM];  // Pole indikujúce obsadenosť stĺpcov (1 = obsadený).
int diag1_hrozba[DIAGONALA], diag2_hrozba[DIAGONALA];   // Polia indikujúce obsadenosť diagonál.
int pocet_rieseni;  // Počítadlo počtu nájdených riešení.
FILE *riesenie; // Ukazovateľ na súbor pre ukladanie riešení.

void ini();  // Prototyp funkcie pre inicializáciu.
void zapis(); // Prototyp funkcie pre zápis riešenia do súboru.
void hladaj(int riadok); // Prototyp rekurzívnej funkcie na hľadanie riešení.

int main(int argv, char *argc[]){
    ini();  // Inicializácia stavu.
    riesenie = fopen("riesenie.txt", "w");
    if(riesenie == NULL){
        printf("Nepodarilo sa otvorit subor pre zapis rieseni\n");
        return 1;
    }

    hladaj(0);  // Spustenie hľadania riešení.
    fclose(riesenie);

    printf("Pocet rieseni: %d\n", pocet_rieseni);

    return 0;
}
//------------------------------------------------------------------------

void ini(){  // Inicializuje šachovnicu a pomocné polia.
    pocet_rieseni = 0;
    for(int i = 0; i < POCET_DAM; i++){
        stlpec_hrozba[i] = 0;   // Inicializácia hrozieb stĺpcov.
        for(int j = 0; j < POCET_DAM; j++){
            sachovnica[i][j] = '-'; // Vynulovanie šachovnice.
        }
    }
    for(int i = 0; i < DIAGONALA; i++){
        diag1_hrozba[i] = diag2_hrozba[i] = 0;  // Inicializácia hrozieb diagonál.
    }
}

void zapis(){  // Zapisuje aktuálne riešenie do súboru.
    fprintf(riesenie, "Riesenie %d:\n", pocet_rieseni);
    for(int i = 0; i < POCET_DAM; i++){
        for(int j = 0; j < POCET_DAM; j++){
            fprintf(riesenie, "%c ", sachovnica[i][j]);
        }
        fprintf(riesenie, "\n");
    }
    fprintf(riesenie, "\n");
}

void hladaj(int riadok){  // Rekurzívna funkcia na hľadanie riešení umiestnenia dám.
    if(riadok == POCET_DAM){  // Ak sme dosiahli počet riadkov rovný počtu dám, všetky dámy sú správne umiestnené.
        pocet_rieseni++;  // Zvýši počet nájdených riešení.
        zapis();  // Zapisuje kompletné riešenie do súboru.
        return;  // Vráti sa späť do predchádzajúcej úrovne rekurzie.
    }
    for(int stlpce = 0; stlpce < POCET_DAM; stlpce++){  // Skúma všetky stĺpce v aktuálnom riadku.
        // Kontroluje, či súčasný stĺpec a obe diagonály nie sú ohrozené.
        if(!stlpec_hrozba[stlpce] && !diag1_hrozba[stlpce + riadok] && !diag2_hrozba[stlpce - riadok + (POCET_DAM - 1)]){
            sachovnica[riadok][stlpce] = 'D';  // Umiestni dámu na šachovnicu.
            stlpec_hrozba[stlpce] = 1;  // Označí stĺpec ako ohrozený.
            diag1_hrozba[stlpce + riadok] = 1;  // Označí prvú diagonálu ako ohrozenú.
            diag2_hrozba[stlpce - riadok + (POCET_DAM - 1)] = 1;  // Označí druhú diagonálu ako ohrozenú.

            hladaj(riadok + 1);  // Rekurzívne volá funkciu hladaj pre ďalší riadok.

            // Ak rekurzívne volanie vráti riadenie späť, znamená to, že aktuálna cesta nevedie k riešeniu alebo všetky riešenia boli už nájdené.
            sachovnica[riadok][stlpce] = '-';  // Vráti šachovnicu do predchádzajúceho stavu (odstráni dámu).
            stlpec_hrozba[stlpce] = 0;  // Zruší označenie stĺpca ako ohrozeného.
            diag1_hrozba[stlpce + riadok] = 0;  // Zruší označenie prvej diagonály ako ohrozenej.
            diag2_hrozba[stlpce - riadok + (POCET_DAM - 1)] = 0;  // Zruší označenie druhej diagonály ako ohrozenej.
        }
    }
}
