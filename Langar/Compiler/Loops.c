//
// Created by Inbar
//

#include "Compiler.h"

/**
 * @param func - the function in which the loop appears
 * @param index - the index of the line in which the loop appears
 * @return - the char of the loop statement
 */
char* compileLoop(Func* func, int index) {
    char labelStr[WORD_SIZE];
    char* firstLabel = (char*)malloc(sizeof(char) * WORD_SIZE);
    char* lastLabel = (char*)malloc(sizeof(char) * WORD_SIZE);
    int condAmount = getInsideLoop(func, index);
    char* asCode = (char*)malloc(MAX_TEXT * sizeof(char));
    // creating the first label
    strcat(asCode, "\n");
    sprintf(labelStr, "%d", func->lLabel + 1);
    strcpy(firstLabel, func->name);
    strcat(firstLabel, "_l_");
    strcat(firstLabel, labelStr);
    strcat(firstLabel, ":\n");
    // creating the last label
    sprintf(labelStr, "%d", func->lLabel  + condAmount + 2);
    strcpy(lastLabel, func->name);
    strcat(lastLabel, "_l_");
    strcat(lastLabel, labelStr);
    strcat(asCode, firstLabel);
    strcat(asCode, compileExpression(subLine(&func->code.lines[index], 2,
            func->code.lines[index].size - 2), func));
    strcat(asCode, ifStatementTemplate(lastLabel));
    return asCode;
}

/**
 * @param func - the function in which the loop appears.
 * @param index - the index of the line in which the loop starts.
 * @return - the number of loops that appears inside the loops
 *           that starts in index
 */
int getInsideLoop(Func* func, int index) {
    int i;
    int counter = 0;
    int lenOfLoop = getEndOfBlock(&func->code, index + 1);
    for(i = index + 2; i <= lenOfLoop; i++) {
        if(!strcmp(func->code.lines[i].type, LOOP)) {
            counter+=2;
        }
    }
    return counter;
}