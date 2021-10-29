//
// Created by 86156 on 2021-10-09.
// 以下语法成分不需要出现<BlockItem> <Decl> <BType>
//
#include <iostream>
#include <stdio.h>
#include "lexical_analysis.h"
#include "Syntax_analysis.h"
#include "Symbol_Table.h"
#include "Error.h"
using namespace std;

/*BType*/
void BType(){

}
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
    while(SymbolList[CurSymPos] == CONSTTK||(SymbolList[CurSymPos] == INTTK&&SymbolList[CurSymPos+1] == IDENFR&&SymbolList[CurSymPos+2] != LPARENT)){//CONSTTK
        if(SymbolList[CurSymPos] == CONSTTK)
			ConstDecl();
		else
			VarDecl();
    }

	while(SymbolList[CurSymPos] == VOIDTK||(SymbolList[CurSymPos] == INTTK&&SymbolList[CurSymPos+1] == IDENFR&&SymbolList[CurSymPos+2] == LPARENT)){//VOIDTK
		FuncDef();
	}

	if(SymbolList[CurSymPos] == INTTK&&SymbolList[CurSymPos+1] == MAINTK){
    	Sym_map(SymbolList[CurSymPos]);
       	CurSymPos = CurSymPos+1;
		MainFuncDef();
    }


    if(ErrorPrintFlag)
    printf("<CompUnit>\n");
}

