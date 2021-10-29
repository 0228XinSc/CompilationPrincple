//
// Created by 86156 on 2021-09-27.
//

/*
 * 词法分析器实现
 * 功能：
 *
 *
 * */

#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexical_analysis.h"

using namespace std;
/*void InitSymbolList(){
	
	MapSymbol.insert(pair<int, string>(1, "IDENFR"));
	MapSymbol.insert(pair<int, string>(2, "INTCON"));
	MapSymbol.insert(pair<int, string>(3, "STRCON"));
	MapSymbol.insert(pair<int, string>(4, "MAINTK main"));
	MapSymbol.insert(pair<int, string>(5, "CONSTTK const"));
	MapSymbol.insert(pair<int, string>(6, "INTTK int"));
	MapSymbol.insert(pair<int, string>(7, "BREAKTK break"));
	MapSymbol.insert(pair<int, string>(8, "CONTINUETK continue"));
	MapSymbol.insert(pair<int, string>(9, "IFTK if"));
	MapSymbol.insert(pair<int, string>(10, "ELSETK else"));
	MapSymbol.insert(pair<int, string>(11, "NOT !"));
	MapSymbol.insert(pair<int, string>(12, "AND &&"));
	MapSymbol.insert(pair<int, string>(13, "OR ||"));
	MapSymbol.insert(pair<int, string>(14, "WHILETK while"));
	MapSymbol.insert(pair<int, string>(15, "GETINTTK getint"));
	MapSymbol.insert(pair<int, string>(16, "PRINTFTK printf"));
	MapSymbol.insert(pair<int, string>(17, "RETURNTK return"));
	MapSymbol.insert(pair<int, string>(18, "PLUS +"));
	MapSymbol.insert(pair<int, string>(19, "MINU -"));
	MapSymbol.insert(pair<int, string>(20, "VOIDTK void"));
	MapSymbol.insert(pair<int, string>(21, "MULT *"));
	MapSymbol.insert(pair<int, string>(22, "DIV /"));
	MapSymbol.insert(pair<int, string>(23, "MOD %"));
	MapSymbol.insert(pair<int, string>(24, "LSS <"));
	MapSymbol.insert(pair<int, string>(25, "LEQ <="));
	MapSymbol.insert(pair<int, string>(26, "GRE >"));
	MapSymbol.insert(pair<int, string>(27, "GEQ >="));
	MapSymbol.insert(pair<int, string>(28, "EQL =="));
	MapSymbol.insert(pair<int, string>(29, "NEQ !="));
	MapSymbol.insert(pair<int, string>(30, "ASSIGN ="));
	MapSymbol.insert(pair<int, string>(31, "SEMICN ;"));
	MapSymbol.insert(pair<int, string>(32, "COMMA ,"));
	MapSymbol.insert(pair<int, string>(33, "LPARENT ("));
	MapSymbol.insert(pair<int, string>(34, "RPARENT )"));
	MapSymbol.insert(pair<int, string>(35, "LBRACK ["));
	MapSymbol.insert(pair<int, string>(36, "RBRACK ]"));
	MapSymbol.insert(pair<int, string>(37, "LBRACE {"));
	MapSymbol.insert(pair<int, string>(38, "RBRACE }"));
	MapSymbol.insert(pair<int, string>(39, "ERROR"));
	MapSymbol.insert(pair<int, string>(40, "NOTES"));
	
}	*/
void InitSymbolList(){
	
	MapSymbol.insert(pair<int, string>(1, "IDENFR"));
	MapSymbol.insert(pair<int, string>(2, "INTCON"));
	MapSymbol.insert(pair<int, string>(3, "STRCON"));
	MapSymbol.insert(pair<int, string>(4, "MAINTK main"));
	MapSymbol.insert(pair<int, string>(5, "CONSTTK const"));
	MapSymbol.insert(pair<int, string>(6, "INTTK int"));
	MapSymbol.insert(pair<int, string>(7, "BREAKTK break"));
	MapSymbol.insert(pair<int, string>(8, "CONTINUETK continue"));
	MapSymbol.insert(pair<int, string>(9, "IFTK if"));
	MapSymbol.insert(pair<int, string>(10, "ELSETK else"));
	MapSymbol.insert(pair<int, string>(11, "NOT !"));
	MapSymbol.insert(pair<int, string>(12, "AND &&"));
	MapSymbol.insert(pair<int, string>(13, "OR ||"));
	MapSymbol.insert(pair<int, string>(14, "WHILETK while"));
	MapSymbol.insert(pair<int, string>(15, "GETINTTK getint"));
	MapSymbol.insert(pair<int, string>(16, "PRINTFTK printf"));
	MapSymbol.insert(pair<int, string>(17, "RETURNTK return"));
	MapSymbol.insert(pair<int, string>(18, "PLUS +"));
	MapSymbol.insert(pair<int, string>(19, "MINU -"));
	MapSymbol.insert(pair<int, string>(20, "VOIDTK void"));
	MapSymbol.insert(pair<int, string>(21, "MULT *"));
	MapSymbol.insert(pair<int, string>(22, "DIV /"));
	MapSymbol.insert(pair<int, string>(23, "MOD %"));
	MapSymbol.insert(pair<int, string>(24, "LSS <"));
	MapSymbol.insert(pair<int, string>(25, "LEQ <="));
	MapSymbol.insert(pair<int, string>(26, "GRE >"));
	MapSymbol.insert(pair<int, string>(27, "GEQ >="));
	MapSymbol.insert(pair<int, string>(28, "EQL =="));
	MapSymbol.insert(pair<int, string>(29, "NEQ !="));
	MapSymbol.insert(pair<int, string>(30, "ASSIGN ="));
	MapSymbol.insert(pair<int, string>(31, "SEMICN ;"));
	MapSymbol.insert(pair<int, string>(32, "COMMA ,"));
	MapSymbol.insert(pair<int, string>(33, "LPARENT ("));
	MapSymbol.insert(pair<int, string>(34, "RPARENT )"));
	MapSymbol.insert(pair<int, string>(35, "LBRACK ["));
	MapSymbol.insert(pair<int, string>(36, "RBRACK ]"));
	MapSymbol.insert(pair<int, string>(37, "LBRACE {"));
	MapSymbol.insert(pair<int, string>(38, "RBRACE }"));
	MapSymbol.insert(pair<int, string>(39, "ERROR"));
	MapSymbol.insert(pair<int, string>(40, "NOTES"));
	
}
//清空token字符数组
void ClearToken(){
    memset(token,'\0',sizeof(token));
}
bool IsSpace(){
    return CurC == ' ' ? true : false;
}
bool IsNewline(){
    return CurC == '\n' ? true : false;
}
bool IsTab(){
    return CurC == '\t' ? true : false;
}
bool IsAlpha(){
    return isalpha(CurC) ? true : false;
}
bool IsDigit(){
    return (CurC > 47 && CurC < 58) ? true : false;
}
bool IsPlus(){
    return CurC == '+' ? true : false;
}
bool IsMinu(){
    return CurC == '-' ? true : false;
}
bool IsNot(){
    return CurC == '!' ? true : false;
}
bool IsMult(){
    return CurC == '*' ? true : false;
}
bool IsDiv(){
    return CurC == '/' ? true : false;
}
bool IsMod(){
    return CurC == '%' ? true : false;
}
bool IsLss(){
    return CurC == '<' ? true : false;
}
bool IsGre(){
    return CurC == '>' ? true : false;
}
bool IsAssign(){
    return CurC == '=' ? true : false;
}
bool IsSemicn(){
    return CurC == ';' ? true : false;
}
bool IsComma(){
    return CurC == ',' ? true : false;
}
bool IsLparent(){
    return CurC == '(' ? true : false;
}
bool IsRparent(){
    return CurC == ')' ? true : false;
}
bool IsLbrack(){
    return CurC == '[' ? true : false;
}
bool IsRbrack(){
    return CurC == ']' ? true : false;
}
bool IsLbrace(){
    return CurC == '{' ? true : false;
}
bool IsRbrace(){
    return CurC == '}' ? true : false;
}
bool IsAnd(){
    return CurC == '&' ? true : false;
}
bool IsOr(){
    return CurC == '|' ? true : false;
}
void ConToken(){
    token[tokeni] = CurC;
    tokeni++;
}


