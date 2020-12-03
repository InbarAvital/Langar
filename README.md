# Langar

**WORK IN PROGRESS - NOT COMPLETE**

My current goal is to create my own programming language, written in C.
I might add some cool unique things to it, still thinking :)

Take into consideration that I do not really have OOP in C, but I still wanted to write it in C to make it more of a challenge. Therefore, my code can't be separated into objects and have inheritance, so it affects the way I choose to implement stuff. I will try add as many explanations as I can for the least ideal things I do.

Let's see how it goes!

### What I have so far regarding processing the code given to me:
 - [X] Tokenizer - splits the code to tokens
 - [X] Lexer - take the tokens code and add info
 - [X] Organizer - organize the code to make it easier when we start compiling
 - [X] Identifier - gives a role to each line
 - [X] Shunting Yard algorithm - turns expressions to postfix notation

### What I have so far regarding the compiler:
 - [X] Operators
     - [X] Add
     - [X] Subtract
     - [X] Divide
     - [X] Multiply
 - [ ] Functions
     - [X] label
     - [X] return value (supports only the current types of variables I support).
     - [ ] calling a function
     - [ ] returning value using a function
     - [ ] getting arguments
 - [ ] Variables -
     - [X] int
     - [X] char
     - [X] bool
     - [ ] float
     - [ ] string
     - [X] deals with expressions such as: int a = 5+b*2-(4/2)
     - [X] local Variables
     - [ ] global Variables
     - [ ] arrays
 - [X] Conditions
     - [X] if
     - [X] else
     - [X] elif
     - [X] \>=, <=, >, <, ==, !=, &&, ||
 - [ ] Loops
     - [ ] while
     - [ ] for
 - [ ] Sections
 - [ ] Classes
 - [ ] Includes
 - [ ] Semantic checks -
     - will add later
          
## How my code works:

**Processing the code:**
 1. I go over the code given to me, and split it into tokens using the `Tokenizer`.
 2. I go over each token and give it a "role", for example - int is a 'type', + is an 'operator' etc. I use the `Lexer` to do so.
 3. I organize the code using the `Organizer`, to make it easier for me to compile. I delete empty lines, and does stuff like splitting 'int a = 5;' to 'int a;' and 'a = 5;'. You can go over the Organizer to see what other stuff I do.
 4. Just like I did with the lexer, giving the tokens roles, this time I give the lines roles, for example - 'int a;' will be set with 'initVar', I do the following with the `Identifier`.

**This is when the fun begins, and we have enough information about the code to start compiling it!**
 1. Currently, the compiler is first looking for functions.
 2. When found, it adds a label for the function and starts compiling it.
 3. It first looks for all the local variables and initialize them by giving them an offset.
 4. When we give those variables a value somewhere in the code, it looks for their offset and puts the value in the offset, using the `Shunting Yard Algorithm` if necessary.
 5. Also, if there is a reference to a variable, for example: a = b + 1, it will also look for b's offset and work with it.
 6. To be continued...

