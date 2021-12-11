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
            int _IdentTypeId,
            int _DataTypeId,
            int _LineNumIndex,
            FuncInformationTab* _FunInformation,
            ArrayInformationTab* _ArrayInformation,
            int _IntDataAddr
    ) :
            NameIndex(_NameIndex),
            IdentTypeId(_IdentTypeId),
            DataTypeId(_DataTypeId),
            LineNumIndex(_LineNumIndex),
            FuncInformation(_FunInformation),
            ArrayInformation(_ArrayInformation),
            IntDataAddr(_IntDataAddr){}
    int NameIndex;//传TokenList 的i位置
    int IdentTypeId;
    int DataTypeId;
    int LineNumIndex;//标识符在记录行号数组中的下标
    FuncInformationTab* FuncInformation;
    ArrayInformationTab* ArrayInformation;
    int IntDataAddr;//变量值在数据存储表中的指针
};
extern vector<DataTable> DataStack;

/*运行栈实现*/
extern vector<int> RunStack;
/*数据存储表*/
extern int IntDataTable[200000];
extern int IntDataTableTop;
extern int ArrayStorageArea[200000];
extern int ArrayStorageAreaTop;
/* */
extern int IsFunc;
extern vector<int> RunStack_Func;
extern string PrintfTemp;
extern queue<int> PrintStack;
extern int indata;
//extern int MainReturn;



void Interpretation_execution();

void PCodeListPrint();
#endif //COMPILATIONPRINCPLE_INTERPRETATION_EXECUTION_H