void GetSymbol(){
    ClearToken();
    CurC = InitCode[CurCPos++];//获得当前读入字符
    while(IsNewline()||IsSpace()||IsTab()||CurC == '\r'){
        CurC = InitCode[CurCPos++];
    }
    if(IsAlpha() || CurC == '_'){
        tokeni = 0;
        while(IsAlpha()||IsDigit()||CurC == '_'){
            /*拼接字符串*/
            ConToken();
            CurC = InitCode[CurCPos++];
        }
        CurC = InitCode[--CurCPos];
        token[tokeni] = '\0';
        /*查找保留字*/
    	if(strcmp("main", token) == 0) {
    	    symbol = 4;
    	}
    	else if(strcmp("const", token) == 0) {
    	    symbol = 5;
    	}
    	else if(strcmp("int", token) == 0) {
    	    symbol = 6;
    	}
    	else if(strcmp("break", token) == 0) {
    	    symbol = 7;
    	}
    	else if(strcmp("continue", token) == 0) {
    	    symbol = 8;
    	}
    	else if(strcmp("if", token) == 0) {
    	    symbol = 9;
    	}
    	else if(strcmp("else", token) == 0) {
    	    symbol = 10;
    	}
    	else if(strcmp("while", token) == 0) {
    	    symbol = 14;
    	}
    	else if(strcmp("getint", token) == 0) {
    	    symbol = 15;
    	}
    	else if(strcmp("printf", token) == 0) {
    	    symbol = 16;
    	}
    	else if(strcmp("return", token) == 0) {
    	    symbol = 17;
    	}
    	else if(strcmp("void", token) == 0) {
    	    symbol = 20;
    	}
    	else{
    	    symbol = 1;//标识符
    	}
    }
    else if(IsDigit()){
        tokeni = 0;
        while(IsDigit()) {
            ConToken();
            CurC = InitCode[CurCPos++];
        }
        CurC = InitCode[--CurCPos];
        token[tokeni] = '\0';
        symbol = 2;//INTCON
    }
    else if (CurC == '"')
    {
        tokeni = 0;
        while (CurC = InitCode[CurCPos++]) {
            if (CurC == '"') {
                break;
            }
            token[tokeni] = CurC;
            tokeni++;
        }
        token[tokeni] = '\0';
        symbol = 3;//STRCON

    }
    else if(IsPlus()){
        symbol = 18;//PLUS
    }
    else if(IsMinu()){
        symbol = 19;//MINU
    }
    else if(IsMult()){
        symbol = 21;//MULT
    }
    else if(IsDiv()){
    	CurC = InitCode[CurCPos++];
        if(CurC == '*'){
           CurC = InitCode[CurCPos++];
           char LastC = InitCode[CurCPos-2];
           char Last2C = InitCode[CurCPos-3];
           while(1){
        		if(Last2C != '/'&&LastC == '*'&&CurC == '/'){
        			symbol = 40;//notes
					break;
				}
				else{
					CurC = InitCode[CurCPos++];
           			LastC = InitCode[CurCPos-2];
                    Last2C = InitCode[CurCPos-3];
				}
		   }
        }
        /*/*
     * /testfile created with ``heart'' by 19373384
     *
    /
    */
        else if(IsDiv()){
        	CurC = InitCode[CurCPos++];
            while(CurC != '\n'){
                CurC = InitCode[CurCPos++];
                if(CurC == '\n'){
                	symbol = 40; //notes
					break;
				}
            }
        }
        else{
        	symbol = 22;//DIV
        	CurC = InitCode[--CurCPos];
		}
            
    }
    else if(IsMod()){
        symbol = 23;//MOD
    }
    else if(IsSemicn()){
        symbol = 31;//SEMICN
    }
    else if(IsComma()){
        symbol = 32;//COMMA
    }
    else if(IsLparent()){
        symbol = 33;//LPARENT
    }
    else if(IsRparent()){
        symbol = 34;//RPARENT
    }
    else if(IsLbrack()){
        symbol = 35;//LBRACK
    }
    else if(IsRbrack()){
        symbol = 36;//RBRACK
    }
    else if(IsLbrace()){
        symbol = 37;//LBRACE
    }
    else if(IsRbrace()){
        symbol = 38;//RBRACE
    }
    else if(IsNot()) {
        CurC = InitCode[CurCPos++];
        if(IsAssign()){
            symbol = 29;//NEQ
        }
        else{
            symbol = 11;//NOT
            CurC = InitCode[--CurCPos];
        }
    }
    else if(IsLss()){
        CurC = InitCode[CurCPos++];
        if(IsAssign()){
            symbol = 25;//LEQ
        }
        else {
            symbol = 24;//LSS
            CurC = InitCode[--CurCPos];
        }
    }
    else if(IsGre()){
        CurC = InitCode[CurCPos++];
        if(IsAssign()){
            symbol = 27;//GEQ
        }
        else{
            symbol = 26;//GRE
            CurC = InitCode[--CurCPos];
        }
    }
    else if(IsAssign()){
        CurC = InitCode[CurCPos++];
        if(IsAssign()){
            symbol = 28;//EQL        
			
        }
        else {
            symbol = 30;//Assign
            CurC = InitCode[--CurCPos];
        }

    }
    else if(IsAnd()){
        CurC = InitCode[CurCPos++];
        if(IsAnd()) {
            symbol = 12;//AND
        }
    }
    else if(IsOr()){
        CurC = InitCode[CurCPos++];
        if(IsOr()) {
            symbol = 13;//OR
        }
    }
    else{
    	symbol = 39;//ERROR
	} 
}

void Sym_map(int symbol) //映射函数
{	map<int, string>::iterator item;
	item = MapSymbol.find(symbol);
	if(symbol <= 2 && symbol >=1){
		cout << item->second << ' ' << TokenList[CurSymPos] << endl;
	}
	else if(symbol == 3){
		cout << item->second << ' ' << "\"" << TokenList[CurSymPos] << "\"" << endl;
	}
	else if(symbol >3&&symbol < 39){
		cout << item->second  << endl;
	}
}
