//
// Created by Inbar
//

#ifndef MYLANGUAGE_LEXER_H
#define MYLANGUAGE_LEXER_H

#include "../Tokenizer/Tokenizer.h"
#include <ctype.h>

#define TYPE_SIZE 20
typedef struct LexeredObjects {
    char* value;
    /**
    * Possible Tokens:
    *      state, type, number, n_sign(()[]<>!,"), m_sign(+-/*),  loop, condition,
    *      string, cut(;), assign(=), start_block({), end_block(}).
    */
    char* token;
} LexObj;

typedef struct LexeredLines {
    LexObj* words;
    int size;
    /**
    * Possible Types:
    *      init_var, init_func, update_var, condition, loop, block({}), init_class, return unknown.
    */
    char* type;
} LexLine;

typedef struct LexeredCodes {
    LexLine* lines;
    int size;
} LexCode;

LexObj* lexerWord(char* word);
LexLine* lexerLine(TokLine* line);
LexCode* lexer(TokCode* code);

// help functions of LexCode
LexCode* copyLexCode(LexCode* source);
LexLine* copyLexLine(LexLine* source);
LexObj* copyLexObj(LexObj* source);
LexCode* getBlockOfCode(LexCode* code, int index);
int getBlockOfCodeInt(LexCode* code, int index);

#endif //MYLANGUAGE_LEXER_H