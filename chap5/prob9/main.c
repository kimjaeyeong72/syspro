#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

void printFileReverse(FILE *file) {
    char lines[MAX_LINE_LENGTH][MAX_LINE_LENGTH]; 
    int lineCount = 0;

    
    while (fgets(lines[lineCount], MAX_LINE_LENGTH, file) != NULL) {
        lineCount++;
    }

    
    for (int i = lineCount - 1; i >= 0; i--) {
        printf("%s", lines[i]);
    }
}

int main() {
    FILE *file;
    char filename[] = "test.txt"; 

    file = fopen(filename, "r");
    if (file == NULL) {
        return 1;
    }

    printFileReverse(file);

    fclose(file);

    return 0;
}


