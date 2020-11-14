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

        // a++ and a-- will be turned to a=a+1 and a=a-1
        if(organized->lines[i].size == 4 &&
                !strcmp(organized->lines[i].words[0].token, "string") &&
                ((!strcmp(organized->lines[i].words[1].value, "+") && !strcmp(organized->lines[i].words[2].value, "+")) ||
                ((!strcmp(organized->lines[i].words[1].value, "-") && !strcmp(organized->lines[i].words[2].value, "-")))) &&
                !strcmp(organized->lines[i].words[3].token, "cut")) {
            organized->lines[i] = *organizeIncDec(&organized->lines[i]);
        }

        // a+=b, a-=b, a*=b, a/=b  ==>  a=a+(b), a=a-(b), a=a*(b), a=a/(b)
        if(organized->lines[i].size > 3 &&
                !strcmp(organized->lines[i].words[0].token, "string") &&
                !strcmp(organized->lines[i].words[1].token, "m_sign") &&
                !strcmp(organized->lines[i].words[2].token, "assign")) {
            organized->lines[i] = *organizeMath(&organized->lines[i]);
        }

        // int a() { - the { will be in a new line.
        if(organized->lines[i].size > 1 &&
                (!strcmp(organized->lines[i].words[organized->lines[i].size - 1].value, "{") ||
                !strcmp(organized->lines[i].words[organized->lines[i].size - 1].value, "}"))) {
            organized = organizeBlock(organized, i);
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
    organized->lines = (LexLine*) malloc(LINE_AMOUNT * sizeof(LexLine));
    organized->size = code->size + 1;
    int i;

    // sets the lines before the indexed line to stay the same;
    for(i = 0; i < index; i++) {
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
        organized->lines[i+1] = *copyLexLine(&code->lines[i]);
    }
    return organized;
}

/**
 * a++ and a-- will be turned to a=a+1 and a=a-1
 *
 * @param line - the line we want to fix.
 * @return the line after fixing the problem.
 */
LexLine* organizeIncDec(LexLine* line) {
    LexLine* organized = (LexLine*) malloc(sizeof(LexLine));
    organized->words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexObj));
    organized->size = 6;

    // sets the first value to be the variable's name
    organized->words[0].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[0].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[0].value, line->words[0].value);
    strcpy(organized->words[0].token, line->words[0].token);

    // second value is equal sign
    organized->words[1].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[1].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[1].value, "=");
    strcpy(organized->words[1].token, "assign");

    // third value is also the variable's name
    organized->words[2].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[2].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[2].value, line->words[0].value);
    strcpy(organized->words[2].token, line->words[0].token);

    // forth value is the sign in the current line (inc or dec)
    organized->words[3].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[3].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[3].value, line->words[1].value);
    strcpy(organized->words[3].token, line->words[1].token);

    // fifth value is the number one
    organized->words[4].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[4].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[4].value, "1");
    strcpy(organized->words[4].token, "number");

    // sixth value is ;
    organized->words[5].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[5].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[5].value, ";");
    strcpy(organized->words[5].token, "cut");

    return organized;
}

/**
 * a+=b, a-=b, a*=b, a/=b  ==>  a=a+(b), a=a-(b), a=a*(b), a=a/(b)
 *
 * @param line - the line we want to fix.
 * @return the line after fixing the problem.
 */
LexLine* organizeMath(LexLine* line) {
    LexLine* organized = (LexLine*) malloc(sizeof(LexLine));
    organized->words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexObj));
    organized->size = line->size + 3;

    // sets the first value to be the variable's name
    organized->words[0].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[0].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[0].value, line->words[0].value);
    strcpy(organized->words[0].token, line->words[0].token);

    // second value is equal sign
    organized->words[1].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[1].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[1].value, "=");
    strcpy(organized->words[1].token, "assign");

    // third value is also the variable's name
    organized->words[2].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[2].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[2].value, line->words[0].value);
    strcpy(organized->words[2].token, line->words[0].token);

    // forth value is the sign in the current line (inc or dec)
    organized->words[3].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[3].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[3].value, line->words[1].value);
    strcpy(organized->words[3].token, line->words[1].token);

    // fifth value is "("
    organized->words[4].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[4].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[4].value, "(");
    strcpy(organized->words[4].token, "sign");

    // now the rest stay the same
    int i = 0;
    for(i = 3; i < line->size - 1; i++) {
        organized->words[i+2].value = (char*)malloc(WORD_SIZE * sizeof(char));
        organized->words[i+2].token = (char*)malloc(WORD_SIZE * sizeof(char));
        strcpy(organized->words[i+2].value, line->words[i].value);
        strcpy(organized->words[i+2].token, line->words[i].token);
    }

    // and it will end with );
    organized->words[organized->size - 2].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[organized->size - 2].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[organized->size - 2].value, ")");
    strcpy(organized->words[organized->size - 2].token, "sign");
    organized->words[organized->size - 1].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[organized->size - 1].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[organized->size - 1].value, ";");
    strcpy(organized->words[organized->size - 1].token, "cut");

    return organized;
}

/**
 * int a() { - the { will be in a new line.
 *
 * @param line - the line we want to fix.
 * @return the line after fixing the problem.
 */
LexCode* organizeBlock(LexCode* code, int index) {
    LexCode* organized = (LexCode*) malloc(sizeof(LexCode*));
    organized->lines = (LexLine*) malloc(LINE_AMOUNT * sizeof(LexLine));
    organized->size = code->size + 1;
    int i;

    // sets the lines before the indexed line to stay the same;
    for(i = 0; i < index; i++) {
        organized->lines[i] = *copyLexLine(&code->lines[i]);
    }

    organized->lines[index].words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexObj));
    organized->lines[index + 1].words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexObj));

    // sets the indexed line
    for(i = 0; i < code->lines[index].size - 1; i++) {
        organized->lines[index].words[i] = *copyLexObj(&code->lines[index].words[i]);
    }
    organized->lines[index].size = code->lines[index].size - 1;

    // adds the new { line
    organized->lines[index + 1].words[0].value = (char*) malloc(WORD_SIZE * sizeof(char));
    organized->lines[index + 1].words[0].token = (char*) malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->lines[index + 1].words[0].value, "{");
    strcpy(organized->lines[index + 1].words[0].token, "sign");
    organized->lines[index + 1].size = 1;

    // sets the rest of the words to stay the same.
    for(i = index + 1; i < code->size; i++) {
        organized->lines[i+1] = *copyLexLine(&code->lines[i]);
    }
    return organized;
}