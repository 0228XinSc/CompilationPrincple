//
// Created by 86156 on 2021-10-08.
//

#include <bits/stdc++.h>
/*#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <map>*/
#include "lexical_analysis.h"
#include "Syntax_analysis.h"

#define DEBUG

using namespace std;
map<int,string> MapSymbol;
char InitCode[500000];      //存储源文件整体字符串用于词法分析
int CurCPos;            //当前字符串位置
int CurSymPos;
int InitCodeN;          //存放当前字符
int SymbolListN; 
char CurC;                  //存放字符串
char token[1000];         //token字符串指针
string TokenList[10000];
int tokeni;
int symbol;
int SymbolList[100000];

int main() {

#ifdef DEBUG
    setbuf(stdout, nullptr);
#endif

    InitSymbolList();
	FILE* in = freopen("testfile.txt", "r", stdin);
    FILE* out = freopen("output.txt", "w", stdout);
    /*读入字符串*/
    while((CurC = getchar()) != EOF){
        InitCode[CurCPos++] = CurC;
    }
    InitCodeN = CurCPos;
    for(CurCPos=0, CurSymPos=0; CurCPos<InitCodeN-1; ){
        GetSymbol();
        if(symbol>=1&&symbol<=38){
            SymbolList[CurSymPos] = symbol;
        	TokenList[CurSymPos] = token;
            //Token[CurSymPos] = token;
			CurSymPos++;
		} 
        
    }
    SymbolListN = CurSymPos;
    for(CurSymPos=0; CurSymPos<SymbolListN-1; ){
        CompUnit();
		Sym_map(SymbolList[CurSymPos]);
    }
	//
    /*完成词法分析*/
    /*开始语法分析，从ouput文件中读入*/
    fclose(stdin);
    fclose(stdout);
    return 0;
}
