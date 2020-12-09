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
    int offset;
    int size;
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
    int cLabel; // condition label
    int lLabel; // loop label
} Func;

typedef struct Classes {
    char* name;
    Var* vars; // the global variables
    int* varsSize;
    Func* funcs; // the functions in the class
    LexCode code;
} Class;

// the queue for the conditions and loops
typedef struct Queue_Object {
    char* type;
    int label;
} QObject;

typedef struct Queue_Conditions_Loops {
    QObject* object;
    int size;
} QueueCL;

#endif //MYLANGUAGE_STRUCTS_H
