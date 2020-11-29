//
// Created by Inbar
//

#ifndef MYLANGUAGE_ORGANIZER_H
#define MYLANGUAGE_ORGANIZER_H

#include "../Lexer/Lexer.h"

LexCode* organize(LexCode* code);
LexCode* organizeAssign(LexCode* code, int index);
LexLine* organizeIncDec(LexLine* line);
LexLine* organizeMath(LexLine* line);
LexCode* organizeBlock(LexCode* code, int index);
LexLine* organizeDoubleSigns(LexLine* line, int index);
LexCode* organizeEmptyLine(LexCode* code, int index);
#endif //MYLANGUAGE_ORGANIZER_H
