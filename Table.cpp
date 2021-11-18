//
// Created by 86156 on 2021-10-19.
//
#include <stdio.h>
#include "Table.h"
#include "Lexical_analysi.h"
#include "Error.h"

/*符号表操作*/

/*填表*/
void SymTabInsert(int NameIndex, int& IdentTypeId, int &DataTypeId, int LineNumIndex,
        int InsertType, FuncInformationTab* FuncInformation, int IntValue){
    /*声明填表*/
    if(InsertType == DECLFLAG){
        if(SymTabFind(TokenList[NameIndex], DECLFLAG) == -1){
            StackSymbolTable.push_back({NameIndex, IdentTypeId, DataTypeId, LineNumIndex, FuncInformation, IntValue});
        }
        else if(SymTabFind(TokenList[NameIndex], DECLFLAG) >= 0){
            /*重复声明*/
            Error(EB);
        }
    }
    else if(InsertType == CALLFLAG){
        int StackSymPos = 0;
        if((StackSymPos = SymTabFind(TokenList[NameIndex], CALLFLAG)) >= 0){
            IdentTypeId = StackSymbolTable[StackSymPos].IdentTypeId;
            DataTypeId = StackSymbolTable[StackSymPos].DataTypeId;
        }
        else if(SymTabFind(TokenList[NameIndex], CALLFLAG) == -1){
            Error(EC);
        }
    }
    /*打印符号表*/
    /*printf("-----------------------------SYMBOLLIST------------------------------\n");
    printf("-------------------------------INSERT--------------------------------\n");
    int n = StackSymbolTable.size();
    for(int i=0; i<n; i++){
        printf("%-20s%-20d%-20d\n", TokenList[StackSymbolTable[i].NameIndex].c_str(), StackSymbolTable[i].DataTypeId, StackSymbolTable[i].IdentTypeId);
    }*/

}
/*查表*/
int SymTabFind(string token, int SymTabFindType){
    int i, n = StackSymbolTable.size();
    //栈式符号表为空时,返回-1表示没查找到对应标识符
    if(n == 0){
        return -1;
    }
    /*声明，判断是否重复声明*/
    if(SymTabFindType == DECLFLAG){
        int SubProIndex = SubProgramIndexTable.size()-1;
        /*查找标识符所在作用域是否出现同名标识符*/
        /*考虑没有分程序只有全局变量的情况，即分程序索引表为空,只扫描栈式符号表即可*/
        if(SubProgramIndexTable.size() == 0){
            for(i=n-1; i>=0; i--){
                if(TokenList[StackSymbolTable[i].NameIndex] == token){
                    return i;//查找到对应标识符，返回其在栈式符号表的位置
                }
            }
        }
        /*有分程序索引*/
        else{
            for(i=n-1; i>=SubProgramIndexTable[SubProIndex]; i--){
                if(TokenList[StackSymbolTable[i].NameIndex] == token){
                    return i;//查找到对应标识符，返回其在栈式符号表的位置
                }
            }
        }

    }
    /*调用，判断该标识符是否已经声明，若声明则将*/
    else if(SymTabFindType == CALLFLAG){
        for(i = n-1; i>=0; i--){
            if(TokenList[StackSymbolTable[i].NameIndex] == token){
                /*找到之前的声明，将声明的信息填入到当前符号表调用位置的符号表项中*/
                return i;
            }
        }
    }
    return -1;
}
/*删除符号表栈顶内容*/
void SymTabPop(){

    StackSymbolTable.pop_back();
}
/*定位*/
/*将分程序索引表的顶端填入当前标识符所在栈的位置下标,函数的第一个形参标识符*/
void SymTabLoc(int Index){
    //printf("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkLOC%d", SymbolListLine[CurSymPos]);
    SubProgramIndexTable.push_back(Index);
}
/*重定位*/
/*清除刚刚被编译的分程序在栈式符号表中的记录*/
void SymTabReLoc(){
    int i, SubProIndexTabN = SubProgramIndexTable.size();
    /*考虑分程序索引表为零时,将*/
    if(SubProIndexTabN > 0){
        int top = SubProgramIndexTable[SubProIndexTabN-1];
        int StackTableN = StackSymbolTable.size();
        for(i=top; i<StackTableN; i++){
            SymTabPop();
        }
        //将分程序索引表的栈顶弹出
        SubProgramIndexTable.pop_back();
    }


    /*打印符号表*/
    /*printf("%d", SymbolListLine[CurSymPos]);
    printf("-----------------------------SYMBOLLIST------------------------------\n");
    printf("----------------------------------POP----------------------------------\n");
    int n = StackSymbolTable.size();
    for(int i=0; i<n; i++){
        printf("%-20s%-20d%-20d\n", TokenList[StackSymbolTable[i].NameIndex].c_str(), StackSymbolTable[i].DataTypeId, StackSymbolTable[i].IdentTypeId);
    }*/

}