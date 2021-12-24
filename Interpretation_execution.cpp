//
// Created by 86156 on 2021-11-18.
//
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "Lexical_analysi.h"
#include "Interpretation_execution.h"
#include "Table.h"

using namespace std;
int IsCall = 0;
int PCodePrintFlag = 0;
int ArrayTempBeginIndex = 0;
void PrintDataStack(){
    int n = DataStack.size();
    printf("|%-20s|\n", "DataStack");
    printf("|%-5s|%-15s|%-10s|%-15s|%-10s|\n", "NO", "Name", "FuncIndex", "ArrayTempIndex", "Value");
    for(int i=0; i<=n-1; i++){
        printf("|%-5d|%-15s|%-10d|%-15d|%-10d|\n", i, TokenList[DataStack[i].NameIndex].c_str(), DataStack[i].FuncIndex, DataStack[i].ArrayTempIndex, DataStack[i].Value);
    }
}
/*运行栈操作*/
void RunStackPop(){
    if(RunStackTop == -1) {//栈空
        printf("Empty RunStack!\n");
    }
    else{
        RunStack[RunStackTop] = 0;
        RunStackTop--;
    }

}
void RunStackPushBack(int value){
    if(RunStackTop == 10000-1){
        printf("Full RunStack!\n");
    }
    else{
        RunStack[++RunStackTop] = value;
    }

}
int RunStackSize(){
    int n=0;
    for(int i=RunStackTop; i>=0; i--){
        n++;
    }
    return n;

}
/*数据栈操作*/
void DataStackInsert(int NameIndex, int FuncIndex, int ArrayTempIndex, int Value){/*int ArrayTempIndex,*/
    DataStack.push_back({NameIndex, FuncIndex, ArrayTempIndex, Value});/*ArrayTempIndex,*/
    //PrintDataStack();
}
void DataStackFind(int NameIndex){
    //PrintDataStack();
    for(int j = DataStack.size()-1; j >= 0; j--){
        if(TokenList[NameIndex] == TokenList[DataStack[j].NameIndex]){
            RunStackPushBack(j);
            if(PCodePrintFlag)
                printf("P_DATA_FIND  name : %s\n", TokenList[DataStack[j].NameIndex].c_str());
            break;
        }
    }
}
void DataStackPop(){
    DataStack.pop_back();
}
void DataStackLoc(int Index){
    DataStackIndexTable.push_back(Index);
}
void DataStackReLoc(){
    int i, DataIndexTabN = DataStackIndexTable.size();
    /*考虑分程序索引表为零时,将*/
    if(DataIndexTabN > 0){
        int top = DataStackIndexTable[DataIndexTabN-1];
        int DataStackTabN = DataStack.size();
        for(i=top; i<DataStackTabN; i++){
            DataStackPop();
        }
        //将分程序索引表的栈顶弹出
        DataStackIndexTable.pop_back();
    }
}
/*函数中存在return 之前的reloc只能reloc一层，但是因为函数中block有很多
 * 所以会存在很多个loc 最后只有一个reloc情况，导致无法正常reloc层数
 * 会使层数越来越多，不能退出block中的新生成得变量*/

