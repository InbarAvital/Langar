//
// Created by Inbar
//

#include "Lexer.h"

/**
 * @param code - the code splitted to tokens
 * @return the lexered code using the functions below. It basically means
 *         each token will receive a type stating what he is (number, string etc.)
 */
LexCode* lexer(TokCode* code) {
    int i;
    LexCode* lexered = (LexCode*)malloc(sizeof(LexCode));
    lexered->lines = (LexLine*)malloc(LINE_AMOUNT * sizeof(LexLine));
    lexered->size = code->size;
    for(i = 0; i < lexered->size; i++) {
        lexered->lines[i] = *lexerLine(&code->lines[i]);
    }
    return lexered;
}

/**
 *
 * @param line - a tokenized line
 * @return - the tokenized line with a token type inserted to each token.
 */
LexLine* lexerLine(TokLine* line) {
    int i;
    LexLine* lexered = (LexLine*)malloc(sizeof(LexLine));
    lexered->type = NULL;
    lexered->words = (LexObj*)malloc(WORD_AMOUNT * sizeof(LexObj));
    lexered->size = line->size;
    for(i = 0; i < lexered->size; i++) {
        lexered->words[i] = *lexerWord(line->words[i]);
    }
    return lexered;
}

/**
 * @param word - a string representing a word
 * @return - a LexObj - the word with the token(what type of word it is)
 */
LexObj* lexerWord(char* word) {
    LexObj *lexered = (LexObj*) malloc(sizeof(LexObj));
    lexered->value = (char*) malloc(WORD_SIZE * sizeof(char));
    strcpy(lexered->value, word);
    lexered->token = (char*) malloc(WORD_SIZE * sizeof(char));

    //checks if this is a state (private/public)
    if (!strcmp(word, "private") || !strcmp(word, "public")) {
        strcpy(lexered->token, STATE);
        return lexered;
    }

    // checks if this is a type(int, string, char, double, float, bool, void)
    if (!strcmp(word, "int") || !strcmp(word, "string") ||
        !strcmp(word, "char") || !strcmp(word, "double") ||
        !strcmp(word, "float") || !strcmp(word, "bool") ||
        !strcmp(word, "void")) {
        strcpy(lexered->token, TYPE);
        return lexered;
    }

    // checks if this is a number
    int i;
    int flag = 0; // the amount of . chars in this string
    for (i = 0; i < strlen(word); i++) {
        if (!isdigit(word[i])) {
            if (word[i] == '.' && flag == 0) {
                flag++;
            } else {
                flag = -1;
                break;
            }
        }
    }
    if (flag != -1) {
        strcpy(lexered->token, NUMBER);
        return lexered;
    }

    // checks if cut
    if(!strcmp(word, ";")) {
        strcpy(lexered->token, CUT);
        return lexered;
    }

    // checks if this is a normal sign
    if (!strcmp(word, "(") || !strcmp(word, ")") ||
            !strcmp(word, "[") || !strcmp(word, "]") ||
            !strcmp(word, "\"") || !strcmp(word, "'")) {
        strcpy(lexered->token, SIGN);
        return lexered;
    }

    // checks if this is a mathematical sign
    if (!strcmp(word, "+") || !strcmp(word, "-") ||
        !strcmp(word, "/") || !strcmp(word, "*")) {
        strcpy(lexered->token, OPERATOR);
        return lexered;
    }

    // special characters
    if(!strcmp(word, "=")) {
        strcpy(lexered->token, ASSIGN);
        return lexered;
    }
    if(!strcmp(word, "{")) {
        strcpy(lexered->token, BLOCK_START);
        return lexered;
    }
    if(!strcmp(word, "}")) {
        strcpy(lexered->token, BLOCK_END);
        return lexered;
    }

    // checks if it is a loop:
    if (!strcmp(word, "for") || !strcmp(word, "while")) {
        strcpy(lexered->token, LOOP);
        return lexered;
    }

    // checks if it is a condition
    if (!strcmp(word, "if") || !strcmp(word, "else") ||
            !strcmp(word, "elif")) {
        strcpy(lexered->token,  CONDITION);
        return lexered;
    }

    if(!strcmp(word, "<") || !strcmp(word, ">") ||
            !strcmp(word, "!")) {
        strcpy(lexered->token,  CONDITION_SIGN);
        return lexered;
    }

    // if we got this far, it is a string
    strcpy(lexered->token, STRING);
    return lexered;
}