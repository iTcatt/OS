#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    FILE* input_file = fopen("test.txt", "r");
    if (input_file == NULL) {
        perror("Input file was not opened.\n");
        return 1;
    }

    char ouput_file[100];
    printf("Enter output file: ");
    scanf("%s", ouput_file);
    
    pid_t process_id = fork();
    if (process_id == -1) {
        perror("Error: fork.\n");
        return 1;
    }

    if (process_id > 0) { 
        float file_data;
        float* array_numbers = (float*) calloc (1, sizeof(float));
        int array_size = 0;
        while(!feof(input_file)) {
            fscanf(input_file, "%f", &file_data);
            array_numbers[array_size] = file_data;
            ++array_size;
            array_numbers = (float*) realloc(
                array_numbers,
                array_size * sizeof(float)
            );
        }

        int file_descriptor = shm_open(
            "common_memory", 
            O_RDWR | O_CREAT, 
            S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH
        );
    
        if (file_descriptor == -1) {
            perror("Error: shared memory open in parent process.\n");
            shm_unlink("common_memory");
            close(file_descriptor);
            return 2;
        }

        if (ftruncate(file_descriptor, array_size) == -1) {
            perror("Error: ftruncate.\n");
            return 3;
        }

        float* float_array = mmap(
            NULL, 
            array_size, 
            PROT_WRITE, 
            MAP_SHARED, 
            file_descriptor, 
            0
        );

        if (float_array == MAP_FAILED){
            perror("Error: parent mmap");
            shm_unlink("common_memory");
            close(file_descriptor);
            return 4;
        }

        for (int array_index = 0; array_index < array_size; ++array_index){
            float_array[array_index] = array_numbers[array_index];
        }

        wait(NULL);
        close(file_descriptor);
    } else { 
        char* path = "./child";
        int error_code_execl = execl(path, path, ouput_file, NULL); 
        if (error_code_execl  == -1) {
            perror("Couldn't find programm to execute!\n");
            return 5;
        }
    }
    return 0;
}
