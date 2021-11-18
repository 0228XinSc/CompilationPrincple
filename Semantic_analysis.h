//
// Created by 86156 on 2021-11-18.
//

#ifndef COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
#define COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H

/*表达式*/
void Sem_orr();
void Sem_and();
void Sem_add();
void Sem_sub();
void Sem_mul();
void Sem_div();
void Sem_mod();

void Sem_inc();
void Sem_dim();
void Sem_not();

void Sem_pushRunStacki(int Attr_NumValue);
void Sem_pushRunStack(int Attr_NumValue);

#endif //COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
