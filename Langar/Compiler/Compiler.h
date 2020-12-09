//
// Created by Inbar
//

#ifndef MYLANGUAGE_COMPILER_H
#define MYLANGUAGE_COMPILER_H

#include "TemplatesIA32.h"
#include "../Shunting-yard/ShuntingYard.h"

char* compileClass(Class* class);
char* compileExpression(LexLine* expression, Func* func);
char* compileReturn(LexLine* line, Func* func);
char* getSizePtr(Var* var);

// Variables
Var initVar(LexLine* line);
Var* getVar(char* name,  Func* func);
void compileInitVar(Func* func, int index);
char* compileUpdateLocalVar(Func* func, int index);

// Functions
char* compileFunc(Func* func);
Func initFunc(LexLine* line);

// Conditions
char* compileCondition(Func* func, int index);
int getConditionLength(Func* func, int index);
int getInsideCondition(Func* func, int index);

// Loops
char* compileLoop(Func* func, int index);
int getInsideLoop(Func* func, int index);

#endif //MYLANGUAGE_COMPILER_H
