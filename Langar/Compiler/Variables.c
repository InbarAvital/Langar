//
// Created by Inbar
//

#include "Compiler.h"

/**
 * @param line - a line in which the var is being initialized
 * @return a new var initialized according to the line sent..
 */
Var initVar(LexLine* line) {
    Var var;
    var.type = (char*)malloc(TYPE_SIZE * sizeof(char));
    var.name = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(var.type, line->words[0].value);
    strcpy(var.name, line->words[1].value);
    var.offset = 0;
    var.size = 0;
    // setting the amount of bytes
    if(!strcmp(var.type, "int")) {
        var.size = 4;
    } else if(!strcmp(var.type, "char")) {
        var.size = 1;
    } else if(!strcmp(var.type, "bool")) {
        var.size = 1;
    }
    return var;
}

/**
 * @param name  - the name of the variable.
 * @param func - the function the variable is in.
 * @return the var.
 */
Var* getVar(char* name,  Func* func) {
    int i;
    for(i = 0; i < *func->locVarSize; i++) {
        if(!strcmp(func->localVars[i].name, name)) {
            return &func->localVars[i];
        }
    }
    // ---------- here I can add a - there is no such var error --------------
    return NULL;
}

/**
 * @param func - the function we want to add a var to
 * @param index - the line in which we init a var.
 */
void compileInitVar(Func* func, int index) {
    func->localVars[*func->locVarSize] = initVar(&func->code.lines[index]);
    if(*func->locVarSize == 0) {
        func->localVars[*func->locVarSize].offset = func->localVars[*func->locVarSize].size;
    } else {
        func->localVars[*func->locVarSize].offset =
                func->localVars[*func->locVarSize - 1].offset +
                func->localVars[*func->locVarSize].size;
    }
    *func->locVarSize = *func->locVarSize + 1;
}

/**
 * @param func - the function that contains the var we are updating
 * @param index - the line in which we update the var
 * @return an assembly code of the var update
 */
char* compileUpdateLocalVar(Func* func, int index) {
    char* asCode = (char*)malloc(MAX_TEXT * sizeof(char));
    Var* var = getVar(func->code.lines[index].words[0].value,  func);
    char* sizePtr = getSizePtr(var);
    // if it is an int, calculate the expression and put in the var.
    if(!strcmp(var->type, "int")) {
        strcat(asCode, compileExpression(subLine(&func->code.lines[index], 2,
                                                 func->code.lines[index].size - 1), func));
        strcat(asCode, updateLocalVarFromStackTemplate(var->offset, sizePtr));
    } else if(!strcmp(var->type, "char")) {
        int charValue = (int)(func->code.lines[index].words[3].value[0]);
        strcat(asCode, updateLocalVarFromValueTemplate(var->offset, charValue, sizePtr));
    } else if(!strcmp(var->type, "bool")) {
        int value;
        if(!strcmp(func->code.lines[index].words[2].value, "true") ||
           !strcmp(func->code.lines[index].words[2].value, "1")) {
            value = 1;
        } else if(!strcmp(func->code.lines[index].words[2].value, "false") ||
                  !strcmp(func->code.lines[index].words[2].value, "0")) {
            value = 0;
        } else {
            // ----------------- can later add "incorrect bool assignment" ------------
        }
        strcat(asCode, updateLocalVarFromValueTemplate(var->offset, value, sizePtr));
    }
    return asCode;
}