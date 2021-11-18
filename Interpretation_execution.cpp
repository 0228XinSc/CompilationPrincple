//
// Created by 86156 on 2021-11-18.
//
#include <vector>
#include <stdio.h>
#include "Interpretation_execution.h"
#include "Table.h"
using namespace std;

/*运行栈实现*/
vector<int> RunStack;

void Interpretation_execution(){
    for(int i=0; i<PCodeList.size(); i++){
        switch (PCodeList[i].PCodeOp){
            case P_ADD :
                printf("P_ADD ");
                break;
            case P_SUB :
                printf("P_SUB ");
                break;
            case P_MUL :
                printf("P_MUL ");
                break;
            case P_DIV :
                printf("P_DIV ");
                break;
            case P_MOD :
                printf("P_MOD ");
                break;
            case P_INC :
                printf("P_INC ");
                break;
            case P_DIM :
                printf("P_DIM ");
                break;
            case P_NOT :
                printf("P_NOT ");
                break;
            case P_LOADI:
                printf("P_LOADI ");
                break;
            case P_LOAD:
                printf("P_LOAD ");
                break;
        }
        printf("%d %d\n", PCodeList[i].SubProLevel, PCodeList[i].SymListAddr);
    }
};