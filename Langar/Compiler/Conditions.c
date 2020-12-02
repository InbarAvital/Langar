//
// Created by Inbar
//

#include "Compiler.h"

/**
 * @param func - the function in which the condition appears
 * @param index - the index of the line in which the condition appears
 * @return - the char of the if statement
 */
char* compileCondition(Func* func, int index) {
    if(strcmp(func->code.lines[index].words[0].value,"else")) {
        char labelStr[WORD_SIZE];
        char* fullLabel = (char*)malloc(sizeof(char) * WORD_SIZE);
        int condAmount = getInsideCondition(func, index);
        char* asCode = (char*)malloc(MAX_TEXT * sizeof(char));
        strcat(asCode, compileExpression(subLine(&func->code.lines[index], 2,
                                                 func->code.lines[index].size -2), func));
        sprintf(labelStr, "%d", func->cLabel + condAmount + 1);
        strcpy(fullLabel, func->name);
        strcat(fullLabel, "_c_");
        strcat(fullLabel, labelStr);
        strcat(asCode, ifStatementTemplate(fullLabel));
        return asCode;
    }
    return "";
}

/**
 * @param func - the function in which the condition appears.
 * @param index - the index of the line in which the condition starts.
 * @return - the number of conditions that appears (not including this one)
 *           until the end of the condition and it's elses.
 */
int getConditionLength(Func* func, int index) {
    int i;
    int counter = 0;
    int lenOfIf = getEndOfBlock(&func->code, index + 1);
    int lenOfElif = 0;
    // counts the if's inside this current if.
    counter += getInsideCondition(func, index);
    // counts the elif/else and the if's inside them
    for(i = lenOfIf + 1; i < func->code.size; i++) {
        if(!strcmp(func->code.lines[i].type, CONDITION) &&
           strcmp(func->code.lines[i].words[0].value, "if")) {
            lenOfElif = getEndOfBlock(&func->code, i + 1);
            counter++;
            counter += getInsideCondition(func, i);
            i = lenOfElif;
        } else {
            break;
        }
    }
    return counter;
}

/**
 * @param func - the function in which the condition appears.
 * @param index - the index of the line in which the condition starts.
 * @return - the number of conditions that appears inside the condition
 *           that starts in index
 */
int getInsideCondition(Func* func, int index) {
    int i;
    int counter = 0;
    int lenOfIf = getEndOfBlock(&func->code, index + 1);
    for(i = index + 2; i <= lenOfIf; i++) {
        if(!strcmp(func->code.lines[i].type,CONDITION)) {
            counter++;
        }
    }
    return counter;
}