/*常量声明*/
//ConstDecl → 'const' BType ConstDef { ',' ConstDef } ';'
//错误 HI
void ConstDecl(){

    if(SymbolList[CurSymPos] == CONSTTK){//CONSTTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == INTTK){//INTTK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            ConstDef();
            while(SymbolList[CurSymPos] == COMMA){//COMMA
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                ConstDef();
            }
            if(SymbolList[CurSymPos] == SEMICN){//SEMICN
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
            }
            else{
                /*不需要加判断*/
                Error(EI);

            }
        }
    }
    if(ErrorPrintFlag)
    printf("<ConstDecl>\n");
}
/*常量定义*/
//ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
void ConstDef(){
    if(SymbolList[CurSymPos] == IDENFR){//IDENFR
        Ident();
        /*syml*/
        int NameIndexTemp = CurSymPos-1, IdentTypeIdTemp = 2, DataTypeIdTemp = 0, LineNumIndexTemp = CurSymPos-1;//行号就是标识符所处的行号
        int dim = 0;//维数
        /*symr*/
        while(SymbolList[CurSymPos] == LBRACK){//LBRACK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            ConstExp();
            if(SymbolList[CurSymPos] == RBRACK){//RBRACK
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                /*syml*/
                dim = dim+1;//读到] 维数+1;
                if(dim == 1){
                    DataTypeIdTemp = 1;
                }
                else if(dim == 2){
                    DataTypeIdTemp = 2;
                }
                /*symr*/
            }
            else{
                Error(EK);
                /*缺少右中括号加判断*/
                /*syml*/
                dim = dim+1;//读到] 维数+1;
                if(dim == 1){
                    DataTypeIdTemp = 1;
                }
                else if(dim == 2){
                    DataTypeIdTemp = 2;
                }
                /*symr*/
            }
        }
        /*插入符号表*/
        SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, DECLFLAG, NULL);
        if(SymbolList[CurSymPos] == ASSIGN){//ASSIGN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            ConstInitVal();
        }

    }
    if(ErrorPrintFlag)
    printf("<ConstDef>\n");
}
/*标识符*/
//Ident
void Ident(){
    if(SymbolList[CurSymPos] == IDENFR) {//IDENFR
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }
	
}
/*常量初值*/
//ConstInitVal → ConstExp  '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
void ConstInitVal(){
    if(SymbolList[CurSymPos] == LBRACE){
    	Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] != RBRACE){
            ConstInitVal();
        }
        while(SymbolList[CurSymPos] == COMMA){
        	Sym_map(SymbolList[CurSymPos]);
        	CurSymPos = CurSymPos+1;
			ConstInitVal();
		}
		if(SymbolList[CurSymPos] == RBRACE){
			Sym_map(SymbolList[CurSymPos]);
        	CurSymPos = CurSymPos+1;
		}
	}
	else{
		ConstExp();
	} 
	if(ErrorPrintFlag)
    printf("<ConstInitVal>\n");
}
/*常量表达式*/
//ConstExp → AddExp
void ConstExp(){
    AddExp();
    if(ErrorPrintFlag)
    printf("<ConstExp>\n");
}
/*加减表达式*/
//AddExp → MulExp | AddExp ('+' | '−') MulExp
//出现左递归
//改写为AddExp → MulExp { ('+'|'-') MulExp }
void AddExp(){
    MulExp();
    if(SymbolList[CurSymPos] == PLUS||SymbolList[CurSymPos] == MINU){
        if(ErrorPrintFlag)
        printf("<AddExp>\n");
	}
    while(SymbolList[CurSymPos] == PLUS||SymbolList[CurSymPos] == MINU){ //18 PLUS 19 MINU
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;

        MulExp();
		if(SymbolList[CurSymPos] == PLUS||SymbolList[CurSymPos] == MINU){
            if(ErrorPrintFlag)
		    printf("<AddExp>\n");
		}
		
    }
    if(ErrorPrintFlag)
    printf("<AddExp>\n");
}
/*乘除模表达式*/
//MulExp → UnaryExp | MulExp ('*' | '/' | '%') UnaryExp
//左递归
//改写后 MulExp → UnaryExp {('*' | '/' | '%') UnaryExp}
void MulExp(){
    UnaryExp();

    if(SymbolList[CurSymPos] == MULT||SymbolList[CurSymPos] == DIV||SymbolList[CurSymPos] == MOD){
        if(ErrorPrintFlag)
        printf("<MulExp>\n");
	}
    while(SymbolList[CurSymPos] == MULT||SymbolList[CurSymPos] == DIV||SymbolList[CurSymPos] == MOD){// * / %
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;

        UnaryExp();
        if(SymbolList[CurSymPos] == MULT||SymbolList[CurSymPos] == DIV||SymbolList[CurSymPos] == MOD){
            if(ErrorPrintFlag)
            printf("<MulExp>\n");
		}
    }
    if(ErrorPrintFlag)
    printf("<MulExp>\n");

}
/*一元表达式*/
//PrimaryExp | Ident '(' [FuncRParams] ')' | UnaryOp UnaryExp
// [FuncRParams];
// First[PrimaryExp] = {(, IDENFR, INTCON} 
// ���ڽ��� 
void UnaryExp(){
    /*Ident '(' [FuncRParams] ')'*/
    if(SymbolList[CurSymPos] == IDENFR&&SymbolList[CurSymPos+1] ==LPARENT){//IDENFR
        Ident();
        /*syml*/
        int NameIndexTemp = CurSymPos-1, IdentTypeIdTemp = 1, DataTypeIdTemp = -1, LineNumIndexTemp = CurSymPos-1;
        /*symr*/
        /*调用函数，查找符号表对应的声明*/
        SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, CALLFLAG, NULL);
        if(DataTypeIdTemp == 3){
            RParmDataType = 3;
        }
        int FuncDefPosInSym = SymTabFind(TokenList[NameIndexTemp], CALLFLAG);//获取函数声明在栈式符号表的位置
        int RParmNum = 0;//记录实参个数
        if(SymbolList[CurSymPos] == LPARENT){//LPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            if(SymbolList[CurSymPos] != RPARENT){

                FuncRParams(RParmNum, StackSymbolTable[FuncDefPosInSym].ExtraSymbol->FParmList, StackSymbolTable[FuncDefPosInSym].ExtraSymbol->FParmNum);//函数实参表
            }
            if(SymbolList[CurSymPos] == RPARENT){//RPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
            }
            else{
                Error(EJ);
                /*不需要加判断*/
            }
        }
        /*判断函数参数个数是否匹配*/
        if(StackSymbolTable[FuncDefPosInSym].ExtraSymbol->FParmNum != RParmNum){
            Error(ED);
        }
		
    }
	else if(SymbolList[CurSymPos] == LPARENT||SymbolList[CurSymPos] == IDENFR||SymbolList[CurSymPos] == INTCON){
        PrimaryExp();
    }
    else if(SymbolList[CurSymPos] == PLUS||SymbolList[CurSymPos] == MINU||SymbolList[CurSymPos] == NOT){// + - !
        UnaryOp();
        UnaryExp();
    }
    if(ErrorPrintFlag)
    printf("<UnaryExp>\n");

}
/*单目运算符*/
//UnaryOp → '+' | '−' | '!'
void UnaryOp(){
    if(SymbolList[CurSymPos] == PLUS||SymbolList[CurSymPos] == MINU||SymbolList[CurSymPos] == NOT){// + - !
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }
    if(ErrorPrintFlag)
    printf("<UnaryOp>\n");
}
/*基本表达式*/
//PrimaryExp → '(' Exp ')' | LVal | Number
void PrimaryExp(){
    if(SymbolList[CurSymPos] == LPARENT){//LPARENT
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        Exp();
        if(SymbolList[CurSymPos] == RPARENT){//RPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
        }
        else{
            Error(EJ);
        }
    }
    else if(SymbolList[CurSymPos] == INTCON){//INTCON
        Number();
    }
    else{
        int IdentTypeIdTemp = 0;
        LVal(IdentTypeIdTemp);
    }
    if(ErrorPrintFlag)
    printf("<PrimaryExp>\n");
}
/*表达式*/
//Exp → AddExp
void Exp(){
    if(SymbolList[CurSymPos-1] == RETURNTK){
        IsVoidReturn = 0;
    }

    AddExp();
    if(ErrorPrintFlag)
    printf("<Exp>\n");

}
/*左值表达式*/
//LVal → Ident {'[' Exp ']'}
void LVal(int& IdentTypeIdTemp){
    Ident();
    /*syml*/
    int NameIndexTemp = CurSymPos-1, DataTypeIdTemp = -1, LineNumIndexTemp = CurSymPos-1;//行号就是标识符所处的行
    /*symr*/
    /*调用变量，查找符号表,获得变量信息， 将DataTypeIdTemp作为维数*/
    SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, CALLFLAG, NULL);//若

    /*对于实参维数的判断,因为获得变量声明时的数据类型，调用时，若遇见一个右中括号说明，将维数减一 如int a[],func(a), 代表a是1维， func(a[]), 代表a是0维*/
    while(SymbolList[CurSymPos] == LBRACK){//LBRACK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        Exp();
        if(SymbolList[CurSymPos] == RBRACK){//RBRACK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            DataTypeIdTemp = DataTypeIdTemp -1;//遇见一个右中括号降维
        }
        else{
            /*不需要加判断*/
            Error(EK);
        }
    }
    RParmDataType = DataTypeIdTemp;
    if(ErrorPrintFlag)
    printf("<LVal>\n");
}

