cmake_minimum_required(VERSION 3.15)
project(MyLanguage)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyLanguage
        Main.c
        Lexer/Lexer.c
        Lexer/Lexer.h
        ObjectsStructs.h
        Tokenizer/Tokenizer.c
        Tokenizer/Tokenizer.h)