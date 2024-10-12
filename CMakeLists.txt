cmake_minimum_required(VERSION 3.28)
project(duck)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(duck src/main.cpp
        src/lang/Lexer.cpp 
        src/lang/Token.cpp
        include/duck/lang/Lexer.h
        include/duck/lang/Token.h
        src/lang/Error.cpp
        include/duck/lang/Error.h
        src/lang/AST.cpp
        include/duck/lang/AST.h
        src/lang/Cursor.cpp
        include/duck/lang/Cursor.h
        include/duck/lang/Parser.h
        src/lang/Parser.cpp
)
