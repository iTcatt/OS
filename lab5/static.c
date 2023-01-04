#include <stdio.h>

extern float Derivative(float x, float delta_x);
extern int PrimeCount(int left_limit, int right_limit);

int main() {
    int command;
    printf("Select a command:\n1 - derivative cos(x) function\n2 - number of primes\n");
    while (scanf("%d", &command) != EOF) {
        switch (command) {
            case 1: {
                printf("Enter x and deltaX: ");
                float x, delta_x;
                scanf("%f %f", &x, &delta_x);
                printf("Derivative equals %f\n", Derivative(x, delta_x));
                printf("\nSelect a command:\n1 - derivative cos(x) function\n2 - number of primes\n");
                break;
            }

            case 2: {
                printf("Enter natural range [A;B]: ");
                int left_limit, right_limit;
                scanf("%d %d", &left_limit, &right_limit);
                printf("Number of primes: %d\n", PrimeCount(left_limit, right_limit));
                printf("\nSelect a command:\n1 - derivative cos(x) function\n2 - number of primes\n");
                break;
            }

            default: {
                printf("Wrong command! Try again.\n");
                printf("\nSelect a command:\n1 - derivative cos(x) function\n2 - number of primes\n");
            }
                
        }
    }

}
