//
// Created by Inbar
//

#include "Organizer.h"

/**
 * @param code - a code.
 * makes the code a more organized code that will make the compiler's work easier.
 */
LexCode* organize(LexCode* code) {
    LexCode* organized = copyLexCode(code);
    int i;
    for(i = 0; i < organized->size; i++) {
        // if this is a variable that is being assigned, split to 2 lines.
        if(organized->lines[i].size > 3 &&
            !strcmp(organized->lines[i].words[0].token, "type") &&
            strcmp(organized->lines[i].words[2].value, "(")) {
            organized = organizeAssign(organized, i);
        }
    }

    return organized;
}

/**
 * will organize assignment.
 * for example:
 *      int x = 0;
 * will become:
 *      int x;
 *      x = 0;
 *
 * @param code - the code we want to fix
 * @param index - the index of the line with the problem.
 * @return the code after fixing the line.
 */
LexCode* organizeAssign(LexCode* code, int index) {
    LexCode* organized = (LexCode*) malloc(sizeof(LexCode*));
    organized->lines = (LexLine*) malloc(LINE_AMOUNT * sizeof(LexObj));
    organized->size = code->size + 1;
    int i;

    // sets the lines before the indexed line to stay the same;
    for(i = 0; i < index; i++) {
        organized->lines[i].words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexObj));
        organized->lines[i] = *copyLexLine(&code->lines[i]);
    }

    organized->lines[index].words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexObj));
    organized->lines[index + 1].words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexObj));
    // sets the indexed line
    for(i = 0; i < code->lines[index].size; i++) {
        if(i < 2) {
            organized->lines[index].words[i] = *copyLexObj(&code->lines[index].words[i]);
        }
        if(i >= 1) {
            organized->lines[index + 1].words[i - 1] = *copyLexObj(&code->lines[index].words[i]);
        }
    }
    // sets ; in the end of the first line
    organized->lines[index].words[2].value = (char*) malloc(WORD_SIZE * sizeof(char));
    organized->lines[index].words[2].token = (char*) malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->lines[index].words[2].value, ";");
    strcpy(organized->lines[index].words[2].token, "cut");
    organized->lines[index].size = 3;
    organized->lines[index+1].size = code->lines[index].size - 1;

    // sets the rest of the words to stay the same.
    for(i = index + 1; i < code->size; i++) {
        organized->lines[i+1].words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexObj));
        organized->lines[i+1] = *copyLexLine(&code->lines[i]);
    }

    return organized;
}