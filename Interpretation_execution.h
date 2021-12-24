//
// Created by 86156 on 2021-11-18.
//

#ifndef COMPILATIONPRINCPLE_INTERPRETATION_EXECUTION_H
#define COMPILATIONPRINCPLE_INTERPRETATION_EXECUTION_H
#include "Table.h"
#include <vector>
#include <string>
#include <queue>
using namespace std;
/*数据栈*/
struct DataTable{
    DataTable(
        int _NameIndex,
        int _FuncIndex,
        int _ArrayTempIndex,
        int _Value
    ) :
        NameIndex(_NameIndex),
        FuncIndex(_FuncIndex),
        ArrayTempIndex(_ArrayTempIndex),
        Value(_Value){}
    int NameIndex;//传TokenList 的i位
    int FuncIndex;//函数在PcodeList的下标,是函数时才赋值
    int ArrayTempIndex;
    int Value;//变量值
};
extern vector<DataTable> DataStack;
extern vector<int> DataStackIndexTable;

extern int RubbishConst;//存放函数数组形参a[][constexp] exp的值
/*运行栈实现*/
extern int RunStack[5000];
extern int RunStackTop;
/*数据存储表*/
extern int IntDataTable[100000];
extern int IntDataTableTop;
/*数组模板表存储区*/
/*        ______
 *  ->TOP| P(2) |
 *       | U(2) |
 *       |  0   |
 *       | P(1) |
 *       | U(1) |
 *       |  0   |
 *       | Begin|
 *       | dim  |
 *       --------
 */
extern int ArrayTempArea[100000];
extern int ArrayTempTop;
/*数组元素存储区*/
extern int ArraySArea[100000];
extern int ArraySAreaTop;
/* */
extern int IsFunc;
extern vector<int> RunStack_Func;
extern vector<int> WLabStack;
extern vector<int> ILabStack;
extern vector<int> AndLabStack;
extern vector<int> OrLabStack;
extern queue<int> PrintStack;
extern int indata;
//extern int MainReturn;

void Interpretation_execution();
void PCodeListPrint();
#endif //COMPILATIONPRINCPLE_INTERPRETATION_EXECUTION_H