/*数字*/
//Number → IntConst
void Number(){
    if(SymbolList[CurSymPos] == INTCON){//INTCON
        IntConst();
    }
    if(ErrorPrintFlag)
    printf("<Number>\n");
}
/*IntConst*/
void IntConst(){
    if(SymbolList[CurSymPos] == INTCON){//INTCON
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }

}
/*函数实参表*/
//FuncRParams → Exp { ',' Exp }
void FuncRParams(int& RParmNum, int FParamList[], int FParamNum){
    int i=0, n = FParamNum;

    Exp();//若进入Lval，更改实参数类型
    /*实参和形参类型是否匹配*/
    if(FParamList[i] != RParmDataType){
        Error(EE);
    }
    i++;
    RParmDataType = 0;
    RParmNum = RParmNum + 1;
    while(SymbolList[CurSymPos] == COMMA){//COMMA
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        Exp();
        if(FParamList[i] != RParmDataType){//若形参和实参参数类型相等
            Error(EE);
        }
        i++;
        RParmDataType = 0;//保持不进入Lval为0维
        RParmNum = RParmNum + 1;
    }
    if(ErrorPrintFlag)
    printf("<FuncRParams>\n");
}
/*变量声明*/
//VarDecl → BType VarDef { ',' VarDef } ';'
//EI
void VarDecl(){
    if(SymbolList[CurSymPos] == INTTK){
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == IDENFR){//IDENFR Ԥ����ident
            VarDef();
            while(SymbolList[CurSymPos] == COMMA){//COMMA
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;

                VarDef();
            }
            if(SymbolList[CurSymPos] == SEMICN){//SEMICN
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
            }
            else{
                /*不需要加判断*/
                Error(EI);
            }
        }
    }
    if(ErrorPrintFlag)
        printf("<VarDecl>\n");
}

/*变量定义*/
//VarDef → Ident { '[' ConstExp ']' } | Ident { '[' ConstExp ']' } '=' InitVal
void VarDef(){
    if(SymbolList[CurSymPos] == IDENFR){
        Ident();
        /*syml*/
        int NameIndexTemp = CurSymPos-1, IdentTypeIdTemp = 3, DataTypeIdTemp = 0, LineNumIndexTemp = CurSymPos-1;//行号就是标识符所处的行号
        int dim = 0;//维数
        /*symr*/
        while(SymbolList[CurSymPos] == LBRACK ){//LBRACK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            ConstExp();
            if(SymbolList[CurSymPos] == RBRACK){//RBRACK
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                /*syml*/
                dim = dim+1;//读到] 维数+1;
                if(dim == 1){
                    DataTypeIdTemp = 1;
                }
                else if(dim == 2){
                    DataTypeIdTemp = 2;
                }
                /*symr*/
            }
            else{
                /*缺少右中括号加判断*/
                Error(EK);
                /*syml*/
                dim = dim+1;//读到] 维数+1;
                if(dim == 1){
                    DataTypeIdTemp = 1;
                }
                else if(dim == 2){
                    DataTypeIdTemp = 2;
                }
                /*symr*/
            }
        }
        /*插入符号表*/
        SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, DECLFLAG, NULL);
        if(SymbolList[CurSymPos] == ASSIGN){//ASSIGN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            InitVal();
        }
    }

    if(ErrorPrintFlag)
    printf("<VarDef>\n");
}

