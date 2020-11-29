//
// Created by Inbar
//

#include "ShuntingYard.h"

/**
 * This is simply a shunting yard algorithm.
 * @param line - the expression.
 * @return the expression in postfix notation.
 */
LexLine* shuntingYard(LexLine* line) {
    int i;

    // init output queue
    LexLine* outputQueue = (LexLine*)malloc(sizeof(LexCode));
    outputQueue->words = (LexObj*)malloc(sizeof(LexObj) * line->size);
    outputQueue->size = 0;
    outputQueue->type = (char*)malloc(sizeof(char) * TYPE_SIZE);
    strcpy(outputQueue->type, line->type);

    // init operator stack
    LexLine* operatorStack = (LexLine*)malloc(sizeof(LexCode));
    operatorStack->words = (LexObj*)malloc(sizeof(LexObj) * line->size);
    operatorStack->size = 0;

    for(i = 0; i < line->size; i++) {
        // if it is a number, put it in the output stack.
        if(!strcmp(line->words[i].token, NUMBER)) {
            outputQueue->words[outputQueue->size] = *copyLexObj(&line->words[i]);
            outputQueue->size++;
        }
        // if it is a string(var), put it in the output stack.
        else if(!strcmp(line->words[i].token, STRING)) {
            outputQueue->words[outputQueue->size] = *copyLexObj(&line->words[i]);
            outputQueue->size++;
        }
        // needs to add later - if it is a func call
        // if it is an operator
        else if (!strcmp(line->words[i].token, OPERATOR)) {
            while((operatorStack->size != 0) &&
                    (precedence(&operatorStack->words[operatorStack->size-1]) <= precedence(&line->words[i])) &&
                    strcmp(operatorStack->words[operatorStack->size-1].value, "(")) {
                outputQueue->words[outputQueue->size] = *copyLexObj(&operatorStack->words[operatorStack->size - 1]);
                outputQueue->size++;
                operatorStack->size--;
            }
            operatorStack->words[operatorStack->size] = *copyLexObj(&line->words[i]);
            operatorStack->size++;
        }
        // dealing with brackets
        else if(!strcmp(line->words[i].value, "(")) {
            operatorStack->words[operatorStack->size] = *copyLexObj(&line->words[i]);
            operatorStack->size++;
        }
        else if(!strcmp(line->words[i].value, ")")) {
            while(strcmp(operatorStack->words[operatorStack->size - 1].value, "(")) {
                outputQueue->words[outputQueue->size] = *copyLexObj(&operatorStack->words[operatorStack->size - 1]);
                outputQueue->size++;
                operatorStack->size--;
            }
            operatorStack->size--;
        }
    }
    // leftovers
    while(operatorStack->size != 0) {
        outputQueue->words[outputQueue->size] = *copyLexObj(&operatorStack->words[operatorStack->size - 1]);
        outputQueue->size++;
        operatorStack->size--;
    }
    // printing for testing
    /*int j;
    for(j = 0; j < outputQueue->size; j++) {
        printf("%s\n", outputQueue->words[j].value);
    }
    printf("\n");*/
    return outputQueue;
}

int precedence(LexObj* obj) {
    // () []
    if(!strcmp(obj->value, "(") || !strcmp(obj->value, ")") ||
            !strcmp(obj->value, "[") || !strcmp(obj->value, "]")) {
        return 1;
    }
    // !
    if(!strcmp(obj->value, "!")) {
        return 2;
    }
    // * / %
    if(!strcmp(obj->value, "*") || !strcmp(obj->value, "/") ||
       !strcmp(obj->value, "%")) {
        return 3;
    }
    // + -
    if(!strcmp(obj->value, "+") || !strcmp(obj->value, "-")) {
        return 4;
    }
    // < <= > >=
    if(!strcmp(obj->value, "<") || !strcmp(obj->value, "<=") ||
       !strcmp(obj->value, ">") || !strcmp(obj->value, ">=")) {
        return 5;
    }
    // == !=
    if(!strcmp(obj->value, "==") || !strcmp(obj->value, "!=")) {
        return 6;
    }
    // &&
    if(!strcmp(obj->value, "&&")) {
        return 7;
    }
    // ||
    if(!strcmp(obj->value, "||")) {
        return 8;
    }
    // =
    if(!strcmp(obj->value, "=")) {
        return 9;
    }
    return 10;
}