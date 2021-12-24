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
enum PCodeType{
    P_ORR,
    P_AND,
    P_EQL,
    P_NEQ,
    P_LSS,
    P_LEQ,
    P_GRE,
    P_GEQ,
    P_ADD,
    P_SUB,
    P_MUL,
    P_DIV,
    P_MOD,
    P_NOT,
    P_LOADI,
    P_LOAD,
    P_STO,
    P_STOINT_PARAM,
    P_STOARY_PARAM,
    P_INPUT,
    P_REPLACE,
    P_OUTPUT,
    P_JPC,
    P_JMP,
    P_JSR,
    P_GPI,
    P_TOPLUS,
    P_TOMINU,
    P_GETTOP,
    P_STOP,
    P_RETURN,
    P_STR,
    P_INITARY_TEMPBEGIN,
    P_INITARY_TEMPLVUP,
    P_INITCARY_SAREA,
    P_INITVARY_SAREA,
    P_GETARY_BEGIN,
    P_NEWARY_TEMP,
    P_LOADARY_TEMP,
    P_LOADARY_PI,
    P_LOADARY_BEGIN,
    P_GETARY_PI,
    P_SWP,
    P_GETARY_TEMPBEGIN,
    P_GETARY_VAL,
    P_LOADARY_ELM,
    P_STOARY,
    P_DATA_INSERT,
    P_DATA_FIND,
    P_DATA_LOC,
    P_DATA_RELOC,
    P_DATA_FUNC_LOC,
    P_DATA_FUNC_RELOC,
    P_LOAD_DATA_INDEX,
    P_LOAD_REPEAT
};
/*表格*/
    /*1.函数信息表*/
typedef struct FuncInformationTable{
    int FParmNum;
    int FParmList[500];
    int* FParmInDataIndex[500];
    int PCodeIndex;
    int ReturnIndex;
} FuncInformationTab;
    /*2.数组向量表*/
typedef struct ArrayInformationTable{
    int* ArrayTemp[10];
    int ArrayTop;

    /*        ______
     *  ->TOP| P(2) |
     *       | U(2) |
     *       | 0 |
     *       | P(1) |
     *       | U(1) |
     *       | 0 |
     *       | Begin|
     *       | dim  |
     *       --------
     */
} ArrayInformationTab;

    /*3.主符号表*/
struct MainSymbolTable{
    MainSymbolTable(
            int _NameIndex,
            int _IdentTypeId,
            int _DataTypeId,
            int _LineNumIndex,
            FuncInformationTab* _FunInformation,
            ArrayInformationTab* _ArrayInformation,
            int* _IntDataAddr
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
    int* IntDataAddr;//变量值在数据存储表中的指针
};
    /*4.PCOde表*/
struct PCodeTable{
    PCodeTable(int _PCodeOp, int _SubProLevel, int _PCodeLineNum, int* _SymListAddr):PCodeOp(_PCodeOp),SubProLevel(_SubProLevel),PCodeLineNum(_PCodeLineNum), SymListAddr(_SymListAddr){}
    int PCodeOp;
    int SubProLevel;//所在分程序层次
    int PCodeLineNum;//所在程序中的行号
    int* SymListAddr;//表示相对地址
};
    /*5.数据存储表*/
//extern vector<int>IntDataTable;

    //PCode
extern vector<PCodeTable> PCodeList;

    //栈式符号表
extern vector<MainSymbolTable> StackSymbolTable;
    //分程序索引表
extern vector<int> SubProgramIndexTable;//存储栈中分程序第一个标识符位置


/*符号表操作*/
void SymTabInsert(int NameIndex, int& IdentTypeId, int& DataTypeId, int LineNumIndex, int InsertType, FuncInformationTab* FuncInformation, ArrayInformationTab* _ArrayInformation, int* IntDataAddr);
int SymTabFind(string token, int SymTabFindType);//查表
void SymTabPop();
void SymTabLoc(int Index);
void SymTabReLoc();

#endif //COMPLIER_SYMBOL_TABLE_H
