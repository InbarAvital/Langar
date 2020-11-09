//
// Created by Inbar on 06/11/2020.
//

#ifndef MYLANGUAGE_GENERAL_H
#define MYLANGUAGE_GENERAL_H

#define WORD_AMOUNT 100
#define WORD_SIZE 100
#define LINE_AMOUNT 10000
#define MAX_TEXT LINE_AMOUNT*WORD_AMOUNT*WORD_SIZE

typedef struct Functions {
    char* name;
    char* returnType;
    char* arguments;
} Function;

#endif //MYLANGUAGE_GENERAL_H
