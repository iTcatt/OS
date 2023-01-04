#include <math.h>

float Derivative(float x, float delta_x) {
    return (cosf(x + delta_x) - cosf(x - delta_x)) / (2 * delta_x);
}

int PrimeCount(int left_limit, int right_limit) {
    int prime_counter = 0;
    int prime_array_size = right_limit + 1;
    int prime_array[prime_array_size];
    for (int i = 0; i < prime_array_size; ++i) 
        prime_array[i] = 0;
    
    prime_array[0] = prime_array[1] = 1;
    for (int i = 2; i * i < prime_array_size; ++i) {
        if (prime_array[i] == 0) {
            for (int k = i * i; k < prime_array_size; k += i)
                prime_array[k] = 1;
        }
    }
    for (int i = left_limit; i <= right_limit; ++i) {
        if (prime_array[i] == 0) {
            ++prime_counter;
        }
    }
    return prime_counter;
}
