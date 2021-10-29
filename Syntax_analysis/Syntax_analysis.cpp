//
// Created by 86156 on 2021-10-09.
// 以下语法成分不需要出现<BlockItem> <Decl> <BType>
//
#include "lexical_analysis.h"
#include <iostream>
#include <stdio.h>
#include "Syntax_analysis.h"
using namespace std;
int CtrlOutput = 0;         //控制语法分析结果输出
int Cursymbol = 0;
int LvalBackN = 0;
int Next2symbol = 0;

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
/*编译单元 */
//CompUnit → {Decl} {FuncDef} MainFuncDef
//Decl → ConstDecl | VarDecl
//First(ConstDecl) = {'const'}
//First(VarDecl) = {'int'}
//First(FuncDef) = First(FuncType) = {'int', 'void'}
//First(MainFunDef) = {'int'}
//存在回溯问题
//改写文法为 'int' ()
//MainFuncDef()
void CompUnit(){
	while(SymbolList[CurSymPos] >= 38||SymbolList[CurSymPos] <= 0){
		CurSymPos = CurSymPos+1;
	}
    while(SymbolList[CurSymPos] == 5||(SymbolList[CurSymPos] == 6&&SymbolList[CurSymPos+1] == 1&&SymbolList[CurSymPos+2] != 33)){//CONSTTK
        if(SymbolList[CurSymPos] == 5)
			ConstDecl();
		else
			VarDecl();
    }

	while(SymbolList[CurSymPos] == 20||(SymbolList[CurSymPos] == 6&&SymbolList[CurSymPos+1] == 1&&SymbolList[CurSymPos+2] == 33)){//VOIDTK
		FuncDef();
	}

	if(SymbolList[CurSymPos] == 6&&SymbolList[CurSymPos+1] == 4){ 
    	Sym_map(SymbolList[CurSymPos]);
       	CurSymPos = CurSymPos+1;
		MainFuncDef();
    }
    


    printf("<CompUnit>\n");
}

