//
// Created by Inbar on 01/11/2020.
//

#ifndef MYLANGUAGE_TOKENIZER_H
#define MYLANGUAGE_TOKENIZER_H

#include "../General.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TokenizedLines {
    char** words;
    int size;
} TokLine;

typedef struct TokenizedCodes {
    TokLine* lines;
    int size;
} TokCode;

TokLine split(TokLine *line, char ch);
char* substring(char* string, int start, int finish);
TokLine tokenizeLine(TokLine* line, char* toSplit);
TokLine delString(TokLine* line, char* str);
TokCode* tokenize(char* text);

#endif //MYLANGUAGE_TOKENIZER_H
