// Program na kontrolu zatvoriek vo vyrazoch pouzitím zásobníka
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ML (ATOM *)malloc(sizeof(ATOM))

typedef int TYP;

typedef struct atom
{
    TYP h;
    struct atom *nasl;
} ATOM;

void ini(ATOM **zas);
int empty(ATOM *zas);
void push(ATOM **zas, TYP x);
void hodnota(ATOM *zas, TYP *x);
void pop(ATOM **zas);
void destroy(ATOM **zas);

void analyza(char *s);

int main(int argc, char **argv)
{
    char s_ok[] = "((())())(())";
    char s_r[] = "()(()))())()";
    char s_l[] = "((()(())()";
    char vyraz[] = "(a + b) * ((a - c) / ((a + 6)";
    analyza(s_ok);
    analyza(s_r);
    analyza(s_l);
    analyza(vyraz);

    return 0;
}

//-------------------------------------
void ini(ATOM **zas)
{
    *zas = ML;
    (*zas)->nasl = NULL;
}
int empty(ATOM *zas)
{
    return zas->nasl == NULL;
}
void push(ATOM **zas, TYP x)
{
    ATOM *p = ML;
    p->h = x;
    p->nasl = *zas;
    *zas = p;
}
void hodnota(ATOM *zas, TYP *x)
{
    if (!empty(zas))
        *x = zas->h;
    else
        fprintf(stderr, "Zasobnik je prazdny.\n");
}
void pop(ATOM **zas)
{
    if (!empty(*zas))
    {
        ATOM *p = *zas;
        *zas = (*zas)->nasl;
        free((void *)p);
    }
    else
        fprintf(stderr, "Zasobnik je prazdny.\n");
}
void destroy(ATOM **zas)
{
    while (!empty(*zas))
        pop(zas);
    free((void *)*zas);
    *zas = NULL;
}
void analyza(char *s)
{
    ATOM *a;
    ini(&a);

    int len = strlen(s), chyba = 0, i = 0;

    while (!chyba && i < len)
    {
        printf("%c", s[i]);
        if (s[i] == '(') // Keď nájde ľavú zátvorku tak prida symbol do zásobnika
            push(&a, '#');
        else if (s[i] == ')') // Keď nájde pravú zátvorku tak dá preč symbol so zásobníka, keď zásobník je prázdny tak prepíse chybu na 1
        {
            if (empty(a))
                chyba = 1;
            else
                pop(&a);
        }
        i++;
    }
    putchar('\n');

    if (chyba) // while mohlo skončit že chyba = 1, znamená že je viac pravých zatvoriek ako lavých
        printf("Chyba lava zatvorka.\n");
    else if (!empty(a)) // mohlo skončiť že i = strlen(s), čo znamená že sme prešli celý výraz bez chyby, ale ked zásobník nie je prázdny, tak vieme že je viac lavých zátvoriek
        printf("Chyba prava zatvorka.\n");
    else // chyba = 0 a zásobník je prázdny, výraz je OK
        printf("Vyraz je OK.\n");

    putchar('\n');
    destroy(&a);
}