/*变量初值*/
//InitVal → Exp | '{' [ InitVal { ',' InitVal } ] '}'
void InitVal(){
    if(SymbolList[CurSymPos] == LBRACE){//LBRACE
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;


        InitVal();
        while(SymbolList[CurSymPos] == COMMA){//COMMA
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            InitVal();
        }
        if(SymbolList[CurSymPos] == RBRACE){//RBRACE
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

        }
    }
    else{
        Exp();
    }
    if(ErrorPrintFlag)
    printf("<InitVal>\n");
}

/*函数定义*/
// FuncDef → FuncType Ident '(' [FuncFParams] ')' Block
void FuncDef(){
    if(SymbolList[CurSymPos] == INTTK){//INTTK
        FuncType();
        if(SymbolList[CurSymPos] == IDENFR){//INDEFR
            Ident();
            /*syml*/
            OtherSymbol* ExtraSymbol = new OtherSymbol;
            int NameIndexTemp = CurSymPos-1, IdentTypeIdTemp = 1, DataTypeIdTemp = 0, LineNumIndexTemp = CurSymPos-1;//行号就是标识符所处的行
            /*symr*/
            /*插入符号表*/
            SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, DECLFLAG, ExtraSymbol);
            /*定位*/
            SymTabLoc((int)StackSymbolTable.size());

            if(SymbolList[CurSymPos] == LPARENT){//LPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;

                if(SymbolList[CurSymPos] != RPARENT){
                    /*syml*/
                    int FParmNum = 0;
                    /*symr*/
                    FuncFParams(FParmNum, ExtraSymbol);//获取函数形参个数和各个形参的数据类型
                    /*syml*/
                    ExtraSymbol->FParmNum = FParmNum;
                    /*symr*/
                }
                else{
                    /*syml*/
                    ExtraSymbol->FParmNum = 0;
                    /*symr*/
                }
                if(SymbolList[CurSymPos] == RPARENT){//RPARENT
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                }
                else{
                    Error(EJ);
                    //无后续分析，不需要加判断
                }
                IsIntReturn = 0;
                Block();
                if(IsIntReturn == 0){
                    Error(EG);
                }
            }
        }

    }
	else if(SymbolList[CurSymPos] == VOIDTK){
		FuncType();
        if(SymbolList[CurSymPos] == IDENFR){//INDEFR
            Ident();
            /*syml*/
            OtherSymbol* ExtraSymbol = new OtherSymbol;
            int NameIndexTemp = CurSymPos-1, IdentTypeIdTemp = 1, DataTypeIdTemp = 3, LineNumIndexTemp = CurSymPos-1;//行号就是标识符所处的行号
            /*symr*/
            /*插入符号表*/
            SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, DECLFLAG, ExtraSymbol);
            /*定位*/
            SymTabLoc((int)StackSymbolTable.size());

            if(SymbolList[CurSymPos] == LPARENT){//LPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                if(SymbolList[CurSymPos] != RPARENT){
                    /*syml*/
                    int FParmNum = 0;
                    /*symr*/
                    FuncFParams(FParmNum, ExtraSymbol);

                    /*syml*/
                    ExtraSymbol->FParmNum = FParmNum;
                    /*symr*/
                }
                else{
                    /*syml*/
                    ExtraSymbol->FParmNum = 0;
                    /*symr*/
                }

                if(SymbolList[CurSymPos] == RPARENT){//RPARENT
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                }
                else{
                    Error(EJ);
                }

                IsVoidReturn = 1;
                Block();
                if(IsVoidReturn == 0){
                    Error(EF);
                }

            }
        }
	}

    if(ErrorPrintFlag)
    printf("<FuncDef>\n");
}

