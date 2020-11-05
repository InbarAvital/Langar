//
// Created by Inbar on 01/11/2020.
//

#ifndef MYLANGUAGE_LEXER_H
#define MYLANGUAGE_LEXER_H
struct Line split(struct Line *line, char ch);
char* substring(char* string, int start, int finish);
struct Line lexerLine(struct Line *line, char* toSplit);
struct Line delString(struct Line* line, char* str);
struct Code* lexer(char* text);
#endif //MYLANGUAGE_LEXER_H
