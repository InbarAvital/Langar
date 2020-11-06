//
// Created by Inbar
//

#ifndef MYLANGUAGE_LEXER_H
#define MYLANGUAGE_LEXER_H

#include "../Tokenizer/Tokenizer.h"
#include <ctype.h>

typedef struct LexeredObjects {
    char* value;
    char* token;
    /**
     * Possible Tokens:
     *      state, type, number, sign(+-/*()[]<>!="{};), loop, condition, string
     */
} LexObj;

typedef struct LexeredLines {
    LexObj* words;
    int size;
} LexLine;

typedef struct LexeredCodes {
    LexLine* lines;
    int size;
} LexCode;

LexObj* lexerWord(char* word);
LexLine* lexerLine(TokLine* line);
LexCode* lexer(TokCode* code);

#endif //MYLANGUAGE_LEXER_H