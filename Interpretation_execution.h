//
// Created by 86156 on 2021-11-18.
//

#ifndef COMPILATIONPRINCPLE_INTERPRETATION_EXECUTION_H
#define COMPILATIONPRINCPLE_INTERPRETATION_EXECUTION_H
#include <vector>
using namespace std;
/*运行栈实现*/
extern vector<int> RunStack;
/*数据存储表*/
extern int IntDataTable[50000];
extern int IntDataTableTop;
/*输入缓冲区*/
extern vector<int> Buffer;
extern int BufferTop;
void Interpretation_execution();


#endif //COMPILATIONPRINCPLE_INTERPRETATION_EXECUTION_H
