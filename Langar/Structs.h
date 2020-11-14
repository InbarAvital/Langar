//
// Created by Inbar
//

#ifndef MYLANGUAGE_STRUCTS_H
#define MYLANGUAGE_STRUCTS_H

#include "Lexer/Lexer.h"

#define VAR_AMOUNT 50

typedef struct Variables {
    char* name;
    char* type; // int, string, bool, double, float
} Var;

typedef struct Functions {
    char* name;
    char* returnType;
    Var* args;
    int argSize;
    Var* localVars;
    Var* globalVars;
    int* locVarSize;
    int* gloVarSize;
    LexCode code;
} Func;

typedef struct Classes {
    char* name;
    Var* vars; // the global variables
    int* varsSize;
    Func* funcs; // the functions in the class
    LexCode code;
} Class;

typedef struct VarToOffset {
    Var var;
    int offset;
} VOMap;

typedef struct Compilers {
    char* code; // the assembly code
    VOMap* offset;
} Compiler;

#endif //MYLANGUAGE_STRUCTS_H