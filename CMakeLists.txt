cmake_minimum_required(VERSION 3.15)
project(MyLanguage)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyLanguage
        Langar/Main.c
        Langar/Lexer/Lexer.c
        Langar/Lexer/Lexer.h
        Langar/Lexer/LexeredCode.c
        Langar/Tokenizer/Tokenizer.c
        Langar/Tokenizer/Tokenizer.h
        Langar/Identifier/Identifier.c
        Langar/Organizer/Organizer.c
        Langar/Organizer/Organizer.h
        Langar/Structs.h
        Langar/Compiler/Compiler.c
        Langar/Compiler/Compiler.h
        Langar/Compiler/TemplatesIA32.c
        Langar/Compiler/TemplatesIA32.h)