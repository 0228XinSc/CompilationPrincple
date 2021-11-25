//
// Created by 86156 on 2021-11-18.
//

#ifndef COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
#define COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
#include <vector>
using namespace std;
extern int WLable_inIntTabIndexA;
extern int WLable_inIntTabIndexB;
extern int ILable_inIntTabIndexA;
extern int ILable_inIntTabIndexB;
extern int UnaryOpNum;
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
void Sem_replace(int* Attr_TargetAddr);
/*输出*/
void Sem_output(int* Attr_TargetAddr);
/*栈顶判断跳转*/
void Sem_jpc(int* Attr_TargetAddr);
/*获取跳转目标Pcode下标*/
void Sem_gpi(int* Attr_TargetAddr);
/*无条件跳转*/
void Sem_jmp(int* Attr_TargetAddr);

void Sem_toplus();
void Sem_tominu();

void Sem_gettop(int* Attr_TargetAddr);
void Sem_jsr(int* Attr_TargetAddr);
void Sem_str(int* Attr_TargetAddr);
void Sem_return();
void Sem_stop();
#endif //COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
