#include <time.h>
int check_primality(int number){
    if(number == 0 || number == 1){
        return 0;
    }
    if(number == 2){
        return 1;
    }
    if((number & 1) == 0){
        return 0;
    }
    for(int i = 3; i*i <= number; i+=2){
        if(number % i == 0 && number != i){
            return 0;
        }
    }
    return 1;
}