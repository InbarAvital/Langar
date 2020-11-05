//
// Created by Inbar
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "GeneralStructs.h"
#include "Lexer/Lexer.h"

// for testing
int main() {
    int i, j;
    char* text = "if(x==1) {\ny=x+1\n}";
    struct Code* code = lexer(text);
    for(i = 0; i < code->size; i++) {
        printf("Line %d:\n", i+1);
        for(j = 0; j < code->lines[i].size; j++) {
            printf("%s \n", code->lines[i].words[j]);
        }
    }
}

