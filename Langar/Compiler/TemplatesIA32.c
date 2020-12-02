//
// Created by Inbar
//

#include "TemplatesIA32.h"

/**
 * @return an "add" action considering the two variables we need to add
 *         are already in the stack.
 */
char* addTemplate() {
    char* add = "    pop     ebx\n"
                "    pop     eax\n"
                "    add     eax, ebx\n"
                "    push    eax\n";
    return add;
}

/**
 * @return an "sub" action considering the two variables we need to subtract
 *         are already in the stack.
 */
char* subTemplate() {
    char* sub = "    pop     ebx\n"
                "    pop     eax\n"
                "    sub     eax, ebx\n"
                "    push    eax\n";
    return sub;
}

/**
 * @return an "mul" action considering the two variables we need to multiply
 *         are already in the stack.
 */
char* mulTemplate() {
    char* mul = "    pop     ebx\n"
                "    pop     eax\n"
                "    imul    eax, ebx\n"
                "    push    eax\n";
    return mul;
}

/**
 * @return an "div" action considering the two variables we need to divide
 *         are already in the stack.
 */
char* divTemplate() {
    char* div = "    pop     ebx\n"
                "    pop     eax\n"
                "    idiv    eax, ebx\n"
                "    push    eax\n";
    return div;
}

/**
 * @param offset - the offset from the base pointer.
 * @param sizePtr - the way we approach to the address (is it an int? a char?)
 * @return an update of the var in the given offset (puts the value from the stack).
 */
char* updateLocalVarFromStackTemplate(int offset, char* sizePtr) {
    char* offsetStr[WORD_SIZE];
    // turns the int to char*
    sprintf(offsetStr, "%d", offset);
    char* var = (char*) malloc(WORD_SIZE * sizeof(char));
    strcat(var, "    pop     eax\n"
                "    mov     ");
    strcat(var, sizePtr);
    strcat(var, offsetStr);
    strcat(var, "], eax\n");
    return var;
}

/**
 * @param offset - the offset from the base pointer.
 * @param value - the value we want to insert to the var.
 * @return an update of the var in the given offset (puts the value from the value argument).
 */
char* updateLocalVarFromValueTemplate(int offset, int value, char* sizePtr) {
    char* offsetStr[WORD_SIZE];
    char* valueStr[WORD_SIZE];
    // turns the int to char*
    sprintf(offsetStr, "%d", offset);
    sprintf(valueStr, "%d", value);
    char* var = (char*) malloc(WORD_SIZE * sizeof(char));
    strcat(var,"    mov     ");
    strcat(var, sizePtr);
    strcat(var, offsetStr);
    strcat(var, "], ");
    strcat(var, valueStr);
    strcat(var, "\n");
    return var;
}

/**
 * @return equal(=) template in assembly
 */
char* equalsTemplate() {
    char* str = "    pop     ebx\n"
                "    pop     eax\n"
                "    cmp     eax, ebx\n"
                "    cmove   eax, 1\n"
                "    cmovne  eax, 0\n"
                "    push    eax\n";
    return str;
}

/**
 * @return not equal(!=) template in assembly
 */
char* notEqualsTemplate() {
    char* str = "    pop     ebx\n"
                "    pop     eax\n"
                "    cmp     eax, ebx\n"
                "    cmovne  eax, 1\n"
                "    cmove   eax, 0\n"
                "    push    eax\n";
    return str;
}

/**
 * @return greater equal(>=) template in assembly
 */
char* greaterEqualsTemplate() {
    char* str = "    pop     ebx\n"
                "    pop     eax\n"
                "    cmp     eax, ebx\n"
                "    cmovge  eax, 1\n"
                "    cmovl   eax, 0\n"
                "    push    eax\n";
    return str;
}

/**
 * @return less equal(<=) template in assembly
 */
char* lessEqualsTemplate() {
    char* str = "    pop     ebx\n"
                "    pop     eax\n"
                "    cmp     eax, ebx\n"
                "    cmovle  eax, 1\n"
                "    cmovg   eax, 0\n"
                "    push    eax\n";
    return str;
}

/**
 * @return greater(>) template in assembly
 */
char* greaterTemplate() {
    char* str = "    pop     ebx\n"
                "    pop     eax\n"
                "    cmp     eax, ebx\n"
                "    cmovg   eax, 1\n"
                "    cmovle  eax, 0\n"
                "    push    eax\n";
    return str;
}

/**
 * @return less(<) template in assembly
 */
char* lessTemplate() {
    char* str = "    pop     ebx\n"
                "    pop     eax\n"
                "    cmp     eax, ebx\n"
                "    cmovl   eax, 1\n"
                "    cmovge  eax, 0\n"
                "    push    eax\n";
    return str;
}

/**
 * @return not(!) template in assembly
 */
char* notTemplate() {
    char* str = "    pop     eax\n"
                "    cmp     eax, 0\n"
                "    cmove   eax, 1\n"
                "    cmovne  eax, 0\n"
                "    push    eax\n";
    return str;
}

/**
 * @return and(&&) template in assembly
 */
char* andTemplate() {
    char* str = "    pop     eax\n"
                "    pop     ebx\n"
                "    and     eax, ebx\n"
                "    push    eax\n";
    return str;
}

/**
 * @return or(||) template in assembly
 */
char* orTemplate() {
    char* str = "    pop     eax\n"
                "    pop     ebx\n"
                "    or      eax, ebx\n"
                "    push    eax\n";
    return str;
}

/**
 * @return if template in assembly
 */
char* ifStatementTemplate(char* label) {
    char* str = (char*) malloc(WORD_SIZE * sizeof(char));
    strcpy(str, "    pop     eax\n"
                "    cmp     eax, 0\n"
                "    je      ");
    strcat(str, label);
    strcat(str, "\n");
    return str;
}
