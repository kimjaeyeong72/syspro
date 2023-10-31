#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 100

void readAndSaveText(char saveText[MAX_ROWS][MAX_COLS], int fd, int *totalLines) {
    char buf;
    int row = 0, col = 0;
    *totalLines = 0;

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            saveText[row][col] = '\0';
            (*totalLines)++;
            row++;
            col = 0;
        } else {
            saveText[row][col] = buf;
            col++;
        }

    }
    saveText[row][col] = '\0'; 
}

void printTextArray(char saveText[MAX_ROWS][MAX_COLS], int totalLines, char *option) {
    if (strcmp(option, "*") == 0) {
        for (int i = 0; saveText[i][0] != '\0'; i++) {
            printf("%s\n", saveText[i]);
        }
    } else {
        char *token = strtok(option, ",");
        while (token != NULL) {
            if (strchr(token, '-')) {
                int start, end;
                sscanf(token, "%d-%d", &start, &end);
                for (int i = start - 1; i <= end - 1; i++) {
                    if (i >= 0 && i < totalLines) {
                        printf("%s\n", saveText[i]);
                    }
                }
            } else {
                int line = atoi(token);
                if (line >= 1 && line <= totalLines) {
                    printf("%s\n", saveText[line - 1]);
                }
            }
            token = strtok(NULL, ",");
        }
    }
}

int main() {
    int fd;
    char saveText[MAX_ROWS][MAX_COLS];
    int totalLines = 0;
    char option[50];

    fd = open("test.txt", O_RDONLY);

    readAndSaveText(saveText, fd, &totalLines); 
    close(fd);

    printf("File read success\n");
    printf("Total Line: %d\n", totalLines);
    printf("You can choose 1 ~ 4 Line\n");
    printf("Pls 'Enter' the line to select : ");
    fgets(option, sizeof(option), stdin);
    option[strcspn(option, "\n")] = 0;
    printTextArray(saveText, totalLines, option);

    return 0;
}