## An example of code showing the current ability of my compiler
The code I receive:
```c
int expressions() {
       // expression example
       int a = 5 + 3 - (10 / 2) * 7;
       return a;
}

void variables() {
    // examples of all the variables I currently support in
    int b = 7;
    char ch = 'a';
    // bool accepts both true/false and 1/0
    bool flag = true;
    flag = 0;
    int a = b;
    // you don't have to add a return line
    return;
}

void returnTest() {
    // the function ends here when translating to assembly
    return;
    int a = 1;
    int b = 2;
    a = b + 5;
}

int conditions() {
    // conditions example
    int a = 10;
    int b = 9;
    if(a > 8 || b != 9) {
        if(a < 7) {
            a = 6;
        }
        a = 5;
    } elif(b >= 4 && a==10) {
        b = 3;
    } else {
        b = 2;
    }
    b = 1;
    return a;
}
```
The assembly code I return:
```asm
expressions:
    push    ebp
    mov     ebp, esp
    sub     esp, 4
    push    5
    push    3
    pop     ebx
    pop     eax
    add     eax, ebx
    push    eax
    push    10
    push    2
    pop     ebx
    pop     eax
    idiv    eax, ebx
    push    eax
    push    7
    pop     ebx
    pop     eax
    imul    eax, ebx
    push    eax
    pop     ebx
    pop     eax
    sub     eax, ebx
    push    eax
    pop     eax
    mov     DWORD PTR[ebp - 4], eax
    mov     eax, DWORD PTR[ebp - 4]
    mov     esp, ebp
    pop     ebp
    ret

variables:
    push    ebp
    mov     ebp, esp
    sub     esp, 10
    push    7
    pop     eax
    mov     DWORD PTR[ebp - 4], eax
    mov     BYTE PTR[ebp - 5], 97
    mov     BYTE PTR[ebp - 6], 1
    mov     BYTE PTR[ebp - 6], 0
    mov     ebx, DWORD PTR[ebp - 4]
    push    ebx
    pop     eax
    mov     DWORD PTR[ebp - 10], eax
    mov     esp, ebp
    pop     ebp
    ret

returnTest:
    push    ebp
    mov     ebp, esp
    mov     esp, ebp
    pop     ebp
    ret

conditions:
    push    ebp
    mov     ebp, esp
    sub     esp, 8
    push    10
    pop     eax
    mov     DWORD PTR[ebp - 4], eax
    push    9
    pop     eax
    mov     DWORD PTR[ebp - 8], eax
    mov     ebx, DWORD PTR[ebp - 4]
    push    ebx
    push    8
    pop     ebx
    pop     eax
    cmp     eax, ebx
    cmovg   eax, 1
    cmovle  eax, 0
    push    eax
    mov     ebx, DWORD PTR[ebp - 8]
    push    ebx
    push    9
    pop     ebx
    pop     eax
    cmp     eax, ebx
    cmovne  eax, 1
    cmove   eax, 0
    push    eax
    pop     eax
    pop     ebx
    or      eax, ebx
    push    eax
    pop     eax
    cmp     eax, 0
    je      conditions_c_2
    mov     ebx, DWORD PTR[ebp - 4]
    push    ebx
    push    7
    pop     ebx
    pop     eax
    cmp     eax, ebx
    cmovl   eax, 1
    cmovge  eax, 0
    push    eax
    pop     eax
    cmp     eax, 0
    je      conditions_c_1
    push    6
    pop     eax
    mov     DWORD PTR[ebp - 4], eax

conditions_c_1:
    push    5
    pop     eax
    mov     DWORD PTR[ebp - 4], eax
    jmp     conditions_c_4

conditions_c_2:
    mov     ebx, DWORD PTR[ebp - 8]
    push    ebx
    push    4
    pop     ebx
    pop     eax
    cmp     eax, ebx
    cmovge  eax, 1
    cmovl   eax, 0
    push    eax
    mov     ebx, DWORD PTR[ebp - 4]
    push    ebx
    push    10
    pop     ebx
    pop     eax
    cmp     eax, ebx
    cmove   eax, 1
    cmovne  eax, 0
    push    eax
    pop     eax
    pop     ebx
    and     eax, ebx
    push    eax
    pop     eax
    cmp     eax, 0
    je      conditions_c_3
    push    3
    pop     eax
    mov     DWORD PTR[ebp - 8], eax
    jmp     conditions_c_4

conditions_c_3:
    push    2
    pop     eax
    mov     DWORD PTR[ebp - 8], eax

conditions_c_4:
    push    1
    pop     eax
    mov     DWORD PTR[ebp - 8], eax
    mov     eax, DWORD PTR[ebp - 4]
    mov     esp, ebp
    pop     ebp
    ret
```

The optimizations will be applied in the end.