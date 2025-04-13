
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "../Includes/check.h"

struct tArgsCyclic
{
    int*    Primes;
    int     start;
    int     step;
    int     size;
    int     SIZE_T;
};

void* WorkerCyclic(void* args);
int generateprimecyclic(int SIZE_T){
    long NUM_CPUS = sysconf(_SC_NPROCESSORS_ONLN);
    struct tArgsCyclic args[NUM_CPUS];
    pthread_t threads[NUM_CPUS];
    size_t size = 0;
    int* Primes;

    for(int i = 0; i < NUM_CPUS; i++){
        args[i].Primes = (int*) malloc(sizeof(int));
        args[i].start = i;
        args[i].step = NUM_CPUS;
        args[i].size = 0;
        args[i].SIZE_T = SIZE_T;
    }
    for(int i = 0; i < NUM_CPUS; i++){
        pthread_create(&threads[i], NULL, WorkerCyclic, (void*) &args[i]);
    }
    for(int i = 0; i < NUM_CPUS; i++){
        pthread_join(threads[i], NULL);
    }
    for(int i = 0; i < NUM_CPUS; i++){
        size +=  args[i].size;
    }
    printf("Total primes: %ld\n", size);
    Primes = (int*) malloc(sizeof(int) * size);
    int index = 0;
    for(int i = 0; i < NUM_CPUS; i++){
        for(int j = 0; j < args[i].size; j++){
            Primes[index] = args[i].Primes[j];
            //printf("Primes[%d] = %d\n", index, Primes[index]);
            index++;
        }
    }
    free(Primes);
    for(int i = 0; i < NUM_CPUS; i++){
        free(args[i].Primes);
    }
    return 0;
}

void* WorkerCyclic(void* args){
    struct tArgsCyclic* arguments;
    arguments = (struct tArgsCyclic*) args;
    for(int i = arguments->start; i < arguments->SIZE_T; i+=arguments->step){
        if(check_primality(i)){
            arguments->Primes[arguments->size] = i;
            arguments->Primes = (int*) realloc(arguments->Primes, sizeof(int) * (arguments->size + 2));
            arguments->size++;        
        }
    }
    return (void*) arguments;
}