/*常量声明*/
//ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';'
void ConstDecl(){

    if(SymbolList[CurSymPos] == 5){//CONSTTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == 6){//INTTK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            ConstDef();
            while(SymbolList[CurSymPos] == 32){//COMMA
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                ConstDef();
            }
            if(SymbolList[CurSymPos] == 31){//SEMICN
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
            }
        }
    }
    printf("<ConstDecl>\n");
}
/*常量定义*/
//ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
void ConstDef(){
    if(SymbolList[CurSymPos] == 1){//IDENFR
        Ident();
        while(SymbolList[CurSymPos] == 35){//LBRACK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            ConstExp();
            if(SymbolList[CurSymPos] == 36){//RBRACK
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
            }
        }
        if(SymbolList[CurSymPos] == 30){//ASSIGN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            ConstInitVal();
        }

    }
    printf("<ConstDef>\n");
}
/*标识符*/
//Ident
void Ident(){
    if(SymbolList[CurSymPos] == 1) {//IDENFR
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }
	
}
/*常量初值*/
//ConstInitVal → ConstExp  '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
void ConstInitVal(){
    if(SymbolList[CurSymPos] == 37){
    	Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] != 38){
            ConstInitVal();
        }
        while(SymbolList[CurSymPos] == 32){
        	Sym_map(SymbolList[CurSymPos]);
        	CurSymPos = CurSymPos+1;
			ConstInitVal();
		}
		if(SymbolList[CurSymPos] == 38){
			Sym_map(SymbolList[CurSymPos]);
        	CurSymPos = CurSymPos+1;
		}
	}
	else{
		ConstExp();
	} 
	
    printf("<ConstInitVal>\n");
}
/*常量表达式*/
//ConstExp → AddExp
void ConstExp(){
    AddExp();
    printf("<ConstExp>\n");
}
/*加减表达式*/
//AddExp → MulExp | AddExp ('+' | '−') MulExp
//出现左递归
//改写为AddExp → MulExp { ('+'|'-') MulExp }
void AddExp(){
    MulExp();
    if(SymbolList[CurSymPos] == 18||SymbolList[CurSymPos] == 19){
		printf("<AddExp>\n");
	}
    while(SymbolList[CurSymPos] == 18||SymbolList[CurSymPos] == 19){ //18 PLUS 19 MINU
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;

        MulExp();
		if(SymbolList[CurSymPos] == 18||SymbolList[CurSymPos] == 19){
			printf("<AddExp>\n");
		}
		
    }
    printf("<AddExp>\n");
}
/*乘除模表达式*/
//MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
//左递归
//改写后 MulExp → UnaryExp {('*' | '/' | '%') UnaryExp}
void MulExp(){
    UnaryExp();
    if(SymbolList[CurSymPos] == 21||SymbolList[CurSymPos] == 22||SymbolList[CurSymPos] == 23){
		printf("<MulExp>\n");
	}
    while(SymbolList[CurSymPos] == 21||SymbolList[CurSymPos] == 22||SymbolList[CurSymPos] == 23){// * / %
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;

        UnaryExp();
        if(SymbolList[CurSymPos] == 21||SymbolList[CurSymPos] == 22||SymbolList[CurSymPos] == 23){
			printf("<MulExp>\n");
		}
		//printf("<MulExp>\n");
    }
    printf("<MulExp>\n");

}
/*一元表达式*/
//PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
// [FuncRParams];
// First[PrimaryExp] = {(, IDENFR, INTCON} 
// ���ڽ��� 
void UnaryExp(){
    if(SymbolList[CurSymPos] == 1&&SymbolList[CurSymPos+1] == 33){//IDENFR
        Ident();
        if(SymbolList[CurSymPos] == 33){//LPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            if(SymbolList[CurSymPos] != 34){
                FuncRParams();//函数实参表
            }



            if(SymbolList[CurSymPos] == 34){//RPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
            }
        }
		
    }
	else if(SymbolList[CurSymPos] == 33||SymbolList[CurSymPos] == 1||SymbolList[CurSymPos] == 2){
        PrimaryExp();
    }
    else if(SymbolList[CurSymPos] == 18||SymbolList[CurSymPos] == 19||SymbolList[CurSymPos] == 11){// + - !
        UnaryOp();
        UnaryExp();
    }

    printf("<UnaryExp>\n");

}
/*单目运算符*/
//UnaryOp → '+' | '−' | '!'
void UnaryOp(){
    if(SymbolList[CurSymPos] == 18||SymbolList[CurSymPos] == 19||SymbolList[CurSymPos] == 11){// + - !
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }
    printf("<UnaryOp>\n");
}
/*基本表达式*/
//PrimaryExp → '(' Exp ')' | LVal | Number
void PrimaryExp(){
    if(SymbolList[CurSymPos] == 33){//LPARENT
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        Exp();
        if(SymbolList[CurSymPos] == 34){//RPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
        }
    }
    else if(SymbolList[CurSymPos] == 2){//INTCON
        Number();
    }
    else{
        LVal();
    }
    printf("<PrimaryExp>\n");
}
/*表达式*/
//Exp → AddExp
void Exp(){
    AddExp();
    printf("<Exp>\n");
}
/*左值表达式*/
//LVal → Ident {'[' Exp ']'}
void LVal(){
    Ident();
    while(SymbolList[CurSymPos] == 35){//LBRACK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        Exp();
        if(SymbolList[CurSymPos] == 36){//RBRACK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
        }
    }

    printf("<LVal>\n");
}

/*数字*/
//Number → IntConst
void Number(){
    if(SymbolList[CurSymPos] == 2){//INTCON
        IntConst();
    }
    printf("<Number>\n");
}
/*IntConst*/
void IntConst(){
    if(SymbolList[CurSymPos] == 2){//INTCON
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }

}
/*函数实参表*/
//FuncRParams → Exp { ',' Exp }
void FuncRParams(){
    Exp();
    while(SymbolList[CurSymPos] == 32){//COMMA
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        Exp();
    }
    printf("<FuncRParams>\n");
}
/*变量声明*/
//VarDecl → BType VarDef { ',' VarDef } ';'
void VarDecl(){
    if(SymbolList[CurSymPos] == 6){
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == 1){//IDENFR Ԥ����ident
            VarDef();
            while(SymbolList[CurSymPos] == 32){//COMMA
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;

                VarDef();
            }
            if(SymbolList[CurSymPos] == 31){//SEMICN
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
            }
        }
    }

    printf("<VarDecl>\n");
}

