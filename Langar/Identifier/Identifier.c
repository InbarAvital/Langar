//
// Created by Inbar
//

#include "Identifier.h"

void identifyCode(LexCode* code) {
    int i;
    for(i = 0; i < code->size; i++) {
        identifyLine(&code->lines[i]);
    }
}

/**
 * Identifying the line's type, considering the the user
 * did not do any mistakes (Mistakes will be checked later on).
 * @param line - the line.
 */
void identifyLine(LexLine* line) {
    line->type = (char*)malloc(TYPE_SIZE * sizeof(char));
    // initializing variable
    if(line->size == 3 &&
            !strcmp(line->words[0].token, "type") &&
            !strcmp(line->words[1].token, "string") &&
            !strcmp(line->words[2].token, "cut")) {
        strcpy(line->type, "init_var");
        return;
    }
    // putting new value to a variable
    if(line->size >= 4 &&
            !strcmp(line->words[0].token, "string") &&
            !strcmp(line->words[1].token, "assign")) {
        strcpy(line->type, "update_var");
        return;
    }
    // if now we have a type, it must be the beginning of a function
    if(!strcmp(line->words[0].token, "type")) {
        strcpy(line->type, "init_func");
        return;
    }
    // if, else or elif
    if(!strcmp(line->words[0].token, "condition")) {
        strcpy(line->type, "condition");
        return;
    }
    // while or for
    if(!strcmp(line->words[0].token, "loop")) {
        strcpy(line->type, "loop");
        return;
    }
    // block
    if(!strcmp(line->words[0].value, "{") || !strcmp(line->words[0].value, "}")) {
        strcpy(line->type, "block");
        return;
    }
    // init_class
    if(!strcmp(line->words[0].value, "Class")) {
        strcpy(line->type, "init_class");
        return;
    }
    // return
    if(!strcmp(line->words[0].value, "return")) {
        strcpy(line->type, "return");
        return;
    }
    strcpy(line->type, "unknown");
}