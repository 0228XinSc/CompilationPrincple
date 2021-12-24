//
// Created by 86156 on 2021-11-18.
//

#ifndef COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
#define COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
#include <vector>
#include <string>
#include "Table.h"
using namespace std;
extern int WLable_inIntTabIndexA;
extern int WLable_inIntTabIndexB;
extern int ILable_inIntTabIndexA;
extern int ILable_inIntTabIndexB;
extern int AndLable_inIntTabIndexA;
extern int AndLable_inIntTabIndexB;
extern int OrLable_inIntTabIndexA;
extern int OrLable_inIntTabIndexB;
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
void Sem_not();
void Sem_loadi(int* Attr_NumValueAddr);
void Sem_load(int* Attr_VarValueAddr);
/*赋值*/
void Sem_sto(int* Attr_ValueAddr);
/*给形参赋实参值*/
void Sem_stoInt_param(int* Attr_ValueAddr);
/*给形参赋实参值*/
void Sem_stoAry_param(int* Attr_ValueAddr);
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
/*取正*/
void Sem_toplus();
/*取负*/
void Sem_tominu();
/*获取运行栈栈顶值*/
void Sem_gettop(int* Attr_TargetAddr);
/**/
void Sem_jsr();
/*存储返回地址*/
void Sem_str(int* Attr_TargetAddr);
/*返回调用地址*/
void Sem_return();
/*用来不执行函数声明里的语句*/
void Sem_stop();
/*初始化模板表对应数组存储的长度*/
void Sem_initCAry_sArea();
/*初始化模板表对应数组存储的长度*/
void Sem_initVAry_sArea(int* Attr_TargetAddr);
/*在执行时初始化模板表上下界以及pi*/
void Sem_initAry_tempbegin();
/*在执行时初始化模板表上下界以及pi*/
void Sem_initAry_templvup();
/*根据二维数组，新建一个临时模板表，提供给形参的一维数组*/
void Sem_newAry_temp();
/*加载元素到存储区中*/
void Sem_loadAry_elm();
/*加载数组模板ArrayTempIndex*/
void Sem_LoadAry_temp();
/*加载数组模板中的P(i)*/
void Sem_LoadAry_pi(int* Attr_TargetAddr);
/*加载数组模板中的开始地址*/
void Sem_LoadAry_begin();
/*计算数组模板中的P(i)*/
void Sem_getAry_pi(int* Attr_TargetAddr);
/*交换运行栈顶和次栈顶*/
void Sem_swp();
/*获得模板表在temparea的位置*/
void Sem_getAry_tempBegin(int* Attr_TargetAddr);
/*将栈顶值作为索引获得IntData存储中的值， 其实就是获得数组对应元素*/
void Sem_getAry_val();
/*将栈顶和次站顶的数组对应维数大小相乘获得数组大小，将开始地址赋给模板中的开始地址位置*/
void Sem_getAry_begin(int* Attr_TargetAddr);
/*对数组元素赋值*/
void Sem_stoAry();

void Sem_dataStackInsert();
void Sem_dataStackFind();//查表
void Sem_dataStackLoc();
void Sem_dataStackReLoc();
void Sem_dataStackFuncLoc();
void Sem_dataStackFuncReLoc();

//获取数据栈对应下标的元素的值，加载到运行栈中
void Sem_loadDataIndex();
void Sem_loadRepeat();

#endif //COMPILATIONPRINCPLE_SEMANTIC_ANALYSIS_H
