//
// Created by 86156 on 2021-10-19.
//
#include <vector>
#ifndef COMPLIER_ERROR_H
#define COMPLIER_ERROR_H
using namespace std;
#define EA 0
#define EB 1
#define EC 2
#define ED 3
#define EE 4
#define EF 5
#define EG 6
#define EH 7
#define EI 8
#define EJ 9
#define EK 10
#define EL 11
#define EM 12
extern int ErrorType;
extern char ErrorTypeList[15];
extern vector<int> IsWhile;
extern int IsIntReturn;
extern int IsVoidReturn;
extern int RParmDataType;
void Error(int ErrorType);


#endif //COMPLIER_ERROR_H
