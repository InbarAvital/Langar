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
char* updateLocalVarTemplate(int offset);
char* ifStatementTemplate(LexLine* line);

#endif //MYLANGUAGE_TEMPLATESIA32_H
