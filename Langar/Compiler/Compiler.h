//
// Created by Inbar
//

#ifndef MYLANGUAGE_COMPILER_H
#define MYLANGUAGE_COMPILER_H

#include "TemplatesIA32.h"
#include "../Shunting-yard/ShuntingYard.h"

char* compileClass(Class* class);
char* compileFunc(Func* func);
char* compileExpression(LexLine* expression, Func* func);
Var newVar(LexLine* line);
Var initVar(LexLine* line);
Func newFunc(LexLine* line);
Func initFunc(LexLine* line);
int getVarOffset(char* name,  Func* func);
#endif //MYLANGUAGE_COMPILER_H