/*函数类型*/
//FuncType → 'void' | 'int'
void FuncType(){
    if(SymbolList[CurSymPos] == VOIDTK||SymbolList[CurSymPos] == INTTK){//VOIDTK INTTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }
    if(ErrorPrintFlag)
    printf("<FuncType>\n");
}

/*函数形参表*/
//FuncFParams → FuncFParam { ',' FuncFParam }
void FuncFParams(int& FParmNum, OtherSymbol* ExtraSymbol){
    int FParamDataType = 0;
    FuncFParam(FParamDataType);
    ExtraSymbol->FParmList[FParmNum++] = FParamDataType;
    /*保持0维*/
    FParamDataType = 0;
    while(SymbolList[CurSymPos] == COMMA){//COMMA
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        FuncFParam(FParamDataType);
        ExtraSymbol->FParmList[FParmNum++] = FParamDataType;
        FParamDataType = 0;
    }
    if(ErrorPrintFlag)
    printf("<FuncFParams>\n");
}

/*函数形参*/
//FuncFParam → BType Ident ['[' ']' { '[' ConstExp ']' }]
void FuncFParam(int& FParamDataType){
    if(SymbolList[CurSymPos] == INTTK){//INTTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == IDENFR){
            Ident();

            /*syml*/
            int FParamNameIndex = CurSymPos-1, FParamIdentType = 4, FParamLineNumIndex = CurSymPos-1;//FparamDataType可以直接当作维数0-2,行号就是标识符所处的行号
            /*symr*/

            if(SymbolList[CurSymPos] == LBRACK){//LBRACK
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                if(SymbolList[CurSymPos] == RBRACK){//RBRACK
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                    /*syml*/
                    FParamDataType = FParamDataType + 1;//维数+1 = 1
                    /*symr*/
                    while(SymbolList[CurSymPos] == LBRACK){//LBRACK
                        Sym_map(SymbolList[CurSymPos]);
                        CurSymPos = CurSymPos+1;

                        ConstExp();
                        if(SymbolList[CurSymPos] == RBRACK){//RBRACK
                            Sym_map(SymbolList[CurSymPos]);
                            CurSymPos = CurSymPos+1;
                            /*syml*/
                            FParamDataType = FParamDataType + 1;//维数+1 = 2
                            /*symr*/
                        }
                        else{
                            /*缺少右中括号加判断*/
                            Error(EK);
                            /*syml*/
                            FParamDataType = FParamDataType + 1;//维数+1 = 2
                            /*symr*/
                        }
                    }
                }
                else{
                    /*缺少右中括号加判断*/
                    Error(EK);
                    /*syml*/
                    FParamDataType = FParamDataType + 1;//维数+1 = 1
                    /*symr*/
                    while(SymbolList[CurSymPos] == LBRACK){//LBRACK
                        Sym_map(SymbolList[CurSymPos]);
                        CurSymPos = CurSymPos+1;

                        ConstExp();
                        if(SymbolList[CurSymPos] == RBRACK){//RBRACK
                            Sym_map(SymbolList[CurSymPos]);
                            CurSymPos = CurSymPos+1;
                            /*syml*/
                            FParamDataType = FParamDataType + 1;//维数+1 = 2
                            /*symr*/
                        }
                        else{
                            /*缺少右中括号加判断*/
                            Error(EK);
                            /*syml*/
                            FParamDataType = FParamDataType + 1;//维数+1 = 2
                            /*symr*/
                        }
                    }
                }
            }
            /*将形参变量插入符号表*/
            SymTabInsert(FParamNameIndex, FParamIdentType, FParamDataType, FParamLineNumIndex, DECLFLAG, NULL);
        }
    }
    if(ErrorPrintFlag)
    printf("<FuncFParam>\n");
}

