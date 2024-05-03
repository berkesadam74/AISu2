// Robot v blúdisku -> vyhladá cestu z ľavého horného rohu do pravého dolného rohu.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 8   // bludisko bude mat rozmery MAX x MAX
#define PREK (2 * MAX)  // pocet prekazok

int bludisko[MAX][MAX]; // 2D pole pre ukladanie bludiska
int nasiel; // indikuje, ci sme nasli cestu

void generuj();
void vypis();
void hladaj(int x, int y);

int main(int argc, char *argv[]){
    srand(time(NULL));  // inicializacia generatora nahodnych cisel
    generuj();  // vygenerovanie bludiska
    vypis();    // vypis bludiska
    hladaj(0, 0);   // hladanie cesty od indexu 0, 0 -> lavy horny roh

    return 0;
}
//------------------------------------------------------------------------

void generuj(){ // funkcia na generovanie bludiska
    int pr[MAX * MAX], _pr = MAX * MAX - 2; // pomocne pole pre generovanie prekazok

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            bludisko[i][j] = ' ';   // inicializacia bludiska, vsetky policka su prazdne
        }
    }

    for(int i = 1; i < MAX * MAX - 1; i++){
        pr[i] = i;  // naplnenie pomocneho pola
    }

    int poc = 0, k; // pocet prekazok
    while(poc < PREK){  // generovanie prekážok, pokial počet prekážok nepresiahne požadovaný počet
        k = rand() % _pr;   // vyberie sa nahodne policko z pomocneho pola
        bludisko[pr[k] / MAX][pr[k] % MAX] = '#';   // na vybrane policko sa umiestni prekazka
        poc++;  // zvysenie poctu prekazok
        pr[k] = pr[(--_pr)];    // vybrane policko sa vymeni s poslednym polickom v pomocnom poli
    }
    nasiel = 0; // inicializacia premennej nasiel
}

void vypis(){   // funkcia na výpis blúdiska
    printf("*****************\n");
    for(int i = 0; i < MAX; i++){   // stľpce
        putchar('|');
        for(int j = 0; j < MAX; j++){   // riadky
            printf("%c|", bludisko[i][j]);     // výpis jednotlivých znakov v rade
        }
        putchar('\n');  // nový riadok
        // for(int k = 0; k < MAX; k++)
        //     printf("--");
        // putchar('\n');
    }
    putchar('\n');
    getchar();  // čakanie na stlačenie klávesy
}

void hladaj(int x, int y){  // funkcia na hľadanie cesty
    bludisko[x][y] = '.';   // označenie navštíveného políčka
    vypis();    // výpis blúdiska
    if(x == MAX - 1 && y == MAX - 1) {    // ak sme našli cestu alebo sme na konci blúdiska
        nasiel = 1;
        return;
    }
    if(!nasiel && x < MAX && bludisko[x+1][y] == ' ')   // ak sme nenašli cestu a môžeme sa pohnúť dole
        hladaj(x+1,y);  // rekurzívne volanie funkcie hladaj smerom dole
    if(!nasiel && y < MAX && bludisko[x][y+1] == ' ')   // ak sme nenašli cestu a môžeme sa pohnúť doprava
        hladaj(x,y+1);  // rekurzívne volanie funkcie hladaj smerom doprava
    if(!nasiel && x > 0 && bludisko[x-1][y] == ' ')  // ak sme nenašli cestu a môžeme sa pohnúť hore
        hladaj(x-1,y);  // rekurzívne volanie funkcie hladaj smerom hore
    if(!nasiel && y > 0 && bludisko[x][y-1] == ' ') // ak sme nenašli cestu a môžeme sa pohnúť na lavo
        hladaj(x,y-1);  // rekurzívne volanie funkcie hladaj smerom do lava
    if(nasiel)  //  keď sme našli cestu tak sa vráti z rekurzie
        return;
    bludisko[x][y] = ' ';   // keď sa nevieme pohnúť tak sa vráti o jednu pozíciu a skúsi iné cesty
    vypis();
}
