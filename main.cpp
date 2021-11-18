//
// Created by 86156 on 2021-10-08.
//

#include <bits/stdc++.h>
#include "Lexical_analysi.h"
#include "Syntax_analysis.h"
#include "Table.h"

#define DEBUG

using namespace std;

/*词法分析*/
map<int,string> MapSymbol;  //存储序号对应类别码
char InitCode[500000];      //存储源文件整体字符串用于词法分析
char CurC;                  //存放字符串
int InitCodeN;              //存放当前字符
int CurCPos;                //从源文件读入字符串当前字符串位置
char token[1000];           //token字符串指针
int tokeni;
int symbol;
/*语法分析*/
string TokenList[10000];
int SymbolList[100000];
int CurSymPos;              //语法分析 类别码数组 和token数组位置
int SymbolListN;            //类别码个数
/*符号表管理*/
int SymbolListLine[100000]; //存储每个标识符对应的行号
int LineNum;//行号
vector<int> SubProgramIndexTable;
vector<MainSymbolTable> StackSymbolTable;
/*错误处理*/
int ErrorType;
int RParmDataType;//实参在没进入LVAL，都当作0维
vector<int> IsWhile;
int IsIntReturn;
int IsVoidReturn;
char ErrorTypeList[15] = {'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm'};

int ErrorPrintFlag = 0;

int main() {

    #ifdef DEBUG
        setbuf(stdout, nullptr);
    #endif

    InitSymbolList();
	FILE* in = freopen("testfile.txt", "r", stdin);
    //FILE* out = freopen("error.txt", "w", stdout);
    //FILE* out = freopen("output.txt", "w", stdout);
    /*读入字符串*/
    while((CurC = getchar()) != EOF){
        InitCode[CurCPos++] = CurC;
    }
    InitCodeN = CurCPos;
    LineNum = 1;
    for(CurCPos=0, CurSymPos=0; CurCPos<InitCodeN-1; ){
        GetSymbol();
        if(symbol>=1&&symbol<=38){
            SymbolList[CurSymPos] = symbol;
        	TokenList[CurSymPos] = token;
        	SymbolListLine[CurSymPos] = LineNum;
            //Token[CurSymPos] = token;
			CurSymPos++;
		} 
        
    }
    SymbolListN = CurSymPos;
    for(CurSymPos=0; CurSymPos<SymbolListN-1; ) {
        CompUnit();
        Sym_map(SymbolList[CurSymPos]);
    }
    /*目标代码的解释执行*/

    fclose(stdin);
    //fclose(stdout);
    return 0;
}
