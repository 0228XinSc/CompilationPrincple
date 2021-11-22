//
// Created by 86156 on 2021-11-18.
//

#include <vector>
#include "Semantic_analysis.h"
#include "Interpretation_execution.h"
#include "Table.h"
using namespace std;
/*表达式*/
void Sem_orr(){
    PCodeList.push_back({P_ORR, -1, NULL});
}
void Sem_and(){
    PCodeList.push_back({P_AND, -1, NULL});
}
void Sem_eql(){
    PCodeList.push_back({P_EQL, -1, NULL});
}
void Sem_neq(){
    PCodeList.push_back({P_NEQ, -1, NULL});
}
void Sem_lss(){
    PCodeList.push_back({P_LSS, -1, NULL});
}
void Sem_leq(){
    PCodeList.push_back({P_LEQ, -1, NULL});
}
void Sem_gre(){
    PCodeList.push_back({P_GRE, -1, NULL});
}
void Sem_geq(){
    PCodeList.push_back({P_GEQ, -1, NULL});
}
void Sem_add(){         //生成一条无操作数的ADD指令
    PCodeList.push_back({P_ADD, -1, NULL});
}
void Sem_sub(){         //生成一条无操作数SUB的指令
    PCodeList.push_back({P_SUB, -1, NULL});
}
void Sem_mul(){         //MULT
    PCodeList.push_back({P_MUL, -1, NULL});
}
void Sem_div(){         //DIV
    PCodeList.push_back({P_DIV, -1, NULL});
}
void Sem_mod(){         //MOD
    PCodeList.push_back({P_MOD, -1, NULL});
}
void Sem_inc(){
    PCodeList.push_back({P_INC, -1, NULL});
}
void Sem_dim(){
    PCodeList.push_back({P_DIM, -1, NULL});
}
void Sem_not(){
    PCodeList.push_back({P_NOT, -1, NULL});
}

void Sem_loadi(int* Attr_NumValueAddr){
    //printf("%d %d\n", *Attr_NumValueAddr, Attr_NumValueAddr);
    PCodeList.push_back({P_LOADI, -1, Attr_NumValueAddr});

}

void Sem_load(int* Attr_VarValueAddr){
    //printf("%d %d\n", *Attr_VarValueAddr, Attr_VarValueAddr);

    PCodeList.push_back({P_LOAD, -1, Attr_VarValueAddr});
}

/*赋值*/
void Sem_sto(int* Attr_ValueAddr){
    //printf("%x\n",Attr_ValueAddr);
    PCodeList.push_back({P_STO, -1, Attr_ValueAddr});
}
/*输入*/
/*将buffer的值放到栈顶*/
void Sem_input(){
    PCodeList.push_back({P_INPUT, -1, NULL});
}
/*输出*/
void Sem_output(int* Attr_TargetAddr){
    PCodeList.push_back({P_OUTPUT, -1, Attr_TargetAddr});
}
/*栈顶判断跳转*/
void Sem_jpc(int* Attr_TargetAddr){
    PCodeList.push_back({P_JPC, -1, Attr_TargetAddr});
}
/*获取跳转标签pcodelist[i]地址*/
void Sem_gpi(int* Attr_TargetAddr){
    *Attr_TargetAddr = PCodeList.size()-1;
    //printf("Attr_TargetAddr%d", *Attr_TargetAddr);
    PCodeList.push_back({P_GPI, -1, Attr_TargetAddr});
}
/*无条件跳转*/
void Sem_jmp(int* Attr_TargetAddr){
    PCodeList.push_back({P_JMP, -1, Attr_TargetAddr});
}