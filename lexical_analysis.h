//
// Created by 86156 on 2021-10-08.
// 注意不要在.h文件中声明变量，会造成多次包含.h文件对变量进行重复声明
//
#include <iostream>
#include <string>
#include <map>

#ifndef LEXICAL_ANALYSIS1_LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS1_LEXICAL_ANALYSIS_H
#define IDENFR 1
#define INTCON 2
#define STRCON 3
#define MAINTK 4
#define CONSTTK 5
#define INTTK 6
#define BREAKTK 7
#define CONTINUETK 8
#define IFTK 9
#define ELSETK 10
#define NOT 11
#define AND 12
#define OR 13
#define WHILETK 14
#define GETINTTK 15
#define PRINTFTK 16
#define RETURNTK 17
#define PLUS 18
#define MINU 19
#define VOIDTK 20
#define MULT 21
#define DIV 22
#define MOD 23
#define LSS 24
#define LEQ 25
#define GRE 26
#define GEQ 27
#define EQL 28
#define NEQ 29
#define ASSIGN 30
#define SEMICN 31
#define COMMA 32
#define LPARENT 33
#define RPARENT 34
#define LBRACK 35
#define RBRACK 36
#define LBRACE 37
#define RBRACE 38
#define ERROR 39
#define NOTES 40
using namespace std;

extern int ErrorPrintFlag;

extern map<int,string> MapSymbol;
extern char InitCode[500000];      //存储源文件整体字符串用于词法分析
extern int CurCPos;            //当前字符串位置
extern int CurSymPos;
extern int InitCodeN;          //存放当前字符
extern char CurC;                  //存放字符串
extern char token[1000];         //token字符串指针
extern string TokenList[10000];
extern int symbol;
extern int tokeni;
extern int SymbolListN;
extern int SymbolList[100000];
extern int SymbolListLine[100000];
extern int LineNum;//行号
//枚举型全局变量，存放单词的类型码

void InitSymbolList();

bool IsSpace();                     //判断是否为空格
bool IsNewline();                   //判断是否为换行符
bool IsTab();                       //判断是否为制表符
bool IsAlpha();                    //判断是否为字母
bool IsDigit();                     //判断是否为数字
bool IsPlus();                      //判断是否为加号
bool IsMinu();
bool IsNot();
bool IsMult();
bool IsDiv();
bool IsMod();
bool IsLss();
bool IsGre();
bool IsAssign();
bool IsSemicn();
bool IsComma();
bool IsLparent();
bool IsRparent();
bool IsLbrack();
bool IsRbrack();
bool IsLbrace();
bool IsRbrace();
bool IsAnd();
bool IsOr();

void ClearToken();                  //清空token字符数组
void ConToken();                    //拼接token字符串
void GetSymbol();                   //获得类别码
void Sym_map(int symbol);

#endif //LEXICAL_ANALYSIS1_LEXICAL_ANALYSIS_H

