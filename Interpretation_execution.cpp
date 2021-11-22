//
// Created by 86156 on 2021-11-18.
//
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "Lexical_analysi.h"
#include "Interpretation_execution.h"
#include "Table.h"
using namespace std;

void outputRunStack(){
    if(RunStack.size()>=2)
        printf("top:%d subtop:%d\n", RunStack[RunStack.size()-1], RunStack[RunStack.size()-2]);
}

void Interpretation_execution(){
    for(int i=0; i<PCodeList.size(); i++){
        switch (PCodeList[i].PCodeOp){
            case P_ORR :
                if(RunStack.size() >= 2){
                    int result = RunStack[RunStack.size()-2] || RunStack[RunStack.size()-1];
                    RunStack.pop_back();
                    RunStack[RunStack.size()-1] = result;
                }
                printf("P_ORR %d %d\n", -1, NULL);
                break;
            case P_AND :
                if(RunStack.size() >= 2){
                    int result = RunStack[RunStack.size()-2] && RunStack[RunStack.size()-1];
                    RunStack.pop_back();
                    RunStack[RunStack.size()-1] = result;
                }
                printf("P_AND %d %d\n", -1, NULL);
                break;
            case P_EQL :
                if(RunStack[RunStack.size()-2] == RunStack.back()){
                    RunStack.pop_back();
                    RunStack.back() = 1;
                    printf("EQl!\n");
                }
                else{
                    RunStack.pop_back();
                    RunStack.back() = 0;
                    printf("NOT EQl\n");
                }
                printf("P_EQL %d %d\n", -1, NULL);
                break;
            case P_NEQ:
                if(RunStack[RunStack.size()-2] != RunStack.back()){
                    RunStack.pop_back();
                    RunStack.back() = 1;
                    printf("NEQ!\n");
                }
                else{
                    RunStack.pop_back();
                    RunStack.back() = 0;
                    printf("NOT NEQ\n");
                }
                printf("P_NEQ %d %d\n", -1, NULL);
                break;
            case P_LSS:
                if(RunStack[RunStack.size()-2] < RunStack.back()){
                    RunStack.pop_back();
                    RunStack.back() = 1;
                    printf("LSS!\n");
                }
                else{
                    RunStack.pop_back();
                    RunStack.back() = 0;
                    printf("NOT LSS\n");
                }
                printf("P_LSS %d %d\n", -1, NULL);
                break;
            case P_LEQ:
                if(RunStack[RunStack.size()-2] <= RunStack.back()){
                    RunStack.pop_back();
                    RunStack.back() = 1;
                    printf("LEQ!\n");
                }
                else{
                    RunStack.pop_back();
                    RunStack.back() = 0;
                    printf("NOT LEQ\n");
                }
                printf("P_LEQ %d %d\n", -1, NULL);
                break;
            case P_GRE:
                if(RunStack[RunStack.size()-2] > RunStack.back()){
                    RunStack.pop_back();
                    RunStack.back() = 1;
                    printf("GRE!\n");
                }
                else{
                    RunStack.pop_back();
                    RunStack.back() = 0;
                    printf("NOT GRE\n");
                }
                printf("P_GRE %d %d\n", -1, NULL);
                break;
            case P_GEQ:
                if(RunStack[RunStack.size()-2] >= RunStack.back()){
                    RunStack.pop_back();
                    RunStack.back() = 1;
                    printf("GEQ!\n");
                }
                else{
                    RunStack.pop_back();
                    RunStack.back() = 0;
                    printf("NOT GEQ\n");
                }
                printf("P_GEQ %d %d\n", -1, NULL);
                break;
            case P_ADD :
                if(RunStack.size() >= 2){
                    int result = RunStack[RunStack.size()-2] + RunStack[RunStack.size()-1];
                    RunStack.pop_back();
                    RunStack.back() = result;
                }
                printf("P_ADD %d %d\n", -1, NULL);
                break;
            case P_SUB :
                if(RunStack.size() >= 2){
                    int result = RunStack[RunStack.size()-2] - RunStack[RunStack.size()-1];
                    RunStack.pop_back();
                    RunStack[RunStack.size()-1] = result;
                }
                printf("P_SUB %d %d\n", -1, NULL);
                break;
            case P_MUL :
                if(RunStack.size() >= 2){
                    int result = RunStack[RunStack.size()-2] * RunStack[RunStack.size()-1];
                    RunStack.pop_back();
                    RunStack[RunStack.size()-1] = result;
                }
                printf("P_MUL %d %d\n", -1, NULL);
                break;
            case P_DIV :
                if(RunStack.size() >= 2){
                    int result = RunStack[RunStack.size()-2] / RunStack[RunStack.size()-1];
                    RunStack.pop_back();
                    RunStack[RunStack.size()-1] = result;
                }
                printf("P_DIV %d %d\n", -1, NULL);
                break;
            case P_MOD :
                if(RunStack.size() >= 2){
                    int result = RunStack[RunStack.size()-2] % RunStack[RunStack.size()-1];
                    RunStack.pop_back();
                    RunStack[RunStack.size()-1] = result;
                }
                outputRunStack();
                printf("P_MOD %d %d\n", -1, NULL);
                break;
            case P_INC :
                RunStack.back() = RunStack.back()+1;
                printf("P_INC %d %d\n", -1, NULL);
                break;
            case P_DIM :
                RunStack.back() = RunStack.back()-1;
                printf("P_DIM %d %d\n", -1, NULL);
                break;
            case P_NOT :
                RunStack.back() = !RunStack.back();
                printf("P_NOT %d %d\n", -1, NULL);
                break;
            case P_LOADI:
                RunStack.push_back(*(PCodeList[i].SymListAddr));

                printf("P_LOADI %d %d\n", -1, RunStack.back());
                break;
            case P_LOAD:
                RunStack.push_back(*(PCodeList[i].SymListAddr));
                printf("P_LOAD %d %d\n", -1, RunStack.back());
                break;
            case P_STO:
                //printf("PcodeList[i]Address : %d\n", PCodeList[i].SymListAddr);
                *(PCodeList[i].SymListAddr) = RunStack.back();
                RunStack.pop_back();
                //printf(" PCodeList[i].SymListAddr :%d %d\n", *PCodeList[i].SymListAddr, PCodeList[i].SymListAddr);
                printf("P_STO %d %d\n", -1, *(PCodeList[i].SymListAddr));
                break;
            case P_INPUT:
                RunStack.push_back(Buffer[BufferTop++]);
                printf("P_INPUT %d %d\n", -1, NULL);
                break;
            case P_OUTPUT:
                /*返回不是.npos 即存在*/

                if(!TokenList[*PCodeList[i].SymListAddr].empty()){
                    int k = *PCodeList[i].SymListAddr;
                    //cout << TokenList[k] << endl;
                    //cout << k << endl;

                    if(TokenList[k].find("%d") == -1){
                        int i;

                        for(i = 0; i<(TokenList[k]).size(); i++){

                            if(
                                    TokenList[k][i] == '\\' &&
                                    TokenList[k][i+1] == 'n'){
                                i++;
                                printf("\n");
                            }
                            else{
                                printf("%c", TokenList[k][i]);
                            }
                        }
                    }
                    if(TokenList[k].find("%d") != -1){
                        int index = (int)TokenList[k].find("%d");
                        stringstream ss ;
                        ss << RunStack.back();
                        string temp = ss.str();
                        TokenList[k]=TokenList[k].replace(index,2,temp); //用substr的指定字符串替换str指定字符串
                        //cout << &RunStack.back() <<endl;
                        //cout<<TokenList[k]<<endl;
                        //cout << k << endl;
                    }
                    printf("P_OUTPUT %d %d\n", -1, NULL);
                }


                break;
            case P_JPC:
                if(RunStack.back() == 0){
                    i = *PCodeList[i].SymListAddr;
                    printf("P_JPC to Pcodelist[%d]\n", i);
                }
                else{
                    //printf("P_JPC Fail!");
                }
                break;
            case P_GPI:

                printf("P_GPI %d %d\n", -1, *(PCodeList[i].SymListAddr));
                break;
            case P_JMP:
                i = *PCodeList[i].SymListAddr;
                printf("P_JMP to Pcodelist[%d]\n", i);
                break;

        }
        //printf("%d %d\n", PCodeList[i].SubProLevel, *PCodeList[i].SymListAddr);
    }
};