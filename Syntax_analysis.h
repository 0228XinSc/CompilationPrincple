//
// Created by 86156 on 2021-10-10.
//

#ifndef COMPLIER_SYNTAX_ANALYSIS_H
#define COMPLIER_SYNTAX_ANALYSIS_H
#include <vector>
#include "Table.h"
void CompUnit();        //编译单元
void ConstDecl();       //常量声明
void BType();           //基本类型
void ConstDef();        //常数定义
void Ident();           //标识符
void ConstExp();        //常量表达式
void ConstInitVal();    //常量初值
void VarDecl();         //变量声明
void VarDef();          //变量定义
void InitVal();         //变量初值
void Exp();             //表达式
void FuncDef();         //函数定义
void FuncType();        //函数类型
void FuncFParams(int& FParmNum, OtherSymbol* ExtraSymbol);     //函数形参表
void FuncFParam(int& DataType);      //函数形参
void MainFuncDef();     //主函数定义
void Block();           //语句块定义
void Stmt();            //语句
void FormatString(int& FormatCNum);    //字符串
void LVal(int& IdentTypeIdTemp);            //左值表达式
void Cond();            //条件表达式
void LOrExp();          //逻辑或表达式
void LAndExp();         //逻辑与表达式
void EqExp();           //相等性表达式
void RelExp();          //关系表达式
void AddExp();          //加减表达式
void MulExp();          //乘除模表达式
void UnaryExp();        //一元表达式
void UnaryOp();         //单目运算符
void PrimaryExp();      //基本表达式
void Number();          //数字
void IntConst();        //整数
void FuncRParams(int& RParmNum, int FParmList[], int FParamNum);     //函数实参表


#endif //COMPLIER_SYNTAX_ANALYSIS_H
