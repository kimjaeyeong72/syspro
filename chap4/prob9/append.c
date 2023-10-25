#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE *file1, *file2;
    char c;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s File1 File2\n", argv[0]);
        return 1;
    }

    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "a+");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening files");
        return 2;
    }

    while ((c = fgetc(file1)) != EOF) {
        fputc(c, file2);
    }

    fclose(file1);
    fclose(file2);

    return 0;
}

