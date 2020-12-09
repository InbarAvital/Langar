//
// Created by Inbar
//

#include "Compiler.h"

/**
 * @param func - a function
 * @return an assembly of the function by using the templates.
 */
char* compileFunc(Func* func) {
    // this queue will get conditions and loops inside to recognize when one is ending
    QueueCL* queueCl = (QueueCL*)malloc(sizeof(QueueCL));
    queueCl->object = (QObject*)malloc(sizeof(QObject) * WORD_AMOUNT);
    queueCl->size = 0;
    // starting writing the code
    char* asCode = (char*)malloc(MAX_TEXT * sizeof(char));
    strcat(asCode, func->name);
    strcat(asCode, ":\n"
                   "    push    ebp\n"
                   "    mov     ebp, esp\n");
    char keepOffset[WORD_SIZE];
    int i;
    // first allocate a place in the stack for each var
    for(i = 0; i < func->code.size; i++) {
        // just in case we have a return before initializing a variable.
        if(!strcmp(func->code.lines[i].type, RETURN)) {
            char* compiledReturn = compileReturn(&func->code.lines[i], func);
            if(compiledReturn == NULL) {
                break;
            }
        }
        // initialize variable
        else if(!strcmp(func->code.lines[i].type, INIT_VAR)) {
            // adds the var to this func's var list
            compileInitVar(func, i);
        }
    }
    // moves esp in case we added variables to the stack.
    if(*func->locVarSize != 0) {
        strcat(asCode,"    sub     esp, ");
        sprintf(keepOffset, "%d", func->localVars[*func->locVarSize - 1].offset);
        strcat(asCode, keepOffset);
        strcat(asCode,"\n");
    }
    // now works on the rest of the code
    for(i = 0; i < func->code.size; i++) {
        // initialize variable
        if(!strcmp(func->code.lines[i].type, INIT_VAR)) {
            // we already dealt with it - we skip
        }
        // updates variable
        else if(!strcmp(func->code.lines[i].type, UPDATE_VAR)) {
            strcat(asCode, compileUpdateLocalVar(func, i));
        }
        // conditions
        else if(!strcmp(func->code.lines[i].type, CONDITION)) {
            queueCl->object[queueCl->size].type = CONDITION;
            queueCl->size++;
            strcat(asCode, compileCondition(func, i));
            i++;
        }
        // return value
        else if(!strcmp(func->code.lines[i].type, RETURN)) {
            char* compiledReturn = compileReturn(&func->code.lines[i], func);
            if(compiledReturn == NULL) {
                break;
            }
            strcat(asCode, compiledReturn);
        }
        // it is a loop
        else if(!strcmp(func->code.lines[i].type, LOOP)) {
            queueCl->object[queueCl->size].type = LOOP;
            queueCl->object[queueCl->size].label = func->lLabel + 1;
            queueCl->size++;
            strcat(asCode, compileLoop(func, i));
            func->lLabel++;
            i++;
        }
        // a block ended
        else if(!strcmp(func->code.lines[i].type, BLOCK) &&
                !strcmp(func->code.lines[i].words[0].token, BLOCK_END)) {
            // if an if statement just ended
            queueCl->size--;
            // if we exit a condition
            if(!strcmp(queueCl->object[queueCl->size].type, CONDITION)) {
                func->cLabel++;
                char label[WORD_SIZE];
                char fullLabel[WORD_SIZE];
                int labelInc = getConditionLength(func, i - 2);
                if(labelInc != 0) {
                    // creating the jmp to end of conditions
                    sprintf(label, "%d", func->cLabel + labelInc);
                    strcpy(fullLabel, func->name);
                    strcat(fullLabel, "_c_");
                    strcat(fullLabel, label);
                    strcat(asCode, "    jmp     ");
                    strcat(asCode, fullLabel);
                    strcat(asCode, "\n");
                }
                // creating the new label
                strcat(asCode, "\n");
                sprintf(label, "%d", func->cLabel);
                strcpy(fullLabel, func->name);
                strcat(fullLabel, "_c_");
                strcat(fullLabel, label);
                strcat(fullLabel, ":\n");
                strcat(asCode, fullLabel);
            }
            // if we exit a loop
            else if(!strcmp(queueCl->object[queueCl->size].type, LOOP)) {
                func->lLabel++;
                char label[WORD_SIZE];
                char fullLabel[WORD_SIZE];
                // creating the jmp to the beginning of the loop
                sprintf(label, "%d", queueCl->object[queueCl->size].label);
                strcpy(fullLabel, func->name);
                strcat(fullLabel, "_l_");
                strcat(fullLabel, label);
                strcat(asCode, "    jmp     ");
                strcat(asCode, fullLabel);
                strcat(asCode, "\n");
                strcat(asCode, "\n");
                // creating the new label
                sprintf(label, "%d", func->lLabel);
                strcpy(fullLabel, func->name);
                strcat(fullLabel, "_l_");
                strcat(fullLabel, label);
                strcat(fullLabel, ":\n");
                strcat(asCode, fullLabel);
            }
        }
    }
    strcat(asCode, "    mov     esp, ebp\n"
                   "    pop     ebp\n"
                   "    ret\n"
                   "\n");
    return asCode;
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
    func.cLabel = 0;
    func.lLabel = 0;
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
