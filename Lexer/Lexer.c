//
// Created by Inbar
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../GeneralStructs.h"
#include "Lexer.h"

/**
 * @param text - code lines.
 * @return - a code (an array of lines) - after lexsering.
 */
struct Code* lexer(char* text) {

    // initializing lines for code (allocating)
    struct Code *lexered = (struct Code*) malloc(sizeof(struct Code));
    int i, j;
    lexered->lines = (struct Line*) malloc(LINE_AMOUNT * sizeof(struct Line));
    for(i = 0; i < LINE_AMOUNT; i++) {
        lexered->lines[i].words = (char **) malloc(WORD_AMOUNT * sizeof(char *));
        lexered->lines[i].size = 0;
    }
    lexered->size = 0;

    // transforming from text(strings) to "Lines"
    int latest = 0;
    for(i = 0; i < strlen(text); i++) {
        if(text[i] == '\n') {
            lexered->lines[lexered->size].words[0] = (char *) malloc(WORD_SIZE * sizeof(char));
            strcpy(lexered->lines[lexered->size].words[0], substring(text, latest, i-1));
            lexered->lines[lexered->size].size = 1;
            latest = i+1;
            lexered->size = lexered->size + 1;
        }
    }
    // for the case we did not end the text with \n
    if(latest != i) {
        lexered->lines[lexered->size].words[0] = (char *) malloc(WORD_SIZE * sizeof(char));
        strcpy(lexered->lines[lexered->size].words[0], substring(text, latest, i-1));
        lexered->lines[lexered->size].size = 1;
        lexered->size = lexered->size + 1;
    }

    // the chars I split my lines by
    char* splitBy = " (){}[]<>!=\";";

    // sending each line to line lexer
    for(i = 0; i < lexered->size; i++) {
        lexered->lines[i] = lexerLine(&lexered->lines[i], splitBy);
    }

    return lexered;
}

/**
 * @param line - a struct including:
 *                  ~ an array of strings
 *                  ~ an int indicating how many strings are in the array.
 * @param toSplit - a string in which each char is a char we want to split our line by.
 * @return - a new line, lexered as requested (according to "tosplit")
 */
struct Line lexerLine(struct Line *line, char* toSplit) {
    struct Line lexered = *line;
    int i;
    for(i = 0; i < strlen(toSplit); i++) {
        lexered = split(&lexered, toSplit[i]);
    }
    // get rid of spaces
    lexered = delString(&lexered, " ");

    return lexered;
}

/**
 * @param line - a struct including:
 *                  ~ an array of strings
 *                  ~ an int indicating how many strings are in the array.
 * @param ch - the char we want to split the strings by
 * @return a new line, in which all of the "ch" chars are separated
 *         from the rest of the words. It does not delete them since some
 *         chars we want to keep for later.
 */
struct Line split(struct Line *line, char ch) {
    int i, j;

    // we will use this var in order to know where was the latest split
    int latest = 0;
    struct Line new_line;

    // setting initial values for the new line
    new_line.words = (char**) malloc(WORD_AMOUNT * sizeof(char*));
    new_line.size = 0;

    // checks for each word - is the char in there?
    // if yes - splits the char from the rest.
    // if not - keeps the current word as it is.
    for(j = 0; j < line->size; j++) {
        latest = 0;
        for(i = 0; line->words[j][i] != '\0'; i++) {
            if(line->words[j][i] == ch) {
                // if this there is something before this char
                if(i != latest) {
                    // first part of the word
                    new_line.words[new_line.size] = (char *) malloc(WORD_SIZE * sizeof(char));
                    strcpy(new_line.words[new_line.size], substring(line->words[j], latest, i-1));
                    new_line.size += 1;
                }
                // second part of the word
                new_line.words[new_line.size] = (char *) malloc(WORD_SIZE * sizeof(char));
                strcpy(new_line.words[new_line.size], substring(line->words[j], i, i));
                new_line.size += 1;
                latest = i+1;
            }
        }
        // if the word has some chars left
        if(latest != i) {
            new_line.words[new_line.size] = (char *) malloc(WORD_SIZE * sizeof(char));
            strcpy(new_line.words[new_line.size], substring(line->words[j], latest, i-1));
            new_line.size += 1;
        }
    }

    // freeing allocation
    for(i = 0; i < line->size; i++) {
        free(line->words[i]);
    }
    free(line->words);

    return new_line;
}

/**
 * @param str - a string
 * @param start - index of the beginning
 * @param finish - index of the end
 * @return a string including only the substring of
 *         str between start and finish (including)
 */
char* substring(char* str, int start, int finish) {
    int i;
    char* substr = (char*) malloc(WORD_SIZE * sizeof(char));
    for(i = start; i <= finish; i++) {
        substr[i-start] = str[i];
    }
    if(substr[i] != '\0') {
        substr[i] = '\0';
    }
    return substr;
}

struct Line delString(struct Line* line, char* str) {
    int i;

    // we will use this var in order to know where was the latest split
    int latest = 0;
    struct Line new_line;

    // setting initial values for the new line
    new_line.words = (char**) malloc(WORD_AMOUNT * sizeof(char*));
    new_line.size = 0;

    // checks for each word - is it the string?
    // if yes - doesn't keep
    // else - keeps
    for(i = 0; i < line->size; i++) {
        char* x = line->words[i];
        if(strcmp(line->words[i],str)) {
            new_line.words[new_line.size] = (char*) malloc(WORD_SIZE * sizeof(char));
            strcpy(new_line.words[new_line.size], line->words[i]);
            new_line.size += 1;
        }
    }

    // freeing allocation
    for(i = 0; i < line->size; i++) {
        free(line->words[i]);
    }
    free(line->words);

    return new_line;
}