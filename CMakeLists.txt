cmake_minimum_required(VERSION 3.13)
project(CompilationPrincple)

set(CMAKE_CXX_STANDARD 14)

add_executable(CompilationPrincple main.cpp Syntax_analysis.h Syntax_analysis.cpp Table.cpp Table.h Error.cpp Error.h Lexical_analysi.cpp Lexical_analysi.h Semantic_analysis.cpp Semantic_analysis.h Interpretation_execution.cpp Interpretation_execution.h)