#include <stdio.h>
#include <stdlib.h>
#include "../Includes/check.h"


int generateprime(int SIZE_T){
    int index = 0;
    int* primes = (int*) malloc(sizeof(int));
    for(int i = 0; i < SIZE_T; i++){
        if(check_primality(i)){
            primes[index] = i;
            primes = (int*) realloc(primes, sizeof(int) * (index + 2));
            //printf("Prime saved : primes[%d] = %d\n",index, primes[index]);
            index++;
        }
    }
    printf("Total primes: %d\n", index);
    free(primes);
    return 0;
}




