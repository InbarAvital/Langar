//
// Created by Inbar on 01/11/2020.
//

#ifndef MYLANGUAGE_STRUCTS_H
#define MYLANGUAGE_STRUCTS_H
#define WORD_AMOUNT 100
#define WORD_SIZE 100
#define LINE_AMOUNT 10000
/**
 * This struct represent a line,
 * including the amount of words in it.
 */
struct Line {
    char** words;
    int size;
};

struct Code {
    struct Line* lines;
    int size;
};
#endif //MYLANGUAGE_STRUCTS_H
