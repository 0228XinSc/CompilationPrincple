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
int PCodePrintFlag = 1;
string OutputTemp;


void Interpretation_execution(){
    for(int i=0; i<PCodeList.size(); i++){
        if(PCodeList[i].SubProLevel == 1&&!IsCall){

        }
        else{
            switch (PCodeList[i].PCodeOp){
                case P_ORR :
                    if(RunStack.size() >= 2){
                        int result = RunStack[RunStack.size()-2] || RunStack[RunStack.size()-1];
                        RunStack.pop_back();
                        RunStack[RunStack.size()-1] = result;
                    }
                    if(PCodePrintFlag)
                    printf("|P_ORR      |%-5d|%-12d\n", -1, NULL);
                    break;
                case P_AND :
                    if(RunStack.size() >= 2){
                        int result = RunStack[RunStack.size()-2] && RunStack[RunStack.size()-1];
                        RunStack.pop_back();
                        RunStack[RunStack.size()-1] = result;
                    }
                    if(PCodePrintFlag)
                    printf("|P_AND       |%-12d|%-12d\n", -1, NULL);
                    break;
                case P_EQL :
                    if(RunStack[RunStack.size()-2] == RunStack.back()){
                        RunStack.pop_back();
                        RunStack.back() = 1;
                        //printf("EQl!\n");
                    }
                    else{
                        RunStack.pop_back();
                        RunStack.back() = 0;
                        //printf("NOT EQl\n");
                    }
                    if(PCodePrintFlag)
                    printf("P_EQL %d %d\n", -1, NULL);
                    break;
                case P_NEQ:
                    if(RunStack[RunStack.size()-2] != RunStack.back()){
                        RunStack.pop_back();
                        RunStack.back() = 1;
                        //printf("NEQ!\n");
                    }
                    else{
                        RunStack.pop_back();
                        RunStack.back() = 0;
                        //printf("NOT NEQ\n");
                    }
                    if(PCodePrintFlag)
                    printf("P_NEQ %d %d\n", -1, NULL);
                    break;
                case P_LSS:
                    if(RunStack[RunStack.size()-2] < RunStack.back()){
                        //printf("%d ", RunStack[RunStack.size()-2]);
                        //printf("%d LSS! %d\n", RunStack[RunStack.size()-2], RunStack[RunStack.size()-1]);
                        RunStack.pop_back();
                        RunStack.back() = 1;
                    }
                    else{
                        //printf("%d NOT LSS %d\n", RunStack[RunStack.size()-2], RunStack[RunStack.size()-1]);
                        RunStack.pop_back();
                        RunStack.back() = 0;
                       // printf("NOT LSS\n");
                    }

                    if(PCodePrintFlag)
                    printf("P_LSS %d %d\n", -1, NULL);
                    break;
                case P_LEQ:
                    if(RunStack[RunStack.size()-2] <= RunStack.back()){
                        RunStack.pop_back();
                        RunStack.back() = 1;
                        //printf("LEQ!\n");
                    }
                    else{
                        RunStack.pop_back();
                        RunStack.back() = 0;
                        //printf("NOT LEQ\n");
                    }
                    if(PCodePrintFlag)
                    printf("P_LEQ %d %d\n", -1, NULL);
                    break;
                case P_GRE:
                    if(RunStack[RunStack.size()-2] > RunStack.back()){
                        RunStack.pop_back();
                        RunStack.back() = 1;
                        //printf("GRE!\n");
                    }
                    else{
                        RunStack.pop_back();
                        RunStack.back() = 0;
                        //printf("NOT GRE\n");
                    }
                    if(PCodePrintFlag)
                    printf("P_GRE %d %d\n", -1, NULL);
                    break;
                case P_GEQ:
                    if(RunStack[RunStack.size()-2] >= RunStack.back()){
                        RunStack.pop_back();
                        RunStack.back() = 1;
                        //printf("GEQ!\n");
                    }
                    else{
                        RunStack.pop_back();
                        RunStack.back() = 0;
                        //printf("NOT GEQ\n");
                    }
                    if(PCodePrintFlag)
                    printf("P_GEQ %d %d\n", -1, NULL);
                    break;
                case P_ADD :
                    if(RunStack.size() >= 2){
                        if(PCodePrintFlag)
                        printf("%d + %d\n", RunStack[RunStack.size()-2], RunStack[RunStack.size()-1]);
                        int result = RunStack[RunStack.size()-2] + RunStack[RunStack.size()-1];
                        RunStack.pop_back();
                        RunStack.back() = result;
                    }
                    if(PCodePrintFlag)
                    printf("P_ADD %d %d\n", -1, NULL);
                    break;
                case P_SUB :
                    if(RunStack.size() >= 2){
                        if(PCodePrintFlag)
                            printf("%d - %d\n", RunStack[RunStack.size()-2], RunStack[RunStack.size()-1]);
                        int result = RunStack[RunStack.size()-2] - RunStack[RunStack.size()-1];
                        RunStack.pop_back();
                        RunStack[RunStack.size()-1] = result;
                    }
                    if(PCodePrintFlag)
                    printf("P_SUB %d %d\n", -1, NULL);
                    break;
                case P_MUL :
                    if(RunStack.size() >= 2){
                        if(PCodePrintFlag)
                            printf("%d * %d\n", RunStack[RunStack.size()-2], RunStack[RunStack.size()-1]);
                        int result = RunStack[RunStack.size()-2] * RunStack[RunStack.size()-1];
                        RunStack.pop_back();
                        RunStack[RunStack.size()-1] = result;
                    }
                    if(PCodePrintFlag)
                    printf("P_MUL %d %d\n", -1, NULL);
                    break;
                case P_DIV :
                    if(RunStack.size() >= 2){
                        if(PCodePrintFlag)
                            printf("%d / %d\n", RunStack[RunStack.size()-2], RunStack[RunStack.size()-1]);
                        int result = RunStack[RunStack.size()-2] / RunStack[RunStack.size()-1];
                        RunStack.pop_back();
                        RunStack[RunStack.size()-1] = result;
                    }
                    if(PCodePrintFlag)
                    printf("P_DIV %d %d\n", -1, NULL);
                    break;
                case P_MOD :
                    if(RunStack.size() >= 2){
                        if(PCodePrintFlag)
                            printf("%d % %d\n", RunStack[RunStack.size()-2], RunStack[RunStack.size()-1]);
                        int result = RunStack[RunStack.size()-2] % RunStack[RunStack.size()-1];
                        RunStack.pop_back();
                        RunStack[RunStack.size()-1] = result;
                    }
                    //outputRunStack();
                    if(PCodePrintFlag)
                    printf("P_MOD %d %d\n", -1, NULL);
                    break;
                case P_INC :
                    RunStack.back() = RunStack.back()+1;
                    if(PCodePrintFlag)
                    printf("P_INC %d %d\n", -1, NULL);
                    break;
                case P_DIM :
                    RunStack.back() = RunStack.back()-1;
                    if(PCodePrintFlag)
                    printf("P_DIM %d %d\n", -1, NULL);
                    break;
                case P_TOMINU:
                    RunStack.back() = -RunStack.back();
                    break;
                case P_TOPLUS:
                    RunStack.back() = RunStack.back();
                    break;
                case P_NOT :
                    RunStack.back() = !RunStack.back();
                    if(PCodePrintFlag)
                    printf("P_NOT %d %d\n", -1, NULL);
                    break;
                case P_LOADI:
                    RunStack.push_back(*(PCodeList[i].SymListAddr));
                    if(PCodePrintFlag)
                    printf("P_LOADI i = %d\n", RunStack.back());
                    break;
                case P_LOAD:
                    RunStack.push_back(*(PCodeList[i].SymListAddr));
                    if(PCodePrintFlag)
                    printf("P_LOAD %d %d\n", -1, RunStack.back());
                    break;
                case P_STO:
                    //printf("PcodeList[i]Address : %d\n", PCodeList[i].SymListAddr);
                    *(PCodeList[i].SymListAddr) = RunStack.back();
                    RunStack.pop_back();
                    //printf(" PCodeList[i].SymListAddr :%d %d\n", *PCodeList[i].SymListAddr, PCodeList[i].SymListAddr);
                    if(1)
                    printf("P_STO LVAL = %d\n", *(PCodeList[i].SymListAddr));
                    break;
                case P_INPUT:
                    if(1){
                        cin >> indata;
                        RunStack.push_back(indata);
                            //printf("input %d\n",RunStack.back());

                    }

                    //RunStack.push_back(Buffer[BufferTop++]);

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
                    /*返回不是.npos 即存在*/
                    PrintStack.push(RunStack.back());
                    //RunStack.pop_back();
                    if(PCodePrintFlag)
                        printf("P_REPLACE %d %d\n", -1, NULL);
                    break;
                case P_JPC:
                    if(RunStack.back() == 0){
                        RunStack.pop_back();
                        i = *PCodeList[i].SymListAddr;
                        if(PCodePrintFlag)
                        printf("P_JPC to Pcodelist[%d]\n", i);
                    }
                    else{
                        RunStack.pop_back();
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
                    i = *PCodeList[i].SymListAddr-1;
                    IsCall = 1;
                    if(PCodePrintFlag)
                    printf("P_JSR to Pcodelist[%d]\n", i);
                    break;
                case P_GETTOP:
                    *PCodeList[i].SymListAddr = RunStack.back();
                    RunStack.pop_back();
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

                case P_GETARY_PI:
                    if(1){
                        int Ui = RunStack.back();
                        RunStack.pop_back();
                        *(PCodeList[i].SymListAddr) = Ui;
                    }
                    if(PCodePrintFlag)
                        printf("P_GETARY_PI %d %d\n", -1, NULL);
                    break;
                case P_SWP:
                    if(1){
                        int Top = RunStack.back();
                        RunStack.pop_back();
                        int SubTop = RunStack.back();
                        RunStack.back() = Top;
                        RunStack.push_back(SubTop);
                    }
                    if(PCodePrintFlag)
                        printf("P_SWP %d %d\n", -1, NULL);
                    break;
                case P_GETARY_VAL:
                    RunStack.back() = ArrayStorageArea[RunStack.back()];
                    if(PCodePrintFlag)
                        printf("P_GETARY_VAL %d %d\n", -1, NULL);
                    break;
                case P_GETARY_BEGIN:
                    if(1){
                        *(PCodeList[i].SymListAddr) = ArrayStorageAreaTop;
                        int length = RunStack.back()*RunStack[RunStack.size()-2];
                        ArrayStorageAreaTop = ArrayStorageAreaTop+length;
                    }
                    if(PCodePrintFlag)
                        printf("P_GETARY_BEGIN %d %d\n", -1, NULL);
                    break;
                case P_STOARY:
                    if(1){
                        int val = RunStack.back();
                        RunStack.pop_back();//将对应数组元素的值删除，栈顶是对用数组元素下标
                        ArrayStorageArea[RunStack.back()] = val;
                        RunStack.pop_back();
                    }
                    if(PCodePrintFlag)
                        printf("P_STOARY %d %d\n", -1, NULL);
                    break;
            }
            //printf("%d %d\n", PCodeList[i].SubProLevel, *PCodeList[i].SymListAddr);
        }
    }

}
void PCodeListPrint(){
    printf("%-20c----PCODELIST----%20c\n",'|','|');
    printf("|NO |LineN|%-11s|%-5s|%-12s|\n", "PCODE", "X", "Y");
    for(int i=0; i<PCodeList.size(); i++){
        printf("|%-3d|%-5d", i, PCodeList[i].PCodeLineNum);
        switch (PCodeList[i].PCodeOp){
            case P_ORR:
                printf("|P_ORR      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_AND:
                printf("|P_AND      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_EQL:
                printf("|P_EQL      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_NEQ:
                printf("|P_NEQ      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LSS:
                printf("|P_LSS      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LEQ:
                printf("|P_LEQ      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_GRE:
                printf("|P_GRE      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_GEQ:
                printf("|P_GEQ      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_ADD:
                printf("|P_ADD      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_SUB:
                printf("|P_SUB      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_MUL:
                printf("|P_MUL      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_DIV:
                printf("|P_DIV      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_MOD:
                printf("|P_MOC      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_INC:
                printf("|P_INC      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_DIM:
                printf("|P_DIM      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_NOT:
                printf("|P_NOT      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LOADI:
                printf("|P_LOADI    |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_LOAD:
                printf("|P_LOAD     |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_STO:
                printf("|P_STO      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_INPUT:
                printf("|P_INPUT    |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_REPLACE:
                printf("|P_REPLACE  |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_OUTPUT:
                printf("|P_OUTPUT   |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_JPC:
                printf("|P_JPC      |\n");
                break;
            case P_JMP:
                printf("|P_JMP      |\n");
                break;
            case P_JSR:
                printf("|P_JSR      |\n");
                break;
            case P_GPI:
                printf("|P_GPI      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_TOPLUS:
                printf("|P_TOPLUS   |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_TOMINU:
                printf("|P_TOMINU   |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_GETTOP:
                printf("|P_GETTOP   |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_STOP:
                printf("|P_STOP     |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_RETURN :
                printf("|P_RETURN   |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
            case P_STR :
                printf("|P_STR      |%-5d|%-12d|\n", PCodeList[i].SubProLevel, NULL);
                break;
        }
    }
}