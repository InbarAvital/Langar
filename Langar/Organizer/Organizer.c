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
    int i, j;
    for(i = 0; i < organized->size; i++) {
        // if this is a variable that is being assigned, split to 2 lines.
        if(organized->lines[i].size > 3 &&
                !strcmp(organized->lines[i].words[0].token, TYPE) &&
                strcmp(organized->lines[i].words[2].value, "(")) {
            organized = organizeAssign(organized, i);
        }
        // a++ and a-- will be turned to a=a+1 and a=a-1
        if(organized->lines[i].size == 4 &&
                !strcmp(organized->lines[i].words[0].token, STRING) &&
                ((!strcmp(organized->lines[i].words[1].value, "+") && !strcmp(organized->lines[i].words[2].value, "+")) ||
                ((!strcmp(organized->lines[i].words[1].value, "-") && !strcmp(organized->lines[i].words[2].value, "-")))) &&
                !strcmp(organized->lines[i].words[3].token, CUT)) {
            organized->lines[i] = *organizeIncDec(&organized->lines[i]);
        }
        // a+=b, a-=b, a*=b, a/=b  ==>  a=a+(b), a=a-(b), a=a*(b), a=a/(b)
        if(organized->lines[i].size > 3 &&
                !strcmp(organized->lines[i].words[0].token, STRING) &&
                !strcmp(organized->lines[i].words[1].token, OPERATOR) &&
                !strcmp(organized->lines[i].words[2].token, ASSIGN)) {
            organized->lines[i] = *organizeMath(&organized->lines[i]);
        }
        // int a() { - the { will be in a new line.
        if(organized->lines[i].size > 1 &&
                (!strcmp(organized->lines[i].words[organized->lines[i].size - 1].value, "{") ||
                !strcmp(organized->lines[i].words[organized->lines[i].size - 1].value, "}"))) {
            organized = organizeBlock(organized, i);
        }
        // &&, ||, ==, !=, <=, >= -----> will become one LexObj
        for(j = 0; j < organized->lines[i].size - 1; j++) {
            if((!strcmp(organized->lines[i].words[j].value, "&") &&
                    !strcmp(organized->lines[i].words[j+1].value, "&")) ||
                    (!strcmp(organized->lines[i].words[j].value, "|") &&
                     !strcmp(organized->lines[i].words[j+1].value, "|")) ||
                    (!strcmp(organized->lines[i].words[j+1].value, "=") &&
                            (!strcmp(organized->lines[i].words[j].value, "=") ||
                            !strcmp(organized->lines[i].words[j].value, ">") ||
                            !strcmp(organized->lines[i].words[j].value, "<") ||
                            !strcmp(organized->lines[i].words[j].value, "!")))) {
                organized->lines[i] = *organizeDoubleSigns(&organized->lines[i], j);
            }
        }
        // if there is an empty line - delete it.
        if(organized->lines[i].size == 0) {
            organized = deleteLine(organized, i);
            i--;
        }
        // } with something after will be splited to 2 lines.
        if(organized->lines[i].size > 1 && !strcmp(organized->lines[i].words[0].value, "}")) {
            organized = organizeEndBlock(organized, i);
        }
        // deletes a comment
        if(!strcmp(organized->lines[i].words[0].value, "/") &&
                !strcmp(organized->lines[i].words[1].value, "/")) {
            organized = deleteLine(organized, i);
            i--;
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
    strcpy(organized->lines[index].words[2].token, CUT);
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
    strcpy(organized->words[1].token, ASSIGN);
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
    strcpy(organized->words[4].token, NUMBER);
    // sixth value is ;
    organized->words[5].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[5].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[5].value, ";");
    strcpy(organized->words[5].token, CUT);
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
    strcpy(organized->words[1].token, ASSIGN);
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
    strcpy(organized->words[4].token, SIGN);
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
    strcpy(organized->words[organized->size - 2].token, SIGN);
    organized->words[organized->size - 1].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[organized->size - 1].token = (char*)malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->words[organized->size - 1].value, ";");
    strcpy(organized->words[organized->size - 1].token, CUT);
    return organized;
}

/**
 * int a() { - the { will be in a new line.
 *
 * @param line - the line we want to fix.
 * @return the code after fixing the problem.
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
    strcpy(organized->lines[index + 1].words[0].token, SIGN);
    organized->lines[index + 1].size = 1;
    // sets the rest of the words to stay the same.
    for(i = index + 1; i < code->size; i++) {
        organized->lines[i+1] = *copyLexLine(&code->lines[i]);
    }
    return organized;
}

/**
 * &&, ||, ==, !=, <=, >= -----> will become one LexObj
 *
 * @param line - the line we want to fix.
 * @return the line after fixing the problem.
 */
