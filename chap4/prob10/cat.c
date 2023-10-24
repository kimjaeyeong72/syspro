#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copyFile(FILE *input, FILE *output, int addLineNumbers) {
    int c;
    int lineNumber = 1;
    int newLine = 1;

    while ((c = getc(input)) != EOF) {
        if (addLineNumbers && newLine) {
            fprintf(output, "%d ", lineNumber);
            newLine = 0;
        }
        fputc(c, output);

        if (c == '\n') {
            lineNumber++;
            newLine = 1;
        }
    }

    if (!newLine) {
        fputc('\n', output);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr,"test\n",argv[0]);
	fprintf(stderr,"test\n",argv[0]);
        return 1;
    }

    int addLineNumbers = 0;
    int fileIndex = 1;

    if (argc > 2 && strcmp(argv[1], "-n") == 0) {
        addLineNumbers = 1;
        fileIndex = 2;
    }

    for (int i = fileIndex; i < argc; i++) {
        FILE *input = fopen(argv[i], "r");
        if (input == NULL) {
            perror("Error opening file");
            return 1;
        }

        copyFile(input, stdout, addLineNumbers);

        fclose(input);
    }

    return 0;
}