/*变量定义*/
//VarDef → Ident { '[' ConstExp ']' } | Ident { '[' ConstExp ']' } '=' InitVal
void VarDef(){
    if(SymbolList[CurSymPos] == 1){
        Ident();
        while(SymbolList[CurSymPos] == 35 ){//LBRACK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            ConstExp();
            if(SymbolList[CurSymPos] == 36){//RBRACK
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
            }
        }
        if(SymbolList[CurSymPos] == 30){//ASSIGN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            InitVal();
        }
    }


    printf("<VarDef>\n");
}

/*变量初值*/
//InitVal → Exp | '{' [ InitVal { ',' InitVal } ] '}'
void InitVal(){
    if(SymbolList[CurSymPos] == 37){//LBRACE
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;


        InitVal();
        while(SymbolList[CurSymPos] == 32){//COMMA
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;


            InitVal();

        }
        if(SymbolList[CurSymPos] == 38){//RBRACE
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

        }
    }
    else{
        Exp();
    }
    printf("<InitVal>\n");
}

/*函数定义*/
// FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
void FuncDef(){
    if(SymbolList[CurSymPos] == 6){//INTTK
        FuncType();
        if(SymbolList[CurSymPos] == 1){//INDEFR
            Ident();
            if(SymbolList[CurSymPos] == 33){//LPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;

                if(SymbolList[CurSymPos] != 34){
                    FuncFParams();
                }


                if(SymbolList[CurSymPos] == 34){//RPARENT
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                }
                Block();
            }
        }

    }
	else if(SymbolList[CurSymPos] == 20){
		FuncType();
        if(SymbolList[CurSymPos] == 1){//INDEFR
            Ident();
            if(SymbolList[CurSymPos] == 33){//LPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                if(SymbolList[CurSymPos] != 34){
                    FuncFParams();
                }


                if(SymbolList[CurSymPos] == 34){//RPARENT
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                }
                Block();
            }
        }
	}
    printf("<FuncDef>\n");
}

/*函数类型*/
//FuncType → 'void' | 'int'
void FuncType(){
    if(SymbolList[CurSymPos] == 6||SymbolList[CurSymPos] == 20){//VOIDTK INTTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }
    printf("<FuncType>\n");
}

/*函数形参表*/
//FuncFParams → FuncFParam { ',' FuncFParam }
void FuncFParams(){
    FuncFParam();
    while(SymbolList[CurSymPos] == 32){//COMMA
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        FuncFParam();
    }
    printf("<FuncFParams>\n");
}

/*函数形参*/
//FuncFParam → BType Ident ['[' ']' { '[' ConstExp ']' }]
void FuncFParam(){
    if(SymbolList[CurSymPos] == 6){//INTTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == 1){
            Ident();
            if(SymbolList[CurSymPos] == 35){//LBRACK
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                if(SymbolList[CurSymPos] == 36){//RBRACK
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                    while(SymbolList[CurSymPos] == 35){//LBRACK
                        Sym_map(SymbolList[CurSymPos]);
                        CurSymPos = CurSymPos+1;

                        ConstExp();
                        if(SymbolList[CurSymPos] == 36){//RBRACK
                            Sym_map(SymbolList[CurSymPos]);
                            CurSymPos = CurSymPos+1;
                        }
                    }
                }
            }
        }

    }
    printf("<FuncFParam>\n");
}

/*语句块*/
//Block → '{' { ConstDecl | VarDecl | Stmt } '}'
//BlockItem →
void Block(){
    if(SymbolList[CurSymPos] == 37){//LBRACE
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        while(SymbolList[CurSymPos] == 5||SymbolList[CurSymPos] == 6||SymbolList[CurSymPos] == 1||
			  SymbolList[CurSymPos] == 7||SymbolList[CurSymPos] == 8||SymbolList[CurSymPos] == 9||
			  SymbolList[CurSymPos] == 10||SymbolList[CurSymPos] == 16||SymbolList[CurSymPos] == 17||
			  SymbolList[CurSymPos] == 37||SymbolList[CurSymPos] == 33||SymbolList[CurSymPos] == 2||
			  SymbolList[CurSymPos] == 14||SymbolList[CurSymPos] == 31||SymbolList[CurSymPos] == 19||
			  SymbolList[CurSymPos] == 11||SymbolList[CurSymPos] == 18){
            if(SymbolList[CurSymPos] == 5){
                ConstDecl();
            }
            else if(SymbolList[CurSymPos] == 6){

                VarDecl();
            }
            else{
            	Stmt(); 
			} 
        }
        if(SymbolList[CurSymPos] == 38){//RBRACE
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
        }

    }
    printf("<Block>\n");
}


