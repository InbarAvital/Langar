//
// Created by Inbar
//

#include "Compiler.h"

/**
 * @param class - the class we want to compile
 * @return an assembly string of the class by using the templates.
 */
char* compileClass(Class* class) {
    char* asCode = (char*)malloc(MAX_TEXT * sizeof(char));
    int i;
    for(i = 0; i < class->code.size; i++) {
        // init_var
        if(!strcmp(class->code.lines[i].type, INIT_VAR)) {
            class->vars[*class->varsSize] = initVar(&class->code.lines[i]);
            class->varsSize++;
        }

        // init_func
        if(!strcmp(class->code.lines[i].type, INIT_FUNC)) {
            Func func = initFunc(&class->code.lines[i]);
            func.globalVars = class->vars;
            func.gloVarSize = class->varsSize;
            // getting the block
            func.code = *getBlockOfCode(&class->code, i + 1);
            i = getBlockOfCodeInt(&class->code, i + 1);
            strcat(asCode, compileFunc(&func));
        }
    }
    return asCode;
}

/**
 * @param func - a function
 * @return an assembly of the function by using the templates.
 */
char* compileFunc(Func* func) {
    char* asCode = (char*)malloc(MAX_TEXT * sizeof(char));
    strcat(asCode, func->name);
    strcat(asCode, ":\n"
                   "    push    ebp\n"
                   "    mov     ebp, esp\n");
    int i;
    // first allocate a place in the stack for each var
    for(i = 0; i < func->code.size; i++) {
        // initialize variable
        if(!strcmp(func->code.lines[i].type, INIT_VAR)) {
            // adds the var to this func's var list
            func->localVars[*func->locVarSize] = initVar(&func->code.lines[i]);
            if(*func->locVarSize == 0) {
                func->localVars[*func->locVarSize].offset = 4;
            } else {
                func->localVars[*func->locVarSize] .offset =
                        func->localVars[*func->locVarSize - 1].offset + 4;
            }
            *func->locVarSize = *func->locVarSize + 1;
        }
    }
    // now works on the rest of the code
    for(i = 0; i < func->code.size; i++) {
        // initialize variable
        if(!strcmp(func->code.lines[i].type, INIT_VAR)) {
            // we already dealt with it - we skip
        }
        // updates variable
        else if(!strcmp(func->code.lines[i].type, UPDATE_VAR)) {
            strcat(asCode, compileExpression(subLine(&func->code.lines[i], 2,
                    func->code.lines[i].size - 1), func));
            strcat(asCode, updateLocalVarTemplate(getVarOffset(
                    func->code.lines[i].words[0].value,  func)));
        }
    }
    strcat(asCode, "    mov     esp, ebp\n"
                   "    pop     ebp\n"
                   "    ret\n"
                   "\n");
    return asCode;
}

/**
 * Activate the ShuntingYard algorithm on the expression, then
 * calculate the it using assembly.
 *
 * @param expression - an expression
 * @param func - the function the line is in (if it is global, func = null)
 * @return the assembly code calculating the expression.
 */
char* compileExpression(LexLine* expression, Func* func) {
    char* asCode = (char*)malloc(MAX_TEXT * sizeof(char));
    int i;
    LexLine* postfixLine = shuntingYard(expression);
    // calculating the expression
    for(i = 0; i < postfixLine->size; i++) {
        // if it is a number, push it in the stack
        if(!strcmp(postfixLine->words[i].token, NUMBER)) {
            strcat(asCode, "    push    ");
            strcat(asCode, postfixLine->words[i].value);
            strcat(asCode, "\n");
        }
        // if it is an operator
        else if(!strcmp(postfixLine->words[i].token, OPERATOR)){
            // adds
            if(!strcmp(postfixLine->words[i].value, "+")) {
                strcat(asCode, addTemplate());
            }
            // subtract
            else if(!strcmp(postfixLine->words[i].value, "-")) {
                strcat(asCode, subTemplate());
            }
            // multiply
            else if(!strcmp(postfixLine->words[i].value, "*")) {
                strcat(asCode, mulTemplate());
            }
            // divide
            else {
                strcat(asCode, divTemplate());
            }
        }
        // if it is a variable
        else if(!strcmp(postfixLine->words[i].token, STRING)) {
            if(func != NULL) {
                char* offsetStr[WORD_SIZE];
                sprintf(offsetStr, "%d", getVarOffset(postfixLine->words[i].value, func));
                strcat(asCode, "    push    DWORD PTR [ebp - ");
                strcat(asCode, offsetStr);
                strcat(asCode, "]\n");
            } else {
                // it is a global var - I will add this option later.
            }
        }
    }
    return asCode;
}
/**
 * @param line - a function
 * @return an assembly of the function by using the templates.
 */
Var initVar(LexLine* line) {
    Var var;
    var.type = (char*)malloc(TYPE_SIZE * sizeof(char));
    var.name = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(var.type, line->words[0].value);
    strcpy(var.name, line->words[1].value);
    var.offset = 0;
    return var;
}

/**
 * @param line - a line in which a function is being initialized
 * @return a function that was initialized according to the line given.
 */
Func initFunc(LexLine* line) {
    Func func;
    func.name = (char *) malloc(WORD_SIZE * sizeof(char));
    func.returnType = (char *) malloc(TYPE_SIZE * sizeof(char));
    func.args = (Var *) malloc(VAR_AMOUNT * sizeof(Var));
    func.argSize = 0;
    func.localVars = (Var *) malloc(VAR_AMOUNT * sizeof(Var));
    func.globalVars = (Var *) malloc(VAR_AMOUNT * sizeof(Var));
    func.locVarSize = (int *) malloc(sizeof(int));
    *func.locVarSize = 0;
    func.gloVarSize = (int *) malloc(sizeof(int));
    *func.gloVarSize = 0;
    strcpy(func.returnType, line->words[0].value);
    strcpy(func.name, line->words[1].value);
    int i = 3;
    // -------------- need to change (it does not work with arrays and such) --------------
    while(strcmp(line->words[i].value, ")")) {
        if (i != 3) {
            i++;
        }
        func.args[func.argSize].type = (char *) malloc(WORD_SIZE * sizeof(char));
        func.args[func.argSize].name = (char *) malloc(WORD_SIZE * sizeof(char));
        strcpy(func.args[func.argSize].type, line->words[i].value);
        strcpy(func.args[func.argSize].name, line->words[i + 1].value);
        func.argSize++;
        i += 2;
    }
    return func;
}

int getVarOffset(char* name,  Func* func) {
    int i;
    for(i = 0; i < *func->locVarSize; i++) {
        if(!strcmp(func->localVars[i].name, name)) {
            return func->localVars[i].offset;
        }
    }
    return 0;
    // ---------- here I can add a - there is no such var error --------------
}