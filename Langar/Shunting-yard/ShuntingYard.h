//
// Created by Inbar on 23/11/2020.
//

#ifndef MYLANGUAGE_SHUNTINGYARD_H
#define MYLANGUAGE_SHUNTINGYARD_H

#include "../Lexer/Lexer.h"
LexLine* shuntingYard(LexLine* line);
int precedence(LexObj* obj);

#endif //MYLANGUAGE_SHUNTINGYARD_H
