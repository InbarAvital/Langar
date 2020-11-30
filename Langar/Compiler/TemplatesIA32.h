//
// Created by Inbar on 13/11/2020.
//

#ifndef MYLANGUAGE_TEMPLATESIA32_H
#define MYLANGUAGE_TEMPLATESIA32_H

#include "../Structs.h"
char* addTemplate();
char* subTemplate();
char* mulTemplate();
char* divTemplate();
char* updateLocalVarFromStackTemplate(int offset, char* sizePtr);
char* updateLocalVarFromValueTemplate(int offset, int value, char* sizePtr);
char* ifStatementTemplate(LexLine* line);

#endif //MYLANGUAGE_TEMPLATESIA32_H
