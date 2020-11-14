//
// Created by Inbar.
//

#include "Lexer.h"

/**
 * @param source
 * @return a copy of source
 */
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

/**
 * @param source
 * @return a copy of source
 */
LexLine* copyLexLine(LexLine* source) {
    LexLine* dest = (LexLine*) malloc(sizeof(LexLine));
    dest->words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexLine));
    if(source->type!=NULL) {
        dest->type = (char*) malloc(TYPE_SIZE * sizeof(char));
        strcpy(dest->type, source->type);
    }
    int i;
    for(i = 0; i < source->size; i++) {
        dest->words[i] = *copyLexObj(&source->words[i]);
    }
    dest->size = source->size;

    return dest;
}

/**
 * @param source
 * @return a copy of source
 */
LexObj* copyLexObj(LexObj* source) {
    LexObj* dest = (LexObj*) malloc(sizeof(LexObj));
    dest->value = (char*) malloc(WORD_SIZE * sizeof(char));
    dest->token = (char*) malloc(WORD_SIZE * sizeof(char));
    strcpy(dest->value, source->value);
    strcpy(dest->token, source->token);

    return dest;
}

/**
 * @param code - the code.
 * @param index - the index of the line when we want to search for an end of a block.
 * @return the block starting at index
 */
LexCode* getBlockOfCode(LexCode* code, int index) {
    int end = getBlockOfCodeInt(code, index);

    // creates a new code, the one we will send back eventually
    LexCode* block = (LexCode*) malloc(sizeof(LexCode*));
    block->lines = (LexLine*) malloc(LINE_AMOUNT * sizeof(LexLine));
    block->size = end - index - 1;
    int i;

    // sets the lines before the indexed line to stay the same
    for(i = index + 1; i < end; i++) {
        block->lines[i - index - 1] = *copyLexLine(&code->lines[i]);
    }
    return block;
}

/**
 * @param code - the code.
 * @param index - the index of the line when we want to search for an end of a block.
 * @return the number of line in which the block ends
 */
int getBlockOfCodeInt(LexCode* code, int index) {
    int count = 1; // will be increased by 1 when { is in code and decreased when } is in code
    int line = index + 1;

    while(count != 0) {
        if(!strcmp(code->lines[line].type, "block")) {
            if(!strcmp(code->lines[line].words[0].value, "{")) {
                count++;
            } else {
                count--;
            }
        }
        line++;
    }

    return line - 1;
}

