//
// Created by 86156 on 2021-11-18.
//

#ifndef COMPILATIONPRINCPLE_INTERPRETATION_EXECUTION_H
#define COMPILATIONPRINCPLE_INTERPRETATION_EXECUTION_H
#include <vector>
#include <string>
#include <queue>
using namespace std;
/*运行栈实现*/
extern vector<int> RunStack;
/*数据存储表*/
extern int IntDataTable[50000];
extern int IntDataTableTop;
/*输入缓冲区*/
extern vector<int> Buffer;
extern int BufferTop;
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