/*语句块*/
//Block → '{' { ConstDecl | VarDecl | Stmt } '}'
//BlockItem →
void Block(){
    if(SymbolList[CurSymPos] == LBRACE){//LBRACE
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        while(SymbolList[CurSymPos] == CONSTTK||SymbolList[CurSymPos] == INTTK||SymbolList[CurSymPos] == IDENFR||
			  SymbolList[CurSymPos] == BREAKTK||SymbolList[CurSymPos] == CONTINUETK||SymbolList[CurSymPos] == IFTK||
			  SymbolList[CurSymPos] == ELSETK||SymbolList[CurSymPos] == PRINTFTK||SymbolList[CurSymPos] == RETURNTK||
			  SymbolList[CurSymPos] == LBRACE||SymbolList[CurSymPos] == LPARENT||SymbolList[CurSymPos] == INTCON||
			  SymbolList[CurSymPos] == WHILETK||SymbolList[CurSymPos] == SEMICN||SymbolList[CurSymPos] == MINU||
			  SymbolList[CurSymPos] == NOT||SymbolList[CurSymPos] == PLUS){
            if(SymbolList[CurSymPos] == CONSTTK){
                ConstDecl();
            }
            else if(SymbolList[CurSymPos] == INTTK){

                VarDecl();
            }
            else{
            	Stmt(); 
			} 
        }
        if(SymbolList[CurSymPos] == RBRACE){//RBRACE
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

        }

    }
    SymTabReLoc();
    if(ErrorPrintFlag)
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
    if(SymbolList[CurSymPos] == IFTK){//IFTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == LPARENT){//LPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            Cond();
            if(SymbolList[CurSymPos] == RPARENT){//RPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                /*定位{*/
                /*if(SymbolList[CurSymPos] == LBRACE){
                    SymTabLoc((int)StackSymbolTable.size());
                }*/
                Stmt();

                if(SymbolList[CurSymPos] == ELSETK){//ELSETK
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                    if(SymbolList[CurSymPos] == LBRACE){
                        SymTabLoc((int)StackSymbolTable.size());
                    }

                    Stmt();

                }
            }
            else{
                Error(EJ);
                //缺少右括号后，正常进入else
                if(SymbolList[CurSymPos] == LBRACE){
                    SymTabLoc((int)StackSymbolTable.size());
                }
                Stmt();

                if(SymbolList[CurSymPos] == ELSETK){//ELSETK
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                    if(SymbolList[CurSymPos] == LBRACE){
                        SymTabLoc((int)StackSymbolTable.size());
                    }
                    Stmt();

                }
            }
        }
        IsIntReturn = 0;
    }
    else if(SymbolList[CurSymPos] == WHILETK){//WHILETK
        /*错误处理：while语句判断*/
        IsWhile.push_back(1);

        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == LPARENT){//LPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            Cond();
            if(SymbolList[CurSymPos] == RPARENT){//RPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                /*if(SymbolList[CurSymPos] == LBRACE){
                    SymTabLoc((int)StackSymbolTable.size());
                }*/
                Stmt();
            }
            else{
                Error(EJ);
                if(SymbolList[CurSymPos] == LBRACE){
                    SymTabLoc((int)StackSymbolTable.size());
                }
                Stmt();
            }
        }
        /*错误处理：while语句判断*/
        IsWhile.pop_back();
    }
    else if(SymbolList[CurSymPos] == BREAKTK){//BREAKTK
        /*Error：在非循环块中使用break和continue语句*/
        if(IsWhile.size() == 0){
            Error(EM);
        }
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == SEMICN){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
        }
        else{
            /*不需要加判断*/
            Error(EI);
        }

    }
    else if(SymbolList[CurSymPos] == CONTINUETK){//CONTINUETK
        /*Error：在非循环块中使用break和continue语句*/
        if(IsWhile.size() == 0){
            Error(EM);
        }
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == SEMICN){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
        }
        else{
            /*不需要加判断*/
            Error(EI);
        }
    }
    else if(SymbolList[CurSymPos] == RETURNTK){//RETURNTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] != SEMICN){
            Exp();
		} 
		
        if(SymbolList[CurSymPos] == SEMICN){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
        }
        else{
            /*不需要加判断*/
            Error(EI);
            if(SymbolList[CurSymPos-1] == RETURNTK){
                IsVoidReturn = 1;
            }
        }
        /*函数中存在return*/
        IsIntReturn = 1;
    }
    else if(SymbolList[CurSymPos] == PRINTFTK){//PRINTFTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == LPARENT){//LPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            int FormatCNum = 0, ExpNum = 0;//格式%d字符个数
            FormatString(FormatCNum);
            while(SymbolList[CurSymPos]== COMMA){//COMMA
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                Exp();
                ExpNum = ExpNum + 1;
            }
            /*printf格式字符和表达式不匹配*/
            if(ExpNum != FormatCNum){
                Error(EL);
            }
            if(SymbolList[CurSymPos] == RPARENT){//RPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                if(SymbolList[CurSymPos] == SEMICN){//SEMICN
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                }
                else{
                    /*不需要加判断*/
                    Error(EI);
                }
            }
            else{
                /*缺少右小括号*/
                Error(EJ);
                if(SymbolList[CurSymPos] == SEMICN){//SEMICN
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                }
                else{
                    /*不需要加判断*/
                    Error(EI);
                }
            }
        }
    }
    else if(SymbolList[CurSymPos] == IDENFR&&SymbolList[CurSymPos+1] == LPARENT){//exp Ident '(' [FuncRParams] );
    	Exp();
    	if(SymbolList[CurSymPos] == SEMICN){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
        }
    	else{
            /*不需要加判断*/
    	    Error(EI);
    	}
    	
	}
    else if(SymbolList[CurSymPos] == IDENFR){//IDENTFR    LVAL
        int StmtCurPos = CurSymPos;
        int Expflag = 1;
		while(SymbolList[StmtCurPos] != SEMICN){
			if(SymbolList[StmtCurPos] == ASSIGN){
				Expflag = 0;
				break;
			}
			else{
				Expflag = 1;
			}
			StmtCurPos = StmtCurPos+1;
		}
		if(Expflag == 0){
			int IdentTypeIdTemp = 0;
		    LVal(IdentTypeIdTemp);
        	if(SymbolList[CurSymPos] == ASSIGN){//ASSIGN
        	    /*不能改变常量的值*/
        	    if(IdentTypeIdTemp == 2){
        	        Error(EH);
        	    }
        	    Sym_map(SymbolList[CurSymPos]);
        	    CurSymPos = CurSymPos+1;
        	    if(SymbolList[CurSymPos] == GETINTTK){//GETINTTK
        	        Sym_map(SymbolList[CurSymPos]);
        	        CurSymPos = CurSymPos+1;
        	        if(SymbolList[CurSymPos] == LPARENT){//LPARENT
        	            Sym_map(SymbolList[CurSymPos]);
        	            CurSymPos = CurSymPos+1;
        	            if(SymbolList[CurSymPos] == RPARENT){//RPARENT
        	                Sym_map(SymbolList[CurSymPos]);
        	                CurSymPos = CurSymPos+1;
        	                if(SymbolList[CurSymPos] == SEMICN){//SEMICN
        	                    Sym_map(SymbolList[CurSymPos]);
         	                   	CurSymPos = CurSymPos+1;
        	                }
        	                else{
                                /*不需要加判断*/
        	                    Error(EI);
        	                }
            	        }
        	            else{
        	                Error(EJ);
        	                /*缺少右小括号*/
                            if(SymbolList[CurSymPos] == SEMICN){//SEMICN
                                Sym_map(SymbolList[CurSymPos]);
                                CurSymPos = CurSymPos+1;
                            }
                            else{
                                /*不需要加判断*/
                                Error(EI);
                            }
        	            }
            	    }
            	}
            	else{
            	    Exp();
            	    if(SymbolList[CurSymPos] == SEMICN){//SEMICN
            	        Sym_map(SymbolList[CurSymPos]);
            	        CurSymPos = CurSymPos+1;
            	    }
            	    else{
                        /*不需要加判断*/
            	        Error(EI);
            	    }
            	}
			}
		
        }
        else{
			Exp();
            if(SymbolList[CurSymPos] == SEMICN){//SEMICN
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
            }
            else{
                /*不需要加判断*/
                Error(EI);
            }

        }
        
    }
	else if(SymbolList[CurSymPos] == LBRACE){
	    SymTabLoc((int)StackSymbolTable.size());
	    Block();

    }
    else{
    	if(SymbolList[CurSymPos] != SEMICN) {
            Exp();
        }

    	if(SymbolList[CurSymPos] == SEMICN){//SEMICN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
    	}
    	else{
            /*不需要加判断*/
            Error(EI);
    	}
	}
    if(ErrorPrintFlag)
    printf("<Stmt>\n");
}
/*字符串*/
void FormatString(int& FormatCNum){
    /*含有非法字符*/
    int IsFormatString = 1, n = TokenList[CurSymPos].size();
    for(int i=0; i<n; i++){
        if( TokenList[CurSymPos][i] != 32&&TokenList[CurSymPos][i] != 33 &&TokenList[CurSymPos][i] != 37 &&
        (TokenList[CurSymPos][i] < 40 || TokenList[CurSymPos][i] > 126)){
            IsFormatString = 0;
        }
        else if(TokenList[CurSymPos][i] == '%' ){
            if(TokenList[CurSymPos][i+1] == 'd'){
                FormatCNum = FormatCNum + 1;
            }
            else {
                IsFormatString = 0;
            }
        }
        else{
            if(TokenList[CurSymPos][i] == '\\' && TokenList[CurSymPos][i+1] != 'n'){
                IsFormatString = 0;
            }

        }
    }

    if(SymbolList[CurSymPos] == STRCON && IsFormatString == 1){//STRCON
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }
    else if(SymbolList[CurSymPos] == STRCON && IsFormatString == 0){
        Error(EA);
    }


}
/*条件表达式*/
//Cond → LOrExp
void Cond(){
    LOrExp();
    if(ErrorPrintFlag)
    printf("<Cond>\n");
}

