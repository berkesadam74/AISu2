// Fibonacciho postupnost riešená rekurzívne
#include <stdio.h>
#include <stdlib.h>

long int fibonacci(int n);

int main(int argc, char *argv[]){
    int n;
    printf("Zadaj n = ");
    scanf("%d", &n);

    printf("fib(%d) = %ld\n", n, fibonacci(n));

    return 0;
}
//---------------------------------------------------
long int fibonacci(int n){
    if(n == 0)
        return 0;
    else if(n == 1)
        return 1;
    else
        return fibonacci(n-1) + fibonacci(n-2);
}