/*语句*/
/*Stmt → LVal '=' Exp ';' // 每种类型的语句都要覆盖
 | [Exp] ';' //有⽆Exp两种情况
 | Block
 | 'if' '(' Cond ')' Stmt [ 'else' Stmt ] // 1.有else 2.⽆else
 | 'while' '(' Cond ')' Stmt
 | 'break' ';' | 'continue' ';'
 | 'return' [Exp] ';' // 1.有Exp 2.⽆Exp
 | LVal = 'getint''('')'';'
 | 'printf''('FormatString{,Exp}')'';' // 1.有Exp 2.⽆Exp*/

void Stmt(){
    if(SymbolList[CurSymPos] == 9){//IFTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == 33){//LPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            Cond();
            if(SymbolList[CurSymPos] == 34){//RPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                Stmt();
                if(SymbolList[CurSymPos] == 10){//ELSETK
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                    Stmt();
                }
            }
        }

    }
    else if(SymbolList[CurSymPos] == 14){//WHILETK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == 33){//LPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            Cond();
            if(SymbolList[CurSymPos] == 34){//RPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                Stmt();
            }

        }
    }
    else if(SymbolList[CurSymPos] == 7){//BREAKTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == 31){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

        }

    }
    else if(SymbolList[CurSymPos] == 8){//CONTINUETK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == 31){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

        }
    }
    else if(SymbolList[CurSymPos] == 17){//RETURNTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] != 31){
        Exp();	
		} 
		
        if(SymbolList[CurSymPos] == 31){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

        }
    }
    else if(SymbolList[CurSymPos] == 16){//PRINTFTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == 33){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            FormatString();
            while(SymbolList[CurSymPos]== 32){//COMMA
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                Exp();

            }
            if(SymbolList[CurSymPos] == 34){//RPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                if(SymbolList[CurSymPos] == 31){//SEMICN
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                }

            }
        }
    }
    else if(SymbolList[CurSymPos] == 1&&SymbolList[CurSymPos+1] == 33){//exp Ident '(' [FuncRParams] );
    	Exp();
    	if(SymbolList[CurSymPos] == 31){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
        }
    	
	}
    else if(SymbolList[CurSymPos] == 1){//IDENTFR    LVAL
        int StmtCurPos = CurSymPos;
        int Expflag = 1;
		while(SymbolList[StmtCurPos] != 31){
			if(SymbolList[StmtCurPos] == 30){
				Expflag = 0;
				break;
			}
			else{
				Expflag = 1;
			}
			StmtCurPos = StmtCurPos+1;
		}
		if(Expflag == 0){
			LVal();
        	if(SymbolList[CurSymPos] == 30){//ASSIGN
        	    Sym_map(SymbolList[CurSymPos]);
        	    CurSymPos = CurSymPos+1;
        	    if(SymbolList[CurSymPos] == 15){//GETINTTK
        	        Sym_map(SymbolList[CurSymPos]);
        	        CurSymPos = CurSymPos+1;
        	        if(SymbolList[CurSymPos] == 33){//LPARENT
        	            Sym_map(SymbolList[CurSymPos]);
        	            CurSymPos = CurSymPos+1;
        	            if(SymbolList[CurSymPos] == 34){//RPARENT
        	                Sym_map(SymbolList[CurSymPos]);
        	                CurSymPos = CurSymPos+1;
        	                if(SymbolList[CurSymPos] == 31){//SEMICN
        	                    Sym_map(SymbolList[CurSymPos]);
         	                   	CurSymPos = CurSymPos+1;
        	                }
	
            	        }
            	    }
            	}
            	else{
            	    Exp();
            	    if(SymbolList[CurSymPos] == 31){//SEMICN
            	        Sym_map(SymbolList[CurSymPos]);
            	        CurSymPos = CurSymPos+1;
            	    }
            	}
			}
		
        }
        else{
			Exp();
            if(SymbolList[CurSymPos] == 31){//SEMICN
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
            }
        }
        
    }
	else if(SymbolList[CurSymPos] == 37){
        Block();//??????????????????????
    }
    else{
    	if(SymbolList[CurSymPos] != 31) {
            Exp();
        }

    	if(SymbolList[CurSymPos] == 31){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
    	}
	}
    printf("<Stmt>\n");
}
/*字符串*/
void FormatString(){
    if(SymbolList[CurSymPos] == 3){//STRCON
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }

}
/*条件表达式*/
//Cond → LOrExp
void Cond(){
    LOrExp();
    printf("<Cond>\n");
}

