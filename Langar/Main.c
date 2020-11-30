//
// Created by Inbar
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Organizer/Organizer.h"
#include "Identifier/Identifier.h"
#include "Compiler/Compiler.h"
#include "Shunting-yard/ShuntingYard.h"
#include "Structs.h"

char* openFile(char* fileName);
void printLexered(LexCode* code);
void printShuntingYard(LexCode* code);

// for testing
int main() {
    // gets the code from the text file.
    char* fileName = "myCode.txt";
    char* text = openFile(fileName);

    TokCode* code = tokenize(text);
    LexCode* lexered = lexer(code);
    LexCode* organized = organize(lexered);
    identifyCode(organized);

    Class* class = (Class*)malloc(sizeof(Class));
    class->vars = (Var *) malloc(VAR_AMOUNT * sizeof(Var));
    class->name = (char *) malloc(WORD_SIZE * sizeof(char));
    class->code = copyLexCode(organized)[0];
    class->varsSize = (int *) malloc(sizeof(int));
    *class->varsSize = 0;
    char* assCode = compileClass(class);
    fflush(stdin);
    fflush(stdout);
    //printLexered(organized);
    printf("%s\n", assCode);
}

void printShuntingYard(LexCode* code) {
    int i;
    for(i = 0; i < code->size; i++) {
        shuntingYard(&code->lines[i]);
    }
}

void printLexered(LexCode* code) {
    int i, j;
    for(i = 0; i < code->size; i++) {
        printf("Line %d - %s\n", i+1, code->lines[i].type);
        for(j = 0; j < code->lines[i].size; j++) {
            printf("value: %s type: %s\n", code->lines[i].words[j].value, code->lines[i].words[j].token);
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

