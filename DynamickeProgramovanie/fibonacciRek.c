// Dynamické programovanie -> rozdiel oproti klasickému rekurzii je, že si pamätáme výsledky
#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // Definuje maximálnu veľkosť poľa pre ukladanie výsledkov.

long int fibd[MAX]; // Pole pre ukladanie výsledkov.

long int fib(int n);    // Prototyp rekurzívnej funkcie pre výpočet Fibonacciho čísel.
long int fib_dynamicky(int n);  // Prototyp funkcie pre výpočet Fibonacciho čísel s dynamickým programovaním.

int main(int argc, char *argv[]){
    for(int i = 0; i < MAX; i++)    // Inicializácia poľa pre ukladanie výsledkov.
        fibd[i] = -1;   // Inicializuje všetky prvky poľa na -1.

    for(int i = 0; i <= 50; i++)
        // printf("Fibonacciho cislo pre %d je: %ld\n", i, fib(i)); // Rekurzívne volanie funkcie pre výpočet Fibonacciho čísel -> veľmi pomalé (trvalo cca 2 min 30 sek)
        printf("Fibonnaciho cislo pre %d je: %ld\n", i, fib_dynamicky(i));  // Volanie funkcie pre výpočet Fibonacciho čísel s dynamickým programovaním -> rýchlejšie (trvalo cca 0,3 sek)

    return 0;
}
//------------------------------------------------------------------------
long int fib(int n){
    if(n == 0)
        return 0;
    if(n == 1 || n == 2)
        return 1;
    return fib(n-1) + fib(n - 2);
}

long int fib_dynamicky(int n){   // Funkcia pre výpočet Fibonacciho čísel s dynamickým programovaním
    if(fibd[n] != -1)   // Ak je výsledok pre dané číslo uložený v poli, vráti ho.
        return fibd[n];
    if(n == 0)  // Ak je n rovné 0, uloží do poľa 0 a vráti 0
        fibd[n] = 0;
    else if(n == 1) // Ak je n rovné 1, uloží do poľa 1 a vráti 1
        fibd[n] = 1;
    else    // Ak n nie je 0 ani 1, uloží do poľa súčet dvoch predchádzajúcich čísel a vráti ho.
        fibd[n] = fib_dynamicky(n - 1) + fib_dynamicky(n - 2);
    return fibd[n];
}
