//
// Created by Inbar
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Lexer/Lexer.h"

// for testing
int main() {
    int i, j;
    char* text = "int x = 1;\n"
                 "if(x==1) {\n"
                 "y=x+1\n"
                 "}";
    TokCode* code = tokenize(text);
    LexCode* lexered = lexer(code);
    for(i = 0; i < lexered->size; i++) {
        printf("Line %d:\n", i+1);
        for(j = 0; j < lexered->lines[i].size; j++) {
            printf("value: %s type: %s\n", lexered->lines[i].words[j].value, lexered->lines[i].words[j].token);
        }
    }
}

