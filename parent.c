#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define P_READ 0
#define P_WRITE 1


int main() {
    int file_descriptors[2];
    char file[80];
    char file_name[80];

    if (pipe(file_descriptors) == -1) {
        printf("Pipe was not created\n");
        return 1;
    }

    switch (fork()) {
        case -1: //error
            printf("Error: Fork\n");
            return 2;
        
        case 0: //child
            close(file_descriptors[P_WRITE]);
            read(file_descriptors[P_READ], file_name, sizeof(file_name));
            char* path = "/mnt/d/ВУЗ/second/OS/Labs/lab2/./child";
            
            if (dup2(file_descriptors[P_READ], 0) == - 1) {
                printf("Error: Dup2\n");
                return 3;
            }

            execl(path, path, file_name,  NULL);
            break;

        default: //parent
            close(file_descriptors[P_READ]);
            printf("Enter filename: ");
            scanf("%s", file);
            write(file_descriptors[P_WRITE], file, sizeof(file));
            printf("Enter float numbers: ");
            float number;
            while (scanf("%f", &number)) {
                if ((write(file_descriptors[P_WRITE], &number, sizeof(float))) == -1) {
                    printf("Error: Write to pipe\n");
                    return 4;
                }
            }

            close(file_descriptors[P_WRITE]);
            wait(NULL);
            break;
    }
}