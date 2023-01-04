#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    FILE* output_file = fopen(argv[1], "w");
    if (output_file == NULL) {
        perror("File was not opened\n");
        return 1;
    }

    int file_descriptor = shm_open(
        "common_memory",
        O_RDWR, 
        S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH
    );

    if (file_descriptor == -1) {
        perror("Error: shared memory in child.\n");
        shm_unlink("common_memory");
        close(file_descriptor);
        return 2;
    }

    struct stat buffer_status;
    fstat(file_descriptor, &buffer_status);
    int buffer_size = buffer_status.st_size;

    float* float_array = mmap(
        NULL, 
        buffer_size, 
        PROT_READ,
        MAP_SHARED, 
        file_descriptor, 
        0
    );
    
    if (float_array == MAP_FAILED) {
        perror("Error: mmap in child process\n");
        shm_unlink("common_memory");
        close(file_descriptor);
        return 2;
    }

    float result_sum = 0;
    for (int array_index = 0; array_index < buffer_size; ++array_index) {
        result_sum += float_array[array_index];
    }
    
    fprintf(output_file, "Sum of float: %.3f\n", result_sum);

    shm_unlink("common_memory");    
    close(file_descriptor);
    fclose(output_file);
    return 0;
}