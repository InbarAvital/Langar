//
// Created by Inbar
//

#include "TemplatesIA32.h"

/**
 * @return an "add" action considering the two variables we need to add
 *         are already in the stack.
 */
char* addTemplate() {
    char* add = "    pop     eax\n"
                "    pop     ebx\n"
                "    add     eax, ebx\n"
                "    push    eax\n";
    return add;
}

/**
 * @return an "sub" action considering the two variables we need to subtract
 *         are already in the stack.
 */
char* subTemplate() {
    char* sub = "    pop     eax\n"
                "    pop     ebx\n"
                "    sub     eax, ebx\n"
                "    push    eax\n";
    return sub;
}

/**
 * @return an "mul" action considering the two variables we need to multiply
 *         are already in the stack.
 */
char* mulTemplate() {
    char* mul = "    pop     eax\n"
                "    pop     ebx\n"
                "    imul    eax, ebx\n"
                "    push    eax\n";
    return mul;
}

/**
 * @return an "div" action considering the two variables we need to divide
 *         are already in the stack.
 */
char* divTemplate() {
    char* div = "    pop     eax\n"
                "    pop     ebx\n"
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
// !=, ==, >, <, bool, !bool, <=, >=, &&, ||
char* ifStatementTemplate(LexLine* line) {

}
