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
Var* getVar(char* name,  Func* func);
char* compileReturn(LexLine* line, Func* func);
void compileInitVar(Func* func, int index);
char* getSizePtr(Var* var);
char* compileUpdateLocalVar(Func* func, int index);
char* compileCondition(Func* func, int index);
int getConditionLength(Func* func, int index);
int getInsideCondition(Func* func, int index);

#endif //MYLANGUAGE_COMPILER_H
