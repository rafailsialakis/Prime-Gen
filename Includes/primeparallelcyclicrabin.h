#ifndef primeparallelcyclicrabin_h
#define primeparallelcyclicrabin_h

#include <time.h>  // For struct timespec

int miller_rabin(unsigned long long n, int k);
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod);
int check_primality_rabin(int number);
int generateprimerabin(int N);
void* WorkerRabin(void* args);

#endif // CHECK_H