/*逻辑或表达式*/
//LOrExp → LAndExp | LOrExp '||' LAndExp
//左递归
//改写为LOrExp → LAndExp {'||' LAndExp}
void LOrExp(){
    LAndExp();
    if(SymbolList[CurSymPos] == 13){
    	printf("<LOrExp>\n");
	}
    while(SymbolList[CurSymPos] == 13){//OR
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        LAndExp();
        if(SymbolList[CurSymPos] == 13){
    		printf("<LOrExp>\n");
		}
		
    }
    printf("<LOrExp>\n");
}

/*逻辑与表达式*/
//LAndExp → EqExp | LAndExp '&&' EqExp
//左递归
//改写为LAndExp → EqExp { '&&' EqExp }
void LAndExp(){
    EqExp();
    if(SymbolList[CurSymPos] == 12){
        	printf("<LAndExp>\n");
		}
    while(SymbolList[CurSymPos] == 12){//AND
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        EqExp();
        if(SymbolList[CurSymPos] == 12){
        	printf("<LAndExp>\n");
		}
		
    }
    printf("<LAndExp>\n");
}

/*相等性表达式*/
//EqExp → RelExp | EqExp ('==' | '!=') RelExp
//左递归
//改写后EqExp → RelExp { ('==' | '!=') RelExp }
void EqExp(){
    RelExp();
    if(SymbolList[CurSymPos] == 28||SymbolList[CurSymPos] == 29){
    	printf("<EqExp>\n");
	}
    while(SymbolList[CurSymPos] == 28||SymbolList[CurSymPos] == 29){//EQL //NEQ
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        RelExp();
        if(SymbolList[CurSymPos] == 28||SymbolList[CurSymPos] == 29){
    		printf("<EqExp>\n");
		}
    }
    printf("<EqExp>\n");
}

/*关系表达式*/
//RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
//左递归
//改写为RelExp → AddExp { ('<' | '>' | '<=' | '>=') AddExp }
void RelExp(){
    AddExp();
    if(SymbolList[CurSymPos] == 26||SymbolList[CurSymPos] == 24||SymbolList[CurSymPos] == 27||SymbolList[CurSymPos] == 25){
    	printf("<RelExp>\n");
	}
    while(SymbolList[CurSymPos] == 26||SymbolList[CurSymPos] == 24||SymbolList[CurSymPos] == 27||SymbolList[CurSymPos] == 25){//GRE LSS GEQ LEQ
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        AddExp();
        if(SymbolList[CurSymPos] == 26||SymbolList[CurSymPos] == 24||SymbolList[CurSymPos] == 27||SymbolList[CurSymPos] == 25){
    		printf("<RelExp>\n");
		}
    }
    printf("<RelExp>\n");

}

/*主函数定义*/

void MainFuncDef(){
	
	if(SymbolList[CurSymPos] == 4){
		Sym_map(SymbolList[CurSymPos]);
		CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == 33){
        	Sym_map(SymbolList[CurSymPos]);
        	CurSymPos = CurSymPos+1;
        	if(SymbolList[CurSymPos] == 34){
        		Sym_map(SymbolList[CurSymPos]);
        		CurSymPos = CurSymPos+1;
        		Block();
			}
		}
	}
	cout << "<MainFuncDef>" << endl;
}
