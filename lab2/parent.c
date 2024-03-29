#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

const int READ = 0;
const int WRITE = 1;

int main() {
    int file_descriptors[2];
    char file_name[80];

    if (pipe(file_descriptors) == -1) {
        printf("Pipe was not created\n");
        return 1;
    }
    pid_t process_id;
    switch (process_id = fork()) {
        case -1: //error
            printf("Error: Fork\n");
            return 2;
        
        case 0: //child
            close(file_descriptors[WRITE]);
            read(file_descriptors[READ], file_name, strlen(file_name) + 1);
            char* path = "./child";
            
            if (dup2(file_descriptors[READ], 0) == -1) {
                printf("Error: Dup2\n");
                return 3;
            }

            int err = execl(path, path, file_name,  NULL);
            if (err == -1) {
                printf("Error: Execl");
            }
            break;

        default: //parent
            close(file_descriptors[READ]);
            printf("Enter filename: ");
            scanf("%s", file_name);
            write(file_descriptors[WRITE], file_name, strlen(file_name) + 1);
            printf("Enter float numbers: ");
            float number;
            while (scanf("%f", &number) != EOF) {
                if ((write(file_descriptors[WRITE], &number, sizeof(float))) == -1) {
                    printf("Error: Write to pipe\n");
                    return 4;
                }
            }
            close(file_descriptors[WRITE]);
            wait(NULL);
            break;
    }
}