//
// Created by 86156 on 2021-10-19.
//
#include <string>
#include <stack>
#include <vector>
#ifndef COMPLIER_SYMBOL_TABLE_H
#define COMPLIER_SYMBOL_TABLE_H

#define DECLFLAG 1
#define CALLFLAG 2
using namespace std;

enum IdentType{
    Func = 1, Const, Var, Parm
};
enum DataType{
    Int = 0, Array1, Array2, Void
};
/*函数信息表*/
typedef struct FuncInformationTable{
    int FParmNum;
    int FParmList[500];
} FuncInformationTab;
/*数组向量表*/

/*整型数值表*/
typedef struct IntInformationTable{
    int IntValue;
} IntInformationTab;
/*主符号表*/
struct MainSymbolTable{
    MainSymbolTable(
            int _NameIndex,
            int _IdentTypeId,
            int _DataTypeId,
            int _LineNumIndex,
            FuncInformationTab* _FunInformation,
            IntInformationTab* _IntValue
            ) :
            NameIndex(_NameIndex),
            IdentTypeId(_IdentTypeId),
            DataTypeId(_DataTypeId),
            LineNumIndex(_LineNumIndex),
            FuncInformationTab(_FunInformation),
            IntInformationTab(_IntValue){}
    int NameIndex;//传TokenList 的i位置
    int IdentTypeId;
    int DataTypeId;
    int LineNumIndex;//标识符在记录行号数组中的下标
    FuncInformationTab* FuncInformation;
    IntInformationTab* IntValue;
};


/*表格*/

//栈式符号表
extern vector<MainSymbolTable> StackSymbolTable;
//分程序索引表
extern vector<int> SubProgramIndexTable;//存储栈中分程序第一个标识符位置

/*失效区*/
//将删除的分程序符号表存入失效区中，有助于构造交叉引用表，或者帮助进行运行时的错误诊断

//符号表操作
void SymTabInsert(int NameIndex, int& IdentTypeId, int& DataTypeId, int LineNumIndex, int InsertType, FuncInformationTab* FuncInformation);
int SymTabFind(string token, int SymTabFindType);//查表
void SymTabPop();
void SymTabLoc(int Index);
void SymTabReLoc();


#endif //COMPLIER_SYMBOL_TABLE_H
