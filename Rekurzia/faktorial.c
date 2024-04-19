// Faktorial čísla n riešený rekurzívne
#include <stdio.h>
#include <stdlib.h>

long int faktorial(int n);

int main(int argc, char *argv[]){
    int n;
    printf("Zadaj n = ");
    scanf("%d", &n);

    printf("%d! = %ld\n", n, faktorial(n));

    return 0;
}
//---------------------------------------------------
long int faktorial(int n){
    if(n == 0)
        return 1;
    else
        return n * faktorial(n-1);
}