/*逻辑或表达式*/
//LOrExp → LAndExp | LOrExp '||' LAndExp
//左递归
//改写为LOrExp → LAndExp {'||' LAndExp}
void LOrExp(){
    LAndExp();
    if(SymbolList[CurSymPos] == OR){
        if(ErrorPrintFlag)
    	printf("<LOrExp>\n");
	}
    while(SymbolList[CurSymPos] == OR){//OR
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        LAndExp();
        if(SymbolList[CurSymPos] == OR){
            if(ErrorPrintFlag)
    		printf("<LOrExp>\n");
		}
		
    }
    if(ErrorPrintFlag)
    printf("<LOrExp>\n");
}

/*逻辑与表达式*/
//LAndExp → EqExp | LAndExp '&&' EqExp
//左递归
//改写为LAndExp → EqExp { '&&' EqExp }
void LAndExp(){
    EqExp();
    if(SymbolList[CurSymPos] == AND){
        if(ErrorPrintFlag)
        	printf("<LAndExp>\n");
    }
    while(SymbolList[CurSymPos] == AND){//AND
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        EqExp();
        if(SymbolList[CurSymPos] == AND){
            if(ErrorPrintFlag)
        	printf("<LAndExp>\n");
		}
		
    }
    if(ErrorPrintFlag)
    printf("<LAndExp>\n");
}

