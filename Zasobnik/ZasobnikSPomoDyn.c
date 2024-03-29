#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 15

// Definujem že aký typ hodnoty bude v zásobníku
typedef int TYP;

// Štruktúra zasobníka s použitím pola.
typedef struct
{
    TYP *h;
    int _z;
} ZASOBNIK;

// Základné funkcie
void ini(ZASOBNIK *z);
int empty(ZASOBNIK z);
void push(ZASOBNIK *z, TYP x);
void pop(ZASOBNIK *z);
void hodnota(ZASOBNIK z, TYP *x);
void destroy(ZASOBNIK *z);

int main(int argc, char **argv)
{
    ZASOBNIK a;
    ini(&a);

    char s[] = "skuska";
    int len = strlen(s), p;

    for (int i = 0; i < len; i++)
        push(&a, s[i]);

    while (!empty(a))
    {
        hodnota(a, &p);
        printf("%c ", p);
        pop(&a);
    }
    putchar('\n');

    return 0;
}
//----------------------------
void ini(ZASOBNIK *z)
{
    // Vytvorím pole dynamicky, nastavím index na 0
    z->h = (TYP *)malloc(sizeof(TYP) * MAX);
    z->_z = 0;
}
int empty(ZASOBNIK z)
{
    // Vtedy je zásobník prázdny, keď index sa rovna nule
    return z._z == 0;
}
void push(ZASOBNIK *z, TYP x)
{
    // Kontrola či zásobník nie je plný.
    if (z->_z < MAX)
    {
        z->h[z->_z] = x; // Pridám hodnotu kde práve ukazuje index
        z->_z++;         // Posuniem index po pridaní hodnoty
    }
    else
        fprintf(stderr, "Zasobnik je plny.\n");
}
void pop(ZASOBNIK *z)
{
    // Kontrola či je zásobník prázdny, keď nie je tak index posuniem dozadu o jeden, čiže vyhodím poslednú pridanú hodnotu
    if (!empty(*z))
        z->_z--;
    else
        fprintf(stderr, "Zasobnik je prazdny.\n");
}
void hodnota(ZASOBNIK z, TYP *x)
{
    // Keď zásobník nie je prázdny, tak zapíšem hodnotu z index - 1 do x (preto index - 1 lebo index ukazuje na dalšiu prázdnu časť v poli)
    if (!empty(z))
        *x = z.h[z._z - 1];
    else
        fprintf(stderr, "Zasobnik je prazdny.\n");
}
void destroy(ZASOBNIK *z)
{
    // Oslobodenie pamäte
    free((void *)z->h);
    z->_z = 0;
}