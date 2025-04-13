#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "unistd.h"
#include "../Includes/check.h"
#include "../Includes/prime.h"
#include "../Includes/primeparallel.h"
#include "../Includes/primeparallelcyclic.h"
#include "../Includes/primeparallelcyclicrabin.h"

struct timespec start,finish;
void banner();
void display_menu();
void start_clock();
void end_clock();
void calculate_time();

int main(){
    banner();
    display_menu();
    calculate_time();
}

void banner(){
    printf("%s\n", "____________________.___   _____      _____  .____    .___________________.___.");
    sleep(1);
    printf("%s\n", "\\______   \\______   \\   | /     \\    /  _  \\ |    |   |   \\__    ___/\\__  |   |");
    sleep(1);
    printf("%s\n", " |     ___/|       _/   |/  \\ /  \\  /  /_\\  \\|    |   |   | |    |    /   |   |");
    sleep(1);
    printf("%s\n", " |    |    |    |   \\   /    Y    \\/    |    \\    |___|   | |    |    \\____   |");
    sleep(1);
    printf("%s\n", " |____|    |____|_  /___\\____|__  /\\____|__  /_______ \\___| |____|    / ______|");
    sleep(1);
    printf("%s\n", "                \\/       \\/       \\/       \\/         \\/     ");
}

void display_menu() {
    int size,choice;
    printf("Enter the size of the range (e.g., 1000000 for primes up to 1 million): ");
    scanf("%d", &size);
    while (1) {
        printf("Prime Number Generation Menu:\n");
        printf("1. Sequential\n");
        printf("2. Parallel\n");
        printf("3. Cyclic\n");
        printf("4. Miller-Rabin\n");
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                start_clock();
                generateprime(size);
                end_clock();
                break;
            case 2:
                start_clock();
                generateprimeparallel(size);
                end_clock();
                break;
            case 3:
                start_clock();
                generateprimecyclic(size);
                end_clock();
                break;
            case 4:
                start_clock();
                generateprimerabin(size);
                end_clock();
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
                continue;
        }
        break;
    }
}

void start_clock(){
    clock_gettime(CLOCK_MONOTONIC, &start);
}

void end_clock(){
    clock_gettime(CLOCK_MONOTONIC, &finish);
}

void calculate_time(){
    double elapsed;
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Time taken %.5lf seconds.\n", elapsed);
}