void DataStackFuncReLoc(int SubProIndex){
    int i, DataIndexTabN = DataStackIndexTable.size();//数据栈顶
    /*考虑分程序索引表为零时,将*/

    if(DataIndexTabN > 0){
        //Pop数据栈
        int FuncDeclIndexInData = DataStackIndexTable[SubProIndex];
        for(int i=DataStack.size()-1; i>=FuncDeclIndexInData; i--){
            DataStackPop();
        }
        //Pop分程序索引表
        for(int i=DataStackIndexTable.size()-1; i>=SubProIndex; i--){
            DataStackIndexTable.pop_back();
        }
    }
}
/*解释执行程序*/
void Interpretation_execution(){
    for(int i=0; i<PCodeList.size(); i++){

        if(PCodeList[i].SubProLevel == 1&&!IsCall){

        }
        else{
            if(PCodePrintFlag)
                printf("%-4d|", i);
            switch (PCodeList[i].PCodeOp){
                case P_ORR :
                    if(RunStackSize() >= 2){
                        int result = RunStack[RunStackTop-1] || RunStack[RunStackTop];
                        RunStackPop();
                        RunStack[RunStackTop] = result;
                    }
                    if(PCodePrintFlag)
                    printf("|P_ORR      |%-5d|%-12d\n", -1, NULL);
                    break;
                case P_AND :
                    if(RunStackSize() >= 2){
                        int result = RunStack[RunStackTop-1] && RunStack[RunStackTop];
                        RunStackPop();
                        RunStack[RunStackTop] = result;
                    }
                    if(PCodePrintFlag)
                    printf("|P_AND       |%-12d|%-12d\n", -1, NULL);
                    break;
                case P_EQL :
                    if(RunStack[RunStackTop-1] == RunStack[RunStackTop]){
                        RunStackPop();
                        RunStack[RunStackTop] = 1;
                        //printf("EQl!\n");
                    }
                    else{
                        RunStackPop();
                        RunStack[RunStackTop] = 0;
                        //printf("NOT EQl\n");
                    }
                    if(PCodePrintFlag)
                    printf("P_EQL %d %d\n", -1, NULL);
                    break;
                case P_NEQ:
                    if(RunStack[RunStackTop-1] != RunStack[RunStackTop]){
                        RunStackPop();
                        RunStack[RunStackTop] = 1;
                        //printf("NEQ!\n");
                    }
                    else{
                        RunStackPop();
                        RunStack[RunStackTop] = 0;
                        //printf("NOT NEQ\n");
                    }
                    if(PCodePrintFlag)
                    printf("P_NEQ %d %d\n", -1, NULL);
                    break;
                case P_LSS:
                    if(RunStack[RunStackTop-1] < RunStack[RunStackTop]){
                        //printf("%d ", RunStack[RunStack.size()-2]);
                        //printf("%d LSS! %d\n", RunStack[RunStack.size()-2], RunStack[RunStack.size()-1]);
                        RunStackPop();
                        RunStack[RunStackTop] = 1;
                    }
                    else{
                        //printf("%d NOT LSS %d\n", RunStack[RunStack.size()-2], RunStack[RunStack.size()-1]);
                        RunStackPop();
                        RunStack[RunStackTop] = 0;
                       // printf("NOT LSS\n");
                    }

                    if(PCodePrintFlag)
                    printf("P_LSS %d %d\n", -1, NULL);
                    break;
                case P_LEQ:
                    if(RunStack[RunStackTop-1] <= RunStack[RunStackTop]){
                        RunStackPop();
                        RunStack[RunStackTop] = 1;
                        //printf("LEQ!\n");
                    }
                    else{
                        RunStackPop();
                        RunStack[RunStackTop] = 0;
                        //printf("NOT LEQ\n");
                    }
                    if(PCodePrintFlag)
                    printf("P_LEQ %d %d\n", -1, NULL);
                    break;
                case P_GRE:
                    if(RunStack[RunStackTop-1] > RunStack[RunStackTop]){
                        RunStackPop();
                        RunStack[RunStackTop] = 1;
                        //printf("GRE!\n");
                    }
                    else{
                        RunStackPop();
                        RunStack[RunStackTop] = 0;
                        //printf("NOT GRE\n");
                    }
                    if(PCodePrintFlag)
                    printf("P_GRE %d %d\n", -1, NULL);
                    break;
                case P_GEQ:
                    if(RunStack[RunStackTop-1] >= RunStack[RunStackTop]){
                        RunStackPop();
                        RunStack[RunStackTop] = 1;
                        //printf("GEQ!\n");
                    }
                    else{
                        RunStackPop();
                        RunStack[RunStackTop] = 0;
                        //printf("NOT GEQ\n");
                    }
                    if(PCodePrintFlag)
                    printf("P_GEQ %d %d\n", -1, NULL);
                    break;
                case P_ADD :
                    if(RunStackSize() >= 2){
                        if(PCodePrintFlag)
                        printf("%d + %d\n", RunStack[RunStackTop-1], RunStack[RunStackTop]);
                        int result = RunStack[RunStackTop-1] + RunStack[RunStackTop];
                        RunStackPop();
                        RunStack[RunStackTop] = result;
                    }
                    if(PCodePrintFlag)
                    printf("P_ADD %d %d\n", -1, NULL);
                    break;
                case P_SUB :
                    if(RunStackSize() >= 2){
                        if(PCodePrintFlag)
                            printf("%d - %d\n", RunStack[RunStackTop-1], RunStack[RunStackTop]);
                        int result = RunStack[RunStackTop-1] - RunStack[RunStackTop];
                        RunStackPop();
                        RunStack[RunStackTop] = result;
                    }
                    if(PCodePrintFlag)
                    printf("P_SUB %d %d\n", -1, NULL);
                    break;
                case P_MUL :
                    if(RunStackSize() >= 2){
                        if(PCodePrintFlag)
                            printf("%d * %d\n", RunStack[RunStackTop-1], RunStack[RunStackTop]);
                        int result = RunStack[RunStackTop-1] * RunStack[RunStackTop];
                        RunStackPop();
                        RunStack[RunStackSize()-1] = result;
                    }
                    if(PCodePrintFlag)
                    printf("P_MUL %d %d\n", -1, NULL);
                    break;
                case P_DIV :
                    if(RunStackSize() >= 2){
                        if(PCodePrintFlag)
                            printf("%d / %d\n", RunStack[RunStackTop-1], RunStack[RunStackTop]);
                        int result = RunStack[RunStackTop-1] / RunStack[RunStackTop];
                        RunStackPop();
                        RunStack[RunStackTop] = result;
                    }
                    if(PCodePrintFlag)
                    printf("P_DIV %d %d\n", -1, NULL);
                    break;
                case P_MOD :
                    if(RunStackSize() >= 2){
                        if(PCodePrintFlag)
                            printf("%d % %d\n", RunStack[RunStackTop-1], RunStack[RunStackTop]);
                        int result = RunStack[RunStackTop-1] % RunStack[RunStackTop];
                        RunStackPop();
                        RunStack[RunStackTop] = result;
                    }
                    //outputRunStack();
                    if(PCodePrintFlag)
                    printf("P_MOD %d %d\n", -1, NULL);
                    break;
                case P_INC :
                    RunStack[RunStackTop] = RunStack[RunStackTop]+1;
                    if(PCodePrintFlag)
                    printf("P_INC %d %d\n", -1, NULL);
                    break;
                case P_DIM :
                    RunStack[RunStackTop] = RunStack[RunStackTop]-1;
                    if(PCodePrintFlag)
                    printf("P_DIM %d %d\n", -1, NULL);
                    break;
                case P_TOMINU:
                    RunStack[RunStackTop] = -RunStack[RunStackTop];
                    break;
                case P_TOPLUS:
                    RunStack[RunStackTop] = RunStack[RunStackTop];
                    break;
                case P_NOT :
                    RunStack[RunStackTop] = !RunStack[RunStackTop];
                    if(PCodePrintFlag)
                    printf("P_NOT %d %d\n", -1, NULL);
                    break;
                case P_LOADI:
                    RunStackPushBack(*(PCodeList[i].SymListAddr));
                    if(PCodePrintFlag)
                    printf("P_LOADI INTCON = %d\n", RunStack[RunStackTop]);
                    break;
                case P_LOAD:
                    RunStackPushBack(*(PCodeList[i].SymListAddr));
                    if(PCodePrintFlag)
                    printf("P_LOAD %d %d\n", -1, RunStack[RunStackTop]);
                    break;
                case P_STO:
                    if(*PCodeList[i].SymListAddr == DECLFLAG){
                        DataStack.back().Value = RunStack[RunStackTop];
                        RunStackPop();
                        if(PCodePrintFlag)
                            printf("P_STO DECL %s = %d\n", TokenList[DataStack.back().NameIndex].c_str(), DataStack.back().Value);
                    }
                    else if(*PCodeList[i].SymListAddr == CALLFLAG){
                        //从运行栈获得对应变量在数据栈中的位置
                        int Value = RunStack[RunStackTop];
                        RunStackPop();
                        int DataStackIndex = RunStack[RunStackTop];
                        RunStackPop();
                        DataStack[DataStackIndex].Value = Value;
                        if (PCodePrintFlag){
                            PrintDataStack();
                            printf("P_STO LVAL %s = %d\n",TokenList[DataStack[DataStackIndex].NameIndex].c_str(), DataStack[DataStackIndex].Value);
                        }
                    }
                    //printf(" PCodeList[i].SymListAddr :%d %d\n", *PCodeList[i].SymListAddr, PCodeList[i].SymListAddr);

                    break;
                case P_STOARY_PARAM:
                    if(1){
                        int j = *PCodeList[i].SymListAddr;
                        DataStack[DataStack.size()-1-j].ArrayTempIndex = RunStack[RunStackTop];
                        RunStackPop();
                        if(PCodePrintFlag)
                            printf("P_STOARY_PARAM PARAM %s AryTemp = %d\n", TokenList[DataStack[DataStack.size()-1-j].NameIndex].c_str(), DataStack[DataStack.size()-1-j].ArrayTempIndex);
                    }
                    break;
                case P_STOINT_PARAM:
                    if(1){
                        int j = *PCodeList[i].SymListAddr;
                        DataStack[DataStack.size()-1-j].Value = RunStack[RunStackTop];
                        RunStackPop();
                        if(PCodePrintFlag)
                            printf("P_STOINT_PARAM PARAM %s = %d\n", TokenList[DataStack[DataStack.size()-1-j].NameIndex].c_str(), DataStack[DataStack.size()-1-j].Value);
                    }
                    break;
                case P_INPUT:
                    if(1){
                        cin >> indata;
                        RunStack[RunStackTop+1] = indata;
                        RunStackTop++;
                    }
                    if(PCodePrintFlag)
                    printf("P_INPUT %d %d\n", -1, indata);
                    break;
                case P_OUTPUT:
                    for(int j=0; j<TokenList[*PCodeList[i].SymListAddr].size(); j++){
                        if(TokenList[*PCodeList[i].SymListAddr][j] == '%'&&
                            TokenList[*PCodeList[i].SymListAddr][j+1] == 'd'
                        ){

                            printf("%d",PrintStack.front());
                            PrintStack.pop();
                            j++;
                        }
                        else if(TokenList[*PCodeList[i].SymListAddr][j] == '\\'&&
                                TokenList[*PCodeList[i].SymListAddr][j+1] == 'n'
                                ){
                            printf("\n");
                            j++;
                        }
                        else{
                            printf("%c", TokenList[*PCodeList[i].SymListAddr][j]);
                        }
                    }
                    if(PCodePrintFlag)
                        printf("P_OUTPUT %d %d\n", -1, NULL);
                    break;
                case P_REPLACE:
                    //返回不是.npos 即存在
                    PrintStack.push(RunStack[RunStackTop]);
                    RunStackPop();
                    if(PCodePrintFlag)
                        printf("P_REPLACE %d %d\n", -1, NULL);
                    break;

                case P_JPC:
                    if(RunStack[RunStackTop] == 0){
                        //pop
                        RunStackPop();
                        i = *PCodeList[i].SymListAddr;
                        if(PCodePrintFlag)
                        printf("P_JPC to Pcodelist[%d]\n", i);
                    }
                    else{
                        RunStackPop();
                        if(PCodePrintFlag)
                            PrintDataStack();
                        //printf("P_JPC Fail!");
                    }

                    break;
                case P_GPI:
                    if(PCodePrintFlag)
                    printf("P_GPI %d %d\n", -1, *(PCodeList[i].SymListAddr));
                    break;
                case P_JMP:
                    i = *PCodeList[i].SymListAddr;
                    if(PCodePrintFlag)
                    printf("P_JMP to Pcodelist[%d]\n", i);
                    break;
                case P_JSR:
                    if(1){
                        int DataStackIndex = RunStack[RunStackTop];
                        RunStackPop();


                        i = DataStack[DataStackIndex].FuncIndex;
                        IsCall = 1;
                    }
                    if(PCodePrintFlag){
                        PrintDataStack();
                        printf("P_JSR to Pcodelist[%d]\n", i);
                    }
                    break;
                case P_GETTOP:
                    *PCodeList[i].SymListAddr = RunStack[RunStackTop];
                    RunStackPop();
                    //printf("ding %d ciding%d\n", RunStack.back(), RunStack[RunStack.size()-2]);
                    if(PCodePrintFlag)
                    printf("P_GETTOP %d %d\n", -1, *PCodeList[i].SymListAddr);
                    break;
                case P_STOP:
                    IsCall = 0;
                    if(PCodePrintFlag)
                    printf("P_STOP %d %d\n", -1, NULL);
                    break;
                case P_RETURN:
                    i = RunStack_Func.back();
                    RunStack_Func.pop_back();
                    //printf("return %d\n", RunStack.back());
                    if(PCodePrintFlag)
                    printf("P_RETURN %d %d\n", -1, NULL);
                    break;
                case P_STR:
                    RunStack_Func.push_back(*PCodeList[i].SymListAddr);
                    if(PCodePrintFlag)
                    printf("P_STR %d %d\n", -1, NULL);
                    break;
                case P_LOADARY_PI:
                    if(1){
                        int DataStackIndex = RunStack[RunStackTop];
                        int ArrayTempIndex = DataStack[DataStackIndex].ArrayTempIndex;
                        int Pi = *PCodeList[i].SymListAddr;
                        RunStackPushBack(ArrayTempArea[ArrayTempIndex+Pi]);
                        if(PCodePrintFlag)
                            printf("P_LOADARY_PI %d %d\n", -1, ArrayTempArea[ArrayTempIndex+Pi]);

                    }
                    break;
                case P_INITCARY_SAREA:
                    if(1){
                        ArraySArea[ArraySAreaTop++] = RunStack[RunStackTop];//将初值加载到数组元素存储区中
                        RunStackPop();
                        if(PCodePrintFlag)
                            printf("P_INITCARY_SAREA %d %d\n", -1, 0);
                    }
                    break;
                case P_INITVARY_SAREA:
                    if(1){
                        if(*PCodeList[i].SymListAddr == Array1){
                            ArraySAreaTop += ArrayTempArea[ArrayTempBeginIndex+3];
                        }
                        else if(*PCodeList[i].SymListAddr == Array2){
                            ArraySAreaTop = ArraySAreaTop + ArrayTempArea[ArrayTempBeginIndex+3]
                                    * ArrayTempArea[ArrayTempBeginIndex+6];
                        }
                        if(PCodePrintFlag)
                            printf("P_INITVARY_SAREA %d %d\n", -1, 0);
                    }
                    break;
                case P_INITARY_TEMPBEGIN:
                    if(1){
                        //RunStackPushBack(ArrayTempTop);//模板表开始位置
                        ArrayTempBeginIndex = ArrayTempTop;
                        ArrayTempArea[ArrayTempTop++] = 0;//维数
                        ArrayTempArea[ArrayTempTop++] = ArraySAreaTop;//开始下标
                        if(PCodePrintFlag)
                            printf("P_INITARY_TEMPBEGIN %d %d\n", -1, 0);
                    }
                    break;
                case P_INITARY_TEMPLVUP:
                    if(1){
                        ArrayTempArea[ArrayTempTop++] = 0;//下界
                        ArrayTempArea[ArrayTempTop++] = RunStack[RunStackTop];//上界
                        RunStackPop();
                        ArrayTempArea[ArrayTempTop++] = 0;//PI
                        //RunStackPushBack(ArrayTempTop);//模板表开始位置
                        //ArrayTempArea[ArrayTempTop++] = 0;//维数
                        //ArrayTempArea[ArrayTempTop++] = 0;//开始下标
                        if(PCodePrintFlag)
                            printf("P_INITARY_TEMPBEGIN %d %d\n", -1, 0);
                    }
                    break;
                case P_NEWARY_TEMP:
                    if(1){
                        int DataStackIndex = RunStack[RunStackTop];
                        RunStackPop();
                        int p1 = ArrayTempArea[DataStack[DataStackIndex].ArrayTempIndex + 4];
                        int v1 = RunStack[RunStackTop]/p1;
                        RunStackPop();
                        int y = ArrayTempArea[DataStack[DataStackIndex].ArrayTempIndex + 6];
                        int x = ArrayTempArea[DataStack[DataStackIndex].ArrayTempIndex + 3];
                        int begin = ArrayTempArea[DataStack[DataStackIndex].ArrayTempIndex + 1];
                        int ArrayTempBeginIndex = ArrayTempTop;
                        int TempBeginIndexinSArea = v1*y+begin;
                        ArrayTempArea[ArrayTempTop++] = 1;//维数
                        ArrayTempArea[ArrayTempTop++] = TempBeginIndexinSArea;//开始位置
                        ArrayTempArea[ArrayTempTop++] = 0;//下界
                        ArrayTempArea[ArrayTempTop++] = y;//上界
                        ArrayTempArea[ArrayTempTop++] = 1;//p1
                        RunStackPushBack(ArrayTempBeginIndex);
                        if(PCodePrintFlag)
                            printf("P_NEW_TEMP %d ARRAYTEMPindex = %d\n", -1, ArrayTempBeginIndex);
                    }
                    break;
                case P_LOADARY_ELM:
                    if(1){
                        ArraySArea[ArraySAreaTop++] = RunStack[RunStackTop];
                        RunStackPop();
                        if(PCodePrintFlag)
                            printf("P_LOADARY_ELM%d %d\n", -1, ArraySArea[ArraySAreaTop-1]);
                    }
                    break;
                case P_LOADARY_TEMP:
                    if(1){
                        int DataStackIndex = RunStack[RunStackTop];
                        RunStackPop();
                        int ArrayTempIndex = DataStack[DataStackIndex].ArrayTempIndex;
                        RunStackPushBack(ArrayTempIndex);
                        if(PCodePrintFlag)
                            printf("P_LOADARY_TEMP%d %d\n", -1, ArrayTempIndex);
                    }
                    break;
                case P_LOADARY_BEGIN:
                    if(1){
                        int DataStackIndex = RunStack[RunStackTop];
                        RunStackPop();
                        int ArrayTempIndex = DataStack[DataStackIndex].ArrayTempIndex;
                        RunStackPushBack(ArrayTempArea[ArrayTempIndex+1]);
                        if(PCodePrintFlag)
                            printf("P_LOADARY_BEGIN%d %d\n", -1, ArrayTempArea[ArrayTempIndex+1]);

                    }
                    break;
                case P_GETARY_PI:
                    if(1){
                        int DataType = *(PCodeList[i].SymListAddr);
                        if(DataType == Array1){
                            ArrayTempArea[ArrayTempBeginIndex+4] = 1;
                        }
                        else if(DataType == Array2){
                            ArrayTempArea[ArrayTempBeginIndex+7] = 1;//i=n=2 p(2) = 1
                            ArrayTempArea[ArrayTempBeginIndex+4] = ArrayTempArea[ArrayTempBeginIndex+6];//计算p(1)值
                        }
                        //int Ui = RunStack[RunStackTop];
                        //RunStackPop();
                        //*(PCodeList[i].SymListAddr) = Ui;
                    }
                    if(PCodePrintFlag)
                        printf("P_GETARY_PI Pi = %d\n", *(PCodeList[i].SymListAddr));
                    break;
                case P_SWP:
                    if(1){
                        int Top = RunStack[RunStackTop];
                        RunStackPop();
                        int SubTop = RunStack[RunStackTop];
                        RunStack[RunStackTop] = Top;
                        RunStackPushBack(SubTop);
                    }
                    if(PCodePrintFlag)
                        printf("P_SWP %d %d\n", -1, NULL);
                    break;
                case P_GETARY_TEMPBEGIN:
                    *(PCodeList[i].SymListAddr) = ArrayTempBeginIndex;
                    if(PCodePrintFlag)
                        printf("P_GETARY_TEMPBEGIN %d %d\n", -1, NULL);
                    break;
                case P_GETARY_VAL:
                    RunStack[RunStackTop] = ArraySArea[RunStack[RunStackTop]];
                    if(PCodePrintFlag)
                        printf("P_GETARY_VAL %d %d\n", -1, NULL);
                    break;
                case P_GETARY_BEGIN:
                    if(1){
                        ArraySAreaTop += RunStack[RunStackTop-1]*RunStack[RunStackTop];
                        RunStackPop();
                        RunStackPop();
                    }
                    if(PCodePrintFlag)
                        printf("P_GETARY_BEGIN %d %d\n", -1, NULL);
                    break;
                case P_STOARY:
                    if(1){
                        int val = RunStack[RunStackTop];
                        RunStackPop();//将对应数组元素的值删除后，当前栈顶是对用数组元素下标
                        ArraySArea[RunStack[RunStackTop]] = val;
                        RunStackPop();
                    }
                    if(PCodePrintFlag)
                        printf("P_STOARY %d %d\n", -1, NULL);
                    break;
                case P_DATA_INSERT:
                    if(1){
                        int Value = RunStack[RunStackTop];
                        RunStackPop();
                        int ArrayTempIndex = RunStack[RunStackTop];
                        RunStackPop();
                        int FuncIndex = RunStack[RunStackTop];
                        RunStackPop();
                        int NameIndex = RunStack[RunStackTop];
                        RunStackPop();
                        DataStackInsert(NameIndex, FuncIndex, ArrayTempIndex, Value);
                        //printf("%s %d\n", TokenList[NameIndex].c_str(), Value);
                    }
                    if(PCodePrintFlag)
                        printf("P_DATA_INSERT %d %d\n", -1, NULL);
                    break;
                case P_DATA_FIND:
                    if(1){
                        //从运行栈获得要找的变量名下标
                        int NameIndex = RunStack[RunStackTop];
                        RunStackPop();
                        DataStackFind(NameIndex);
                    }
                    if(PCodePrintFlag)
                        printf("P_DATA_FIND  \n");
                    break;
                case P_LOAD_DATA_INDEX:
                    if(1){
                        int DataStackIndex = RunStack[RunStackTop];
                        RunStackPop();
                        int Value = DataStack[DataStackIndex].Value;
                        RunStackPushBack(Value);
                        if(PCodePrintFlag)
                            printf("P_LOAD_DATA_INDEX name:  value = %d\n", DataStack[DataStackIndex].Value);
                    }
                    break;
                case P_DATA_LOC:
                    if(1){
                        DataStackLoc(DataStack.size());
                    }
                    if(PCodePrintFlag)
                        printf("P_DATA_LOC \n");
                    break;
                case P_DATA_RELOC:
                    if(1){
                        DataStackReLoc();
                    }
                    if(PCodePrintFlag)
                        printf("P_DATA_ReLoc \n");
                    break;
                case P_DATA_FUNC_LOC:
                    if(1){
                        //记录数据栈分程序表下标
                        RunStack_Func.push_back(DataStackIndexTable.size());
                        DataStackLoc(DataStack.size());
                    }
                    if(PCodePrintFlag)
                        printf("P_DATA_FUNC_LOC \n");
                    break;
                case P_DATA_FUNC_RELOC:
                    if(1){
                        int SubProIndex = RunStack_Func.back();//分程序表的下标，不是数据栈下标
                        RunStack_Func.pop_back();
                        DataStackFuncReLoc(SubProIndex);
                    }
                    if(PCodePrintFlag)
                        printf("P_DATA_FUNC_RELOC \n");
                    break;
                case P_LOAD_REPEAT:
                    if(1){
                        RunStackPushBack(RunStack[RunStackTop]);
                    }
                    if(PCodePrintFlag)
                        printf("P_LOAD_REPEAT \n");
                    break;
            }
        }
    }

}
void PCodeListPrint(){
    printf("%-20c----PCODELIST----%20c\n",'|','|');
    printf("|%-3s|%-5s|%-20s|%-5s|%-12s|\n", "NO", "LineN", "PCODE", "FUNC", "Y");
    for(int i=0; i<PCodeList.size(); i++){
        printf("|%-3d|%-5d", i, PCodeList[i].PCodeLineNum);
        switch (PCodeList[i].PCodeOp){
            case P_ORR:
                printf("|%-20s|%-5d|%-12d|\n", "P_ORR", PCodeList[i].SubProLevel, NULL);
                break;
            case P_AND:
                printf("|%-20s|%-5d|%-12d|\n", "P_AND", PCodeList[i].SubProLevel, NULL);
                break;
            case P_EQL:
                printf("|%-20s|%-5d|%-12d|\n", "P_EQL", PCodeList[i].SubProLevel, NULL);
                break;
            case P_NEQ:
                printf("|%-20s|%-5d|%-12d|\n", "P_NEQ", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LSS:
                printf("|%-20s|%-5d|%-12d|\n", "P_LSS",PCodeList[i].SubProLevel, NULL);
                break;
            case P_LEQ:
                printf("|%-20s|%-5d|%-12d|\n", "P_LEQ", PCodeList[i].SubProLevel, NULL);
                break;
            case P_GRE:
                printf("|%-20s|%-5d|%-12d|\n", "P_GRE", PCodeList[i].SubProLevel, NULL);
                break;
            case P_GEQ:
                printf("|%-20s|%-5d|%-12d|\n", "P_GEQ", PCodeList[i].SubProLevel, NULL);
                break;
            case P_ADD:
                printf("|%-20s|%-5d|%-12d|\n", "P_ADD", PCodeList[i].SubProLevel, NULL);
                break;
            case P_SUB:
                printf("|%-20s|%-5d|%-12d|\n", "P_SUB", PCodeList[i].SubProLevel, NULL);
                break;
            case P_MUL:
                printf("|%-20s|%-5d|%-12d|\n", "P_MUL", PCodeList[i].SubProLevel, NULL);
                break;
            case P_DIV:
                printf("|%-20s|%-5d|%-12d|\n", "P_DIV", PCodeList[i].SubProLevel, NULL);
                break;
            case P_MOD:
                printf("|%-20s|%-5d|%-12d|\n", "P_MOC", PCodeList[i].SubProLevel, NULL);
                break;
            case P_INC:
                printf("|%-20s|%-5d|%-12d|\n", "P_INC",PCodeList[i].SubProLevel, NULL);
                break;
            case P_DIM:
                printf("|%-20s|%-5d|%-12d|\n", "P_DIM", PCodeList[i].SubProLevel, NULL);
                break;
            case P_NOT:
                printf("|%-20s|%-5d|%-12d|\n", "P_NOT", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LOADI:
                printf("|%-20s|%-5d|%-12d|\n", "P_LOADI", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LOAD:
                printf("|%-20s|%-5d|%-12d|\n", "P_LOAD", PCodeList[i].SubProLevel, NULL);
                break;
            case P_STO:
                printf("|%-20s|%-5d|%-12d|\n", "P_STO", PCodeList[i].SubProLevel, NULL);
                break;
            case P_INPUT:
                printf("|%-20s|%-5d|%-12d|\n", "P_INPUT", PCodeList[i].SubProLevel, NULL);
                break;
            case P_REPLACE:
                printf("|%-20s|%-5d|%-12d|\n", "P_REPLACE", PCodeList[i].SubProLevel, NULL);
                break;
            case P_OUTPUT:
                printf("|%-20s|%-5d|%-12d|\n", "P_OUTPUT", PCodeList[i].SubProLevel, NULL);
                break;
            case P_JPC:
                printf("|%-20s|\n", "P_JPC");
                break;
            case P_JMP:
                printf("|%-20s|\n", "P_JMP");
                break;
            case P_JSR:
                printf("|%-20s|\n", "P_JSR");
                break;
            case P_GPI:
                printf("|%-20s|%-5d|%-12d|\n", "P_GPI", PCodeList[i].SubProLevel, NULL);
                break;
            case P_TOPLUS:
                printf("|%-20s|%-5d|%-12d|\n", "P_TOPLUS", PCodeList[i].SubProLevel, NULL);
                break;
            case P_TOMINU:
                printf("|%-20s|%-5d|%-12d|\n", "P_TOMINU", PCodeList[i].SubProLevel, NULL);
                break;
            case P_GETTOP:
                printf("|%-20s|%-5d|%-12d|\n", "P_GETTOP", PCodeList[i].SubProLevel, NULL);
                break;
            case P_STOP:
                printf("|%-20s|%-5d|%-12d|\n", "P_STOP", PCodeList[i].SubProLevel, NULL);
                break;
            case P_RETURN :
                printf("|%-20s|%-5d|%-12d|\n", "P_RETURN", PCodeList[i].SubProLevel, NULL);
                break;
            case P_STR :
                printf("|%-20s|%-5d|%-12d|\n", "P_STR", PCodeList[i].SubProLevel, NULL);
                break;
            case P_DATA_INSERT:
                printf("|%-20s|%-5d|%-12d|\n", "DATA_INSERT", PCodeList[i].SubProLevel, NULL);
                break;
            case P_DATA_FIND:
                printf("|%-20s|%-5d|%-12d|\n", "DATA_FIND", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LOAD_DATA_INDEX:
                printf("|%-20s|%-5d|%-12d|\n", "LOAD_DINDEX", PCodeList[i].SubProLevel, NULL);
                break;
            case P_DATA_LOC:
                printf("|%-20s|%-5d|%-12d|\n", "DATA_LOC", PCodeList[i].SubProLevel, NULL);
                break;
            case P_DATA_RELOC:
                printf("|%-20s|%-5d|%-12d|\n", "DATA_RELOC", PCodeList[i].SubProLevel, NULL);
                break;
            case P_STOINT_PARAM:
                printf("|%-20s|%-5d|%-12d|\n", "P_STOINT_PARAM", PCodeList[i].SubProLevel, NULL);
                break;
            case P_STOARY_PARAM:
                printf("|%-20s|%-5d|%-12d|\n", "P_STOARY_PARAM", PCodeList[i].SubProLevel, NULL);
                break;
            case P_DATA_FUNC_LOC:
                printf("|%-20s|%-5d|%-12d|\n", "P_DATA_FUNC_LOC", PCodeList[i].SubProLevel, NULL);
                break;
            case P_DATA_FUNC_RELOC:
                printf("|%-20s|%-5d|%-12d|\n", "P_DATA_FUNC_RELOC", PCodeList[i].SubProLevel, NULL);
                break;
            case P_GETARY_PI:
                printf("|%-20s|%-5d|%-12d|\n", "P_GETARY_PI", PCodeList[i].SubProLevel, NULL);
                break;
            case P_SWP:
                printf("|%-20s|%-5d|%-12d|\n", "P_SWP", PCodeList[i].SubProLevel, NULL);
                break;
            case P_GETARY_VAL:
                printf("|%-20s|%-5d|%-12d|\n", "P_GETARY_VAL", PCodeList[i].SubProLevel, NULL);
                break;
            case P_GETARY_BEGIN:
                printf("|%-20s|%-5d|%-12d|\n", "P_GETARY_BEGIN", PCodeList[i].SubProLevel, NULL);
                break;
            case P_STOARY:
                printf("|%-20s|%-5d|%-12d|\n", "P_STOARY", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LOADARY_TEMP:
                printf("|%-20s|%-5d|%-12d|\n", "P_LOADARY_TEMP", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LOADARY_PI:
                printf("|%-20s|%-5d|%-12d|\n", "P_LOADARY_PI", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LOADARY_BEGIN:
                printf("|%-20s|%-5d|%-12d|\n", "P_LOADARY_BEGIN", PCodeList[i].SubProLevel, NULL);
                break;
            case P_NEWARY_TEMP:
                printf("|%-20s|%-5d|%-12d|\n", "P_NEWARY_TEMP", PCodeList[i].SubProLevel, NULL);
                break;
        }
    }
}