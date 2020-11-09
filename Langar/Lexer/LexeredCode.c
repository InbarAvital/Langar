//
// Created by Inbar.
//

#include "Lexer.h"

LexCode* copyLexCode(LexCode* source) {
    LexCode* dest = (LexCode*)malloc(sizeof(LexCode));
    int i;
    dest->lines = (LexLine*) malloc(LINE_AMOUNT * sizeof(LexLine));
    for(i = 0; i < source->size; i++) {
        dest->lines[i] = *copyLexLine(&source->lines[i]);
    }
    dest->size = source->size;

    return dest;
}

LexLine* copyLexLine(LexLine* source) {
    LexLine* dest = (LexLine*) malloc(sizeof(LexLine));
    dest->words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexLine));
    int i;
    for(i = 0; i < source->size; i++) {
        dest->words[i] = *copyLexObj(&source->words[i]);
    }
    dest->size = source->size;

    return dest;
}

LexObj* copyLexObj(LexObj* source) {
    LexObj* dest = (LexObj*) malloc(sizeof(LexObj));
    dest->value = (char*) malloc(WORD_SIZE * sizeof(char));
    dest->token = (char*) malloc(WORD_SIZE * sizeof(char));
    strcpy(dest->value, source->value);
    strcpy(dest->token, source->token);

    return dest;
}