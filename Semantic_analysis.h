//
// Created by 86156 on 2021-11-18.
//

#ifndef COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
#define COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
#include <vector>
using namespace std;

/*表达式*/
void Sem_orr();
void Sem_and();
void Sem_eql();
void Sem_neq();
void Sem_lss();
void Sem_leq();
void Sem_gre();
void Sem_geq();
void Sem_add();
void Sem_sub();
void Sem_mul();
void Sem_div();
void Sem_mod();

void Sem_inc();
void Sem_dim();
void Sem_not();

void Sem_loadi(int* Attr_NumValueAddr);
void Sem_load(int* Attr_VarValueAddr);

/*赋值*/
void Sem_sto(int* Attr_ValueAddr);
/*输入*/
void Sem_input();
/*输出*/
void Sem_output(int* Attr_TargetAddr);
/*栈顶判断跳转*/
void Sem_jpc(int* Attr_TargetAddr);
/*获取跳转目标Pcode下标*/
void Sem_gpi(int* Attr_TargetAddr);
/*无条件跳转*/
void Sem_jmp(int* Attr_TargetAddr);
#endif //COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
