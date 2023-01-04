#include <math.h>

float Derivative(float x, float delta_x) {
    return (cosf(x + delta_x) - cosf(x)) / delta_x;
}

int PrimeCount(int left_limit, int right_limit) {
    int prime_counter = 0;
    for (int number = left_limit; number <= right_limit; ++number) {
        int flag_prime = 1;
        for (int devider = 2; devider < number; ++devider) {
            if (number % devider == 0) {
                flag_prime = 0;
                break;
            }  
        }
        
        if (flag_prime == 1 && number != 1) {
            ++prime_counter;
        }
    }
    return prime_counter;
}

