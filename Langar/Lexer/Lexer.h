//
// Created by Inbar
//

#ifndef MYLANGUAGE_LEXER_H
#define MYLANGUAGE_LEXER_H

#include "../Tokenizer/Tokenizer.h"
#include <ctype.h>

#define TYPE_SIZE 20

// defines for lexered objects
#define STATE "state"
#define TYPE "type"
#define NUMBER "number"
#define SIGN "sign"
#define OPERATOR "operator"
#define LOOP "loop"
#define CONDITION "condition"
#define STRING "string"
#define CUT "cut"
#define ASSIGN "assign"
#define BLOCK_START "blockStart"
#define BLOCK_END "blockEnd"
#define AND "and"
#define OR "or"
#define CONDITION_ASSIGN "conditionAssign"

// defines for lexered lines
#define COMMENT "comment"
#define INIT_VAR "initVar"
#define INIT_FUNC "initFunc"
#define UPDATE_VAR "updateVar"
#define BLOCK "block"
#define INIT_CLASS "initClass"
#define RETURN "return"
#define UNKNOWN "unknown"


typedef struct LexeredObjects {
    char* value;
    /**
    * Possible Tokens:
    *      state, type, number, sign(()[]<>!,"'), operator(+-/*),  loop, condition,
    *      string, cut(;), assign(=), blockStart({), blockEnd(}), and(&&), or(||),
    *      conditionAssign(==, !=, <=, >=).
    */
    char* token;
} LexObj;

typedef struct LexeredLines {
    LexObj* words;
    int size;
    /**
    * Possible Types:
    *      initVar, initFunc, updateVar, condition, loop, block({}), initClass, return, comment, unknown.
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
LexLine* subLine(LexLine* line, int start, int end);

#endif //MYLANGUAGE_LEXER_H