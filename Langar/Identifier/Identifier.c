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
            !strcmp(line->words[0].token, TYPE) &&
            !strcmp(line->words[1].token, STRING) &&
            !strcmp(line->words[2].token, CUT)) {
        strcpy(line->type, INIT_VAR);
        return;
    }
    // putting new value to a variable
    if(line->size >= 4 &&
            !strcmp(line->words[0].token, STRING) &&
            !strcmp(line->words[1].token, ASSIGN)) {
        strcpy(line->type, UPDATE_VAR);
        return;
    }
    // if now we have a type, it must be the beginning of a function
    if(!strcmp(line->words[0].token, TYPE)) {
        strcpy(line->type, INIT_FUNC);
        return;
    }
    // if, else or elif
    if(!strcmp(line->words[0].token, CONDITION)) {
        strcpy(line->type, CONDITION);
        return;
    }
    // while or for
    if(!strcmp(line->words[0].token, LOOP)) {
        strcpy(line->type, LOOP);
        return;
    }
    // block
    if(!strcmp(line->words[0].value, "{") || !strcmp(line->words[0].value, "}")) {
        strcpy(line->type, BLOCK);
        return;
    }
    // init_class
    if(!strcmp(line->words[0].value, "Class")) {
        strcpy(line->type, INIT_CLASS);
        return;
    }
    // return
    if(!strcmp(line->words[0].value, "return")) {
        strcpy(line->type, RETURN);
        return;
    }
    // unknown for now
    strcpy(line->type, UNKNOWN);
}