
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../Includes/primeparallelcyclicrabin.h"

struct tArgsRabin
{
    int*    Primes;
    int     start;
    int     step;
    int     size;
    int     SIZE_T;
};

void* WorkerRabin(void* args);
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod);
int miller_rabin(unsigned long long n, int k);
int generateprimerabin(int SIZE_T){
    long NUM_CPUS = sysconf(_SC_NPROCESSORS_ONLN);
    struct tArgsRabin Args[NUM_CPUS];
    pthread_t threads[NUM_CPUS];
    size_t size = 0;
    int* Primes;

    for(int i = 0; i < NUM_CPUS; i++){
        Args[i].Primes = (int*) malloc(sizeof(int));
        Args[i].start = i;
        Args[i].step = NUM_CPUS;
        Args[i].size = 0;
        Args[i].SIZE_T = SIZE_T;
    }
    for(int i = 0; i < NUM_CPUS; i++){
        pthread_create(&threads[i], NULL, WorkerRabin, (void*) &Args[i]);
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

void* WorkerRabin(void* args){
    struct tArgsRabin* arguments;
    arguments = (struct tArgsRabin*) args;
    for(int i = arguments->start; i < arguments->SIZE_T; i+=arguments->step){
        if(check_primality_rabin(i)){
            arguments->Primes[arguments->size] = i;
            arguments->Primes = (int*) realloc(arguments->Primes, sizeof(int) * (arguments->size + 2));
            arguments->size++;        
        }
    }
    return (void*) arguments;
}

// Function to perform modular exponentiation
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Miller-Rabin primality test
int miller_rabin(unsigned long long n, int k) {
    // Handle small numbers
    if (n <= 1) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0) return 0;

    // Write n - 1 as 2^s * d
    unsigned long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    // Repeat the test k times with different bases
    for (int i = 0; i < k; i++) {
        // Random base a in [2, n-2]
        unsigned long long a = 2 + rand() % (n - 3);
        
        // Compute a^d % n
        unsigned long long x = mod_exp(a, d, n);
        
        if (x == 1 || x == n - 1) continue;

        // Repeat squaring and check if we get n - 1
        int continueLoop = 0;
        for (int r = 1; r < s; r++) {
            x = (x * x) % n;
            if (x == n - 1) {
                continueLoop = 1;
                break;
            }
        }

        if (!continueLoop) return 0; // n is composite
    }

    return 1; // n is probably prime
}


int check_primality_rabin(int number) {
    return miller_rabin(number, 5); // 5 iterations for accuracy (increase for better accuracy)
}
