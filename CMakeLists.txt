cmake_minimum_required(VERSION 3.13)
project(CompilationPrincple)

set(CMAKE_CXX_STANDARD 14)

add_executable(CompilationPrincple main.cpp Syntax_analysis.h Syntax_analysis.cpp Symbol_Table.cpp Symbol_Table.h Error.cpp Error.h lexical_analysis.cpp lexical_analysis.h)