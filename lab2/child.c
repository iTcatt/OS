#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* outfile = fopen(argv[1], "w");
    if (outfile == NULL) {
        printf("The file was not opened\n");
        return 1;
    }

    float sum = 0.;
    float number;
    while (read(0, &number, sizeof(float)) > 0) {
        sum += number;
    }
    
    fprintf(outfile, "Sum of numbers: %f\n", sum);
    fclose(outfile);
    printf("Child program finish\n");
    return 0;
}