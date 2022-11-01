#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

FILE* NAME_FILE;
char* HEX_TOTAL;
int STRINGS_IN_FILE = 0;
int FLAG_EOF = 0;
long STRING_IN_THREAD = 1;
pthread_mutex_t MUTEX;

const int MAX_SIZE_HEX = 40;
const int MAX_SIZE_DEC = 60;
const int MAX_SIZE_BIN = 160;

int char_to_dec(char symbol) {
    if (isdigit(symbol)) {
        return symbol - '0';
    }
    return symbol - 'A' + 10; 
}

char* reverse_hex(char* hex_number) {
    int i = MAX_SIZE_HEX - 2;
    while (hex_number[i] == '0') {
        --i;
    }

    int j;
    char* hex_string = malloc(sizeof(char) * MAX_SIZE_HEX);
    for (i, j = 0; i >= 0; --i, ++j) {
        hex_string[j] = hex_number[i];
    }
    return hex_string;
}

char* hex_to_bin(char* hex_number) {
    char* bin_string = malloc(sizeof(char) * MAX_SIZE_BIN);
    int length = strlen(hex_number);
    int dec_number;
    for (int i = 0, k = 0; i < length; ++i, k += 4) {
        dec_number = char_to_dec(hex_number[i]);
        
        for (int j = 3; j >= 0; --j) {
            bin_string[j + k] = dec_number % 2 + '0';
            dec_number /= 2;
        }
    }
    return bin_string;
}

void dec_multiplication_by_2(int* dec_number) {
    int flag_overflow = 0;
    for (int i = 0; i < MAX_SIZE_DEC; ++i) {
        int digit = dec_number[i] * 2;
        if (flag_overflow == 1) {
            digit += 1;
            flag_overflow = 0;
        }
    
        if (digit >= 10) {
            flag_overflow = 1;
        }

        dec_number[i] = digit % 10;
    }
}

void add_one_to_position(int position, int* dec_array) {
    int increment = dec_array[position] + 1;
    if (increment >= 10) {
        dec_array[position] = increment % 10;
        add_one_to_position(position + 1, dec_array);
    } else {
        dec_array[position] = increment;
    }
}

int* bin_to_dec(char* bin_string) {
    int* dec_number = malloc(sizeof(int) * MAX_SIZE_DEC);
    for (int i = 0; i < MAX_SIZE_DEC; ++i) {
        dec_number[i] = 0;
    }

    for (int i = 0; i < strlen(bin_string); ++i) {
        dec_multiplication_by_2(dec_number);
        if (bin_string[i] == '1') {
            add_one_to_position(0, dec_number);
        }
    }
    return dec_number;
}

void dec_divide_common(int* dec_array, int divider) {
    int remainder = 0;
    for (int i = MAX_SIZE_DEC - 1; i >= 0; --i) {
        int current_number = dec_array[i] + remainder * 10;
        dec_array[i] = current_number / divider;
        remainder = current_number % divider;
    }
    
    if ((divider % 2 == 0 && remainder >= (divider / 2)) || (divider % 2 == 1 && remainder > (divider / 2))) {
        add_one_to_position(0, dec_array);
    }
}

void print_dec(int* dec_number) {
    int i = MAX_SIZE_DEC;
    while(dec_number[i] == 0) {
        --i;
    }
    for (i; i >= 0; --i) {
        printf("%d", dec_number[i]);
    }
    printf("\n");
}

int sum_hexs(int position, int number) {
    int flag_overflow = 0;
    if (number < 10) {
        HEX_TOTAL[position] = number + '0';
    } else if (number > 9 && number < 16) {
        HEX_TOTAL[position] = (number - 10) + 'A';
    } else {
        flag_overflow = 1;
        if (number >= 26) {
            HEX_TOTAL[position] = (number - 16 - 10) + 'A';
        } else {
            HEX_TOTAL[position] = (number - 16) + '0';
        }
    }
    return flag_overflow;
}

void hex_calculator(char* file_string) {
    int lenght = strlen(file_string);
    int flag_overflow = 0;
    for (int i = 0; (i < lenght) || (flag_overflow == 1); ++i) {
        int sum_chars;
        if (flag_overflow) {
            sum_chars = char_to_dec(HEX_TOTAL[i]) + char_to_dec('1');
            flag_overflow = sum_hexs(i, sum_chars);
        } 

        int last_elem = lenght - i - 1;
        if (last_elem >= 0) {
            sum_chars = char_to_dec(HEX_TOTAL[i]) + char_to_dec(file_string[last_elem]);
            if (flag_overflow == 0) {
                flag_overflow = sum_hexs(i, sum_chars);
            } else {
                int overflow = sum_hexs(i, sum_chars);
            }
        }
    }
}

void* routine() {
    if (pthread_mutex_lock(&MUTEX) != 0) {
        perror("Mutex lock failed");
    }
    char* file_string = malloc(sizeof(char) * 32);
    for (int i = 0; i < STRING_IN_THREAD; ++i) {
        if (FLAG_EOF) {
            break;
        }
        if (fscanf(NAME_FILE, "%s\n", file_string) == feof(NAME_FILE)) {
            FLAG_EOF = 1;
        }   
        hex_calculator(file_string);
        ++STRINGS_IN_FILE;
    }
    free(file_string);
    if (pthread_mutex_unlock(&MUTEX) != 0) {
        perror("Mutex unlock failed");
    }
}

int main(int argc, char* argv[]) {
    NAME_FILE = fopen(argv[1], "r");
    if (NAME_FILE == NULL) {
        perror("File was not opened");
        return 1;
    }

    HEX_TOTAL = malloc(sizeof(char) * MAX_SIZE_HEX);
    for (int i = 0; i < MAX_SIZE_HEX; ++i) {
        HEX_TOTAL[i] = '0';
    }

    long amount = strtol(argv[2], NULL, 10);
    STRING_IN_THREAD = strtol(argv[3], NULL, 10);
    if (pthread_mutex_init(&MUTEX, NULL) != 0) {
        perror("Mutex init failed");
    }

    pthread_t threads[amount];
    for (int i = 0; i < amount; i++) {
        if (pthread_create(threads + i, NULL, &routine, NULL) != 0) {
            perror("Failed to create thread");
        }
        printf("Thread %d start\n", i + 1);
    }
    
    for (int i = 0; i < amount; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    if (pthread_mutex_destroy(&MUTEX) != 0) {
        perror("Mutex destroy failed");
    }
    
    
    char* hex_string = reverse_hex(HEX_TOTAL);
    printf("\nTotal in hex: ");
    printf("%s\n", hex_string);

    char* bin_string = hex_to_bin(hex_string);

    int* dec_array = bin_to_dec(bin_string);
    printf("Total in dec: ");
    print_dec(dec_array);

    printf("Number of string %d\n", STRINGS_IN_FILE);

    dec_divide_common(dec_array, STRINGS_IN_FILE);
    printf("Average: ");
    print_dec(dec_array);

    free(bin_string);
    free(dec_array);
    free(hex_string);
    free(HEX_TOTAL);
    return 0;
}
