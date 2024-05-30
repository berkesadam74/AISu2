// Rad implementovaný s pužitím jednorozmerného pola
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10 // maximalna veľkosť radu

typedef int TYP; // Definovanie typu udajov ukladaných v poli

typedef struct
{
    TYP h[MAX];
    int zac, kon; // Indexy, ktoré sledujú pozície v poli
} RAD;

// Základné funkcie
void ini(RAD *r);
int empty(RAD r);
int full(RAD r);
void push(RAD *r, TYP x);
void shift(RAD *r);
void hodnota(RAD r, TYP *x);

int main(int argc, char **argv)
{
    RAD a;
    ini(&a);

    char s[] = "skuska";
    int p, len = strlen(s);

    for (int i = 0; i < len; i++)
        push(&a, s[i]);

    while (!empty(a))
    {
        hodnota(a, &p);
        printf("%c ", p);
        shift(&a);
    }
    putchar('\n');

    for (int i = 0; i < 10; i++)
    {
        push(&a, i + 1);
    }
    shift(&a);
    push(&a, 11);

    for (int i = 0; i < 10; i++)
    {
        hodnota(a, &p);
        printf("%d ", p);
        shift(&a);
    }
    putchar('\n');

    return 0;
}
//-----------------------------
void ini(RAD *r)
{
    // Nastavím indexy na 0
    r->zac = r->kon = 0;
}
int empty(RAD r)
{
    // Rad je prázdny, keď indexy sa rovnajú
    return r.zac == r.kon;
}
int full(RAD r)
{
    // Rad je plný keď rozdiel medzi indexmi % MAX sa rovna 0, keďže toto je aj vtedy TRUE keď rad je prázdny, musíme skontrolovať či je ozaj prázdny náš rad
    return (r.kon - r.zac) % MAX == 0 && !empty(r);
}
void push(RAD *r, TYP x)
{
    // Keď rad nie je plný tak vložím hodnotu x na index r->kon a posuniem kon o jedno
    if (!full(*r))
    {
        r->h[r->kon % MAX] = x; // preto modulo MAX aby som stále išiel dookola v poli
        r->kon++;
    }
    else
        fprintf(stderr, "Rad je plny.\n");
}
void shift(RAD *r)
{
    // Keď rad nie je prázdny, tak index začiatku posuniem o jedno k smeru na koniec
    if (!empty(*r))
        r->zac = (r->zac + 1) % MAX; // preto modulo MAX aby som stále išiel dookola v poli
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
void hodnota(RAD r, TYP *x)
{
    // Keďže v rade vraciame hodnotu zo začiatku, tak keď nie je prázdny, vrátim hodnotu do x na indexe zac
    if (!empty(r))
        *x = r.h[r.zac];
    else
        fprintf(stderr, "Rad je prazdny.\n");
}
