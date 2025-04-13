#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../Includes/check.h"

struct tArgsParallel
{
    int*    Primes;
    int     from;
    int     to;
    int     size;
};

void* Worker(void* args);
int generateprimeparallel(int SIZE_T){
    long NUM_CPUS = sysconf(_SC_NPROCESSORS_ONLN);
    int block = SIZE_T / NUM_CPUS;
    struct tArgsParallel Args[NUM_CPUS];
    pthread_t threads[NUM_CPUS];
    size_t size = 0;
    int* Primes;

    for(int i = 0; i < NUM_CPUS; i++){
        Args[i].Primes = (int*) malloc(sizeof(int));
        Args[i].from = block*i;
        Args[i].to = block*(i+1);
        Args[i].size = 0;
    }
    for(int i = 0; i < NUM_CPUS; i++){
        pthread_create(&threads[i], NULL, Worker, (void*) &Args[i]);
    }
    for(int i = 0; i < NUM_CPUS; i++){
        pthread_join(threads[i], NULL);
    }

    for(int i = 0; i < NUM_CPUS; i++){
        size +=  Args[i].size;
    }
    printf("Total primes: %ld\n", size);
    Primes = (int*) malloc(sizeof(int) * size);
    int index = 0;
    for(int i = 0; i < NUM_CPUS; i++){
        for(int j = 0; j < Args[i].size; j++){
            Primes[index] = Args[i].Primes[j];
            //printf("Primes[%d] = %d\n", index, Primes[index]);
            index++;
        }
    }
    free(Primes);
    for(int i = 0; i < NUM_CPUS; i++){
        free(Args[i].Primes);
    }
    return 0;
}

void* Worker(void* args){
    struct tArgsParallel* arguments;
    arguments = (struct tArgsParallel*) args;
    for(int i = arguments->from; i < arguments->to; i++){
        if(check_primality(i)){
            arguments->Primes[arguments->size] = i;
            arguments->Primes = (int*) realloc(arguments->Primes, sizeof(int) * (arguments->size + 2));
            arguments->size++;        
        }
    }
    return (void*) arguments;
}