LexLine* organizeDoubleSigns(LexLine* line, int index) {
    LexLine* organized = (LexLine*) malloc(sizeof(LexLine));
    organized->words = (LexObj*) malloc(WORD_AMOUNT * sizeof(LexObj));
    organized->size = line->size - 1;
    int i = 0;
    // keeps the beginning of the line the same
    for(i = 0; i < index; i++) {
        organized->words[i].value = (char*)malloc(WORD_SIZE * sizeof(char));
        organized->words[i].token = (char*)malloc(WORD_SIZE * sizeof(char));
        strcpy(organized->words[i].value, line->words[i].value);
        strcpy(organized->words[i].token, line->words[i].token);
    }
    // allocates space
    organized->words[index].value = (char*)malloc(WORD_SIZE * sizeof(char));
    organized->words[index].token = (char*)malloc(WORD_SIZE * sizeof(char));
    if(!strcmp(line->words[index].value, "&") &&
        !strcmp(line->words[index+1].value, "&")) {
        // combines & and & to one
        strcpy(organized->words[index].value, "&&");
        strcpy(organized->words[index].token, AND);
    } else if(!strcmp(line->words[index].value, "|") &&
       !strcmp(line->words[index + 1].value, "|")) {
        // combines | and | to one
        strcpy(organized->words[index].value, "||");
        strcpy(organized->words[index].token, OR);
    }
    else {
        if(!strcmp(line->words[index].value, "=")) {
            // combines = and = to one
            strcpy(organized->words[index].value, "==");
            strcpy(organized->words[index].token, CONDITION_ASSIGN);
        } else if(!strcmp(line->words[index].value, ">")) {
            // combines < and = to one
            strcpy(organized->words[index].value, ">=");
            strcpy(organized->words[index].token, CONDITION_ASSIGN);
        } else if(!strcmp(line->words[index].value, "<")) {
            // combines > and = to one
            strcpy(organized->words[index].value, "<=");
            strcpy(organized->words[index].token, CONDITION_ASSIGN);
        } else {
            // combines ! and = to one
            strcpy(organized->words[index].value, "!=");
            strcpy(organized->words[index].token, CONDITION_ASSIGN);
        }
    }
    // keeps the end of the line the same
    for(i = index + 1; i < organized->size; i++) {
        organized->words[i].value = (char*)malloc(WORD_SIZE * sizeof(char));
        organized->words[i].token = (char*)malloc(WORD_SIZE * sizeof(char));
        strcpy(organized->words[i].value, line->words[i + 1].value);
        strcpy(organized->words[i].token, line->words[i + 1].token);
    }
    return organized;
}

/**
 * deletes a line
 *
 * @param line - the line we want to delete.
 * @return the code after fixing the problem.
 */
LexCode* deleteLine(LexCode* code, int index) {
    LexCode* organized = (LexCode*) malloc(sizeof(LexCode*));
    organized->lines = (LexLine*) malloc(LINE_AMOUNT * sizeof(LexLine));
    organized->size = code->size - 1;
    int i;
    // adds the lines before the indexed line;
    for(i = 0; i < index; i++) {
        organized->lines[i] = *copyLexLine(&code->lines[i]);
    }
    // adds the lines after the indexed line;
    for(i = index + 1; i < code->size; i++) {
        organized->lines[i - 1] = *copyLexLine(&code->lines[i]);
    }
    return organized;
}

/**
 * @param code - the code
 * @param index - the index of the line with the problem (} and then something after it)
 * @return a fixed code.
 */
LexCode* organizeEndBlock(LexCode* code, int index) {
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
    // adds the new } line
    organized->lines[index].words[0].value = (char*) malloc(WORD_SIZE * sizeof(char));
    organized->lines[index].words[0].token = (char*) malloc(WORD_SIZE * sizeof(char));
    strcpy(organized->lines[index].words[0].value, "}");
    strcpy(organized->lines[index].words[0].token, SIGN);
    organized->lines[index].size = 1;

    // sets line after that
    for(i = 0; i < code->lines[index].size - 1; i++) {
        organized->lines[index + 1].words[i] = *copyLexObj(&code->lines[index].words[i + 1]);
    }
    organized->lines[index + 1].size = code->lines[index].size - 1;

    // sets the rest of the lines to stay the same.
    for(i = index + 1; i < code->size; i++) {
        organized->lines[i+1] = *copyLexLine(&code->lines[i]);
    }
    return organized;
}