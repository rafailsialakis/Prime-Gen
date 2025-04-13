#ifndef primeparallelcyclic_h
#define primeparallelcyclic_h

// Function declarations
int generateprimecyclic(int N);
void* Worker(void* args);        // For block-based parallelism
void* WorkerCyclic(void* args);  // For cyclic-based parallelism

#endif // CHECK_H
