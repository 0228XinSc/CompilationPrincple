//
// Created by 86156 on 2021-11-18.
//

#include <vector>
#include "Lexical_analysi.h"
#include "Semantic_analysis.h"
#include "Interpretation_execution.h"
#include "Table.h"
using namespace std;
/*表达式*/
void Sem_orr(){
    PCodeList.push_back({P_ORR, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_and(){
    PCodeList.push_back({P_AND, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_eql(){
    PCodeList.push_back({P_EQL, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_neq(){
    PCodeList.push_back({P_NEQ, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_lss(){
    PCodeList.push_back({P_LSS, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_leq(){
    PCodeList.push_back({P_LEQ, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_gre(){
    PCodeList.push_back({P_GRE, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_geq(){
    PCodeList.push_back({P_GEQ, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_add(){         //生成一条无操作数的ADD指令
    PCodeList.push_back({P_ADD, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_sub(){         //生成一条无操作数SUB的指令
    PCodeList.push_back({P_SUB, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_mul(){         //MULT
    PCodeList.push_back({P_MUL, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_div(){         //DIV
    PCodeList.push_back({P_DIV, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_mod(){         //MOD
    PCodeList.push_back({P_MOD, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_not(){
    PCodeList.push_back({P_NOT, IsFunc, SymbolListLine[CurSymPos], NULL});
}

void Sem_loadi(int* Attr_NumValueAddr){
    //printf("%d %d\n", *Attr_NumValueAddr, Attr_NumValueAddr);
    PCodeList.push_back({P_LOADI, IsFunc, SymbolListLine[CurSymPos], Attr_NumValueAddr});

}

void Sem_load(int* Attr_VarValueAddr){
    //printf("%d %d\n", *Attr_VarValueAddr, Attr_VarValueAddr);

    PCodeList.push_back({P_LOAD, IsFunc, SymbolListLine[CurSymPos], Attr_VarValueAddr});
}

/*赋值*/
void Sem_sto(int* Attr_ValueAddr){
    //printf("%x\n",Attr_ValueAddr);
    PCodeList.push_back({P_STO, IsFunc, SymbolListLine[CurSymPos], Attr_ValueAddr});
}
/*输入*/
/*将buffer的值放到栈顶*/
void Sem_input(){
    PCodeList.push_back({P_INPUT, IsFunc, SymbolListLine[CurSymPos], NULL});
}
/*输出*/
void Sem_replace(int* Attr_TargetAddr){
    PCodeList.push_back({P_REPLACE, IsFunc, SymbolListLine[CurSymPos], Attr_TargetAddr});
}
/*输出*/
void Sem_output(int* Attr_TargetAddr){
    PCodeList.push_back({P_OUTPUT, IsFunc, SymbolListLine[CurSymPos], Attr_TargetAddr});
}
/*栈顶判断跳转*/
void Sem_jpc(int* Attr_TargetAddr){
    PCodeList.push_back({P_JPC, IsFunc, SymbolListLine[CurSymPos], Attr_TargetAddr});
}
/*获取跳转标签pcodelist[i]地址*/
void Sem_gpi(int* Attr_TargetAddr){
    *Attr_TargetAddr = PCodeList.size()-1;
    //printf("Attr_TargetAddr%d", *Attr_TargetAddr);
    PCodeList.push_back({P_GPI, IsFunc, SymbolListLine[CurSymPos], Attr_TargetAddr});
}
/*无条件跳转*/
void Sem_jmp(int* Attr_TargetAddr){
    PCodeList.push_back({P_JMP, IsFunc, SymbolListLine[CurSymPos], Attr_TargetAddr});
}
/*无条件跳转*/
void Sem_jsr(int* Attr_TargetAddr){
    PCodeList.push_back({P_JSR, IsFunc, SymbolListLine[CurSymPos], Attr_TargetAddr});
}
/*break*/
/*void Sem_break(){

}*/
/*continue*/

void Sem_toplus(){
    PCodeList.push_back({P_TOPLUS, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_tominu(){
    PCodeList.push_back({P_TOMINU, IsFunc, SymbolListLine[CurSymPos], NULL});
}

void Sem_gettop(int* Attr_TargetAddr){
    PCodeList.push_back({P_GETTOP, IsFunc, SymbolListLine[CurSymPos], Attr_TargetAddr});
}
void Sem_return(){
    PCodeList.push_back({P_RETURN, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_stop(){
    PCodeList.push_back({P_STOP, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_str(int* Attr_TargetAddr){
    PCodeList.push_back({P_STR, IsFunc, SymbolListLine[CurSymPos], Attr_TargetAddr});
}
void Sem_getAry_pi(int* Attr_TargetAddr){
    PCodeList.push_back({P_GETARY_PI, IsFunc, SymbolListLine[CurSymPos], Attr_TargetAddr});
}
void Sem_swp(){
    PCodeList.push_back({P_SWP, IsFunc, SymbolListLine[CurSymPos], NULL});
}
void Sem_getAry_val(){
    PCodeList.push_back({P_GETARY_VAL, SymbolListLine[CurSymPos], IsFunc, NULL});
}
void Sem_getAry_begin(int* Attr_TargetAddr){
    PCodeList.push_back({P_GETARY_BEGIN, IsFunc, SymbolListLine[CurSymPos], Attr_TargetAddr});
}
void Sem_stoAry(){
    PCodeList.push_back({P_STOARY, IsFunc, SymbolListLine[CurSymPos], NULL});
}

