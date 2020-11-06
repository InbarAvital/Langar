//
// Created by Inbar on 06/11/2020.
//

#ifndef MYLANGUAGE_OBJECTSSTRUCTS_H
#define MYLANGUAGE_OBJECTSSTRUCTS_H
#include "GeneralStructs.h"

typedef struct Variables {
    char* name;
    char* state; // global, local
    char* access; // private, public
    char* type; // int, string, bool, double, float
    char* value; // number, string etc...
} Variable;

typedef struct Functions {
    char* name;
    Variable* vars; // the local variables of the functions
    Code* code; // the actual function written in the language
} Function;
#endif //MYLANGUAGE_OBJECTSSTRUCTS_H
