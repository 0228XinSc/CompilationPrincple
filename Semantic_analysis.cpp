//
// Created by 86156 on 2021-11-18.
//

#include <vector>
#include "Semantic_analysis.h"
#include "Table.h"
using namespace std;
/*表达式*/
void Sem_orr(){
    PCodeList.push_back(P_ORR, -1, -1);
}
void Sem_and(){
    PCodeList.push_back(P_AND, -1, -1);
}
void Sem_eql(){
    PCodeList.push_back(P_EQL, -1, -1);
}
void Sem_neq(){
    PCodeList.push_back(P_NEQ, -1, -1);
}
void Sem_add(){         //生成一条无操作数的ADD指令
    PCodeList.push_back(P_ADD, -1, -1);
}
void Sem_sub(){         //生成一条无操作数SUB的指令
    PCodeList.push_back(P_SUB, -1, -1);
}
void Sem_mul(){         //MULT
    PCodeList.push_back(P_MUL, -1, -1);
}
void Sem_div(){         //DIV
    PCodeList.push_back(P_DIV, -1, -1);
}
void Sem_mod(){         //MOD
    PCodeList.push_back(P_MOD, -1, -1);
}
void Sem_inc(){
    PCodeList.push_back(P_INC, -1, -1);
}
void Sem_dim(){
    PCodeList.push_back(P_DIM, -1, -1);
}
void Sem_not(){
    PCodeList.push_back(P_NOT, -1, -1);
}

void Sem_pushRunStacki(int Attr_NumValue){
    PCodeList.push_back(P_LOADI, -1, Attr_NumValue);
}

void Sem_pushRunStack(int Attr_NumValue){
    PCodeList.push_back(P_LOAD, -1, Attr_NumValue);
}