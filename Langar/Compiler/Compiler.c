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
            i = getEndOfBlock(&class->code, i + 1);
            strcat(asCode, compileFunc(&func));
        }
    }
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
        else if(!strcmp(postfixLine->words[i].token, OPERATOR)) {
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
        // condition assign (==, >=, <=, !=)
        else if(!strcmp(postfixLine->words[i].token, CONDITION_ASSIGN)) {
            // ==
            if(!strcmp(postfixLine->words[i].value, "==")) {
                strcat(asCode, equalsTemplate());
            }
            // >=
            else if(!strcmp(postfixLine->words[i].value, ">=")) {
                strcat(asCode, greaterEqualsTemplate());
            }
            // <=
            else if(!strcmp(postfixLine->words[i].value, "<=")) {
                strcat(asCode, lessEqualsTemplate());
            }
            // !=
            else {
                strcat(asCode, notEqualsTemplate());
            }
        }
        // condition sign (><!)
        else if(!strcmp(postfixLine->words[i].token, CONDITION_SIGN)) {
            // >
            if(!strcmp(postfixLine->words[i].value, ">")) {
                strcat(asCode, greaterTemplate());
            }
            // <
            else if(!strcmp(postfixLine->words[i].value, "<")) {
                strcat(asCode, lessTemplate());
            }
            // !
            else {
                strcat(asCode, notTemplate());
            }
        }
        // or (||)
        else if(!strcmp(postfixLine->words[i].token, OR)) {
            strcat(asCode, orTemplate());
        }
        // and (&&)
        else if(!strcmp(postfixLine->words[i].token, AND)) {
            strcat(asCode, andTemplate());
        }
        // if it is a variable
        else if(!strcmp(postfixLine->words[i].token, STRING)) {
            if(func != NULL) {
                Var* var = getVar(postfixLine->words[i].value, func);
                char* offsetStr[WORD_SIZE];
                sprintf(offsetStr, "%d", var->offset);
                strcat(asCode, "    mov     ebx, ");
                strcat(asCode, getSizePtr(var));
                strcat(asCode, offsetStr);
                strcat(asCode, "]\n");
                strcat(asCode, "    push    ebx\n");
            } else {
                // it is a global var - I will add this option later.
            }
        }
    }
    return asCode;
}

/**
 * @param line - the line in which there is a return line
 * @param func - the function that returns
 * @return returns the assembly line that puts the returned value into eax.
 */
char* compileReturn(LexLine* line, Func* func) {
    // if it is void, exit without doing anything
    if(line->size == 2) {
        if(!strcmp(func->returnType, "void")) {
            return NULL;
        }
        else {
            // ------- can add an error later ----------
        }
    }

    int i;
    char* type = (char*) malloc(sizeof(char) * TYPE_SIZE);
    strcpy(type, "");
    char* returnValue = (char*) malloc(sizeof(char) * WORD_SIZE);
    strcpy(returnValue, "    mov     eax, ");
    // check what is the returned type
    // if it is a number
    if(!strcmp(line->words[1].token, NUMBER)) {
        // if it is float
        for(i = 0; i < strlen(line->words[1].value); i++) {
            if(line->words[1].value[i] == '.') {
                strcpy(type, "float");
            }
        }
        // if it is int
        if(!strcmp(type, "")) {
            strcpy(type, "int");
        }
        strcat(returnValue, line->words[1].value);
    }
    // local variable
    else if(!strcmp(line->words[1].token, STRING)) {
        char* offset[WORD_SIZE];
        Var* var = getVar(line->words[1].value, func);
        strcpy(type, var->type);
        strcat(returnValue, getSizePtr(var));
        sprintf(offset, "%d", var->offset);
        strcat(returnValue, offset);
        strcat(returnValue, "]");
    }
    strcat(returnValue, "\n");
    // confirm the returned type to the function's return type
    // ----------- if there is a problem - we can later add an error ----------
    // else, put it in eax
    if(!strcmp(type, func->returnType)) {
        return returnValue;
    }
    return NULL;
}


/**
 * @param var - the var we want to get the size of
 * @return a string of the size ptr (for example- DWORD PTR[ebp -)
 */
char* getSizePtr(Var* var) {
    if(var->size == 4) {
        return "DWORD PTR[ebp - "; // gits 32 bits
    } else if(var->size == 2) {
        return "WORD PTR[ebp - "; // gets 16 bits
    } else if(var->size == 1) {
        return "BYTE PTR[ebp - "; // gets 8 bits
    }
    return NULL;
}