/*相等性表达式*/
//EqExp → RelExp | EqExp ('==' | '!=') RelExp
//左递归
//改写后EqExp → RelExp { ('==' | '!=') RelExp }
void EqExp(){
    RelExp();
    if(SymbolList[CurSymPos] == EQL||SymbolList[CurSymPos] == NEQ){
        if(ErrorPrintFlag)
        printf("<EqExp>\n");
	}
    while(SymbolList[CurSymPos] == EQL||SymbolList[CurSymPos] == NEQ){//EQL //NEQ
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        RelExp();
        if(SymbolList[CurSymPos] == EQL||SymbolList[CurSymPos] == NEQ){
            if(ErrorPrintFlag)
            printf("<EqExp>\n");
		}
    }
    if(ErrorPrintFlag)
    printf("<EqExp>\n");
}

/*关系表达式*/
//RelExp → AddExp | RelExp ('<' | '>' | '<=' | '>=') AddExp
//左递归
//改写为RelExp → AddExp { ('<' | '>' | '<=' | '>=') AddExp }
void RelExp(){
    AddExp();
    if(SymbolList[CurSymPos] == GRE||SymbolList[CurSymPos] == LSS||SymbolList[CurSymPos] == GEQ||SymbolList[CurSymPos] == LEQ){
        if(ErrorPrintFlag)
        printf("<RelExp>\n");
	}
    while(SymbolList[CurSymPos] == GRE||SymbolList[CurSymPos] == LSS||SymbolList[CurSymPos] == GEQ||SymbolList[CurSymPos] == LEQ){//GRE LSS GEQ LEQ
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        AddExp();
        if(SymbolList[CurSymPos] == GRE||SymbolList[CurSymPos] == LSS||SymbolList[CurSymPos] == GEQ||SymbolList[CurSymPos] == LEQ){
            if(ErrorPrintFlag)
            printf("<RelExp>\n");
		}
    }
    if(ErrorPrintFlag)
    printf("<RelExp>\n");

}

/*主函数定义*/

void MainFuncDef(){
	
	if(SymbolList[CurSymPos] == MAINTK){
		Sym_map(SymbolList[CurSymPos]);
		CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == LPARENT){
        	Sym_map(SymbolList[CurSymPos]);
        	CurSymPos = CurSymPos+1;
        	if(SymbolList[CurSymPos] == RPARENT){
        		Sym_map(SymbolList[CurSymPos]);
        		CurSymPos = CurSymPos+1;
        		/*定位分程序索引表*/
        		SymTabLoc((int)StackSymbolTable.size());
        		/**/
        		IsIntReturn = 0;
        		Block();
        		if(IsIntReturn == 0){
        		    Error(EG);
        		}
			}
        	else{
        	    Error(EJ);
                /*缺少右小括号*/
                SymTabLoc((int)StackSymbolTable.size());
                Block();
        	}
		}
	}
    if(ErrorPrintFlag)
	cout << "<MainFuncDef>" << endl;
}
