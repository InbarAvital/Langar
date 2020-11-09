//
// Created by Inbar
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Organizer/Organizer.h"

char* openFile(char* fileName);

// for testing
int main() {
    int i, j;

    // gets the code from the text file.
    char* fileName = "myCode.txt";
    char* text = openFile(fileName);

    TokCode* code = tokenize(text);
    LexCode* lexered = lexer(code);
    LexCode* organized = organize(lexered);
    for(i = 0; i < organized->size; i++) {
        printf("Line %d:\n", i+1);
        for(j = 0; j < organized->lines[i].size; j++) {
            printf("value: %s type: %s\n", organized->lines[i].words[j].value, organized->lines[i].words[j].token);
        }
    }
}

/**
 * @param fileName - the name of the code file.
 * @return the text from the code file.
 */
char* openFile(char* fileName) {
    char* text = (char*) malloc(MAX_TEXT * sizeof(char));
    char* line = (char*) malloc(WORD_AMOUNT * WORD_SIZE * sizeof(char));
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Could not open file %s",fileName);
        return 1;
    }
    while (fgets(line, WORD_AMOUNT * WORD_SIZE, fp) != NULL)
        strcat(text, line);
    fclose(fp);
    return text;
}

