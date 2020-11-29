# Langar
MY CURRENT WORK - NOT COMPLETE

My current goal is to create my own programming language, written in C.
I might add some cool unique things to it, still thinking :)

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
     - [ ] return value
     - [ ] recursion
 - [ ] Variables -
     - [X] int
     - [ ] char
     - [ ] bool
     - [ ] float
     - [ ] string
     - [X] deals with expressions such as: int a = 5+b*2-(4/2)
     - [X] local Variables
     - [ ] global Variables
     - [ ] arrays
 - [ ] Conditions
     - [ ] if
     - [ ] else
     - [ ] elif
 - [ ] Loops
     - [ ] while
     - [ ] for
 - [ ] Classes
 - [ ] Includes
 - [ ] Semantic checks -
     - will add later
          



## An example of code showing the current ability of my compiler
The code I receive:
```c
void func() {
        int a = 5 + 3 - (3 - 5) * 3;
        int b = 7;
        a = b + 1;
}
```
The assembly code I return:
```asm
func:
    push    ebp
    mov     ebp, esp
    push    5
    push    3
    pop     eax
    pop     ebx
    add     eax, ebx
    push    eax
    push    3
    push    5
    pop     eax
    pop     ebx
    sub     eax, ebx
    push    eax
    push    3
    pop     eax
    pop     ebx
    imul    eax, ebx
    push    eax
    pop     eax
    pop     ebx
    sub     eax, ebx
    push    eax
    pop     eax
    mov     DWORD PTR [ebp - 4], eax
    push    7
    pop     eax
    mov     DWORD PTR [ebp - 8], eax
    push    DWORD PTR [ebp - 8]
    push    1
    pop     eax
    pop     ebx
    add     eax, ebx
    push    eax
    pop     eax
    mov     DWORD PTR [ebp - 4], eax
    mov     esp, ebp
    pop     ebp
    ret
```
I know, it's not much, and needs some fixes, but I am still working on it :)

The optimizations will be applied in the end.