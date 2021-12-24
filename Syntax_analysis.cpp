//
// Created by 86156 on 2021-10-09.
// 以下语法成分不需要出现<BlockItem> <Decl> <BType>
// 必须补全，但是在语法分析不必输出
//
// 语义分析在语法分析的基础上添加属性和动作
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Lexical_analysi.h"
#include "Syntax_analysis.h"
#include "Semantic_analysis.h"
#include "Interpretation_execution.h"
#include "Table.h"
#include "Error.h"
using namespace std;


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
//ConstDecl → 'const' BType ConstDef {',' ConstDef } ';'
//错误 HI
//
void ConstDecl(){

    if(SymbolList[CurSymPos] == CONSTTK){//CONSTTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;

        if(SymbolList[CurSymPos] == INTTK){//INTTK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            int Attr_DataType = Int;

            ConstDef(Attr_DataType);

            while(SymbolList[CurSymPos] == COMMA){//COMMA
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;

                ConstDef(Attr_DataType);

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
/*BType*/
void BType(){
    if(SymbolList[CurSymPos] == INTTK) {//INTTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos + 1;
    }
}
/*常量定义*/
//ConstDef → Ident { '[' ConstExp ']' } '=' ConstInitVal
void ConstDef(int Attr_DataType){
    if(SymbolList[CurSymPos] == IDENFR){//IDENFR
        int Attr_Index;//标识符所在类别码数组下标，根据这下标，可获得对应名字，行号
        Ident(Attr_Index);

        IntDataTable[IntDataTableTop++] = 0;//初始未赋初值都设为0

        /*syml*/
        int NameIndexTemp = Attr_Index, IdentTypeIdTemp = 2, DataTypeIdTemp = Attr_DataType, LineNumIndexTemp = Attr_Index;//行号就是标识符所处的行号
        int dim = 0;//维数
        // 初始化数组模板表,记录数组维数,对应维数的上下界以及计算对应P[i]
        ArrayInformationTab* ArrayInformation = new ArrayInformationTab;
        int ArrayTabTop = 0;
        int ArrayTempBeginIndex = 0;
        if(SymbolList[CurSymPos] == LBRACK){
            //ArrayTempBeginIndex = ArrayTempTop;//每个数组模板表长度为8，初始位置8位递增
            Sem_initAry_tempbegin();
            //数组模板表中初始化维数
            //ArraySArea[ArraySAreaTop] = DataTypeIdTemp;//DataTypeIdTemp对应维数
            //ArrayInformation->ArrayTemp[ArrayTabTop++] = &ArraySArea[ArraySAreaTop++];
            //ArrayTempArea[ArrayTempTop++] = DataTypeIdTemp;
            //初始化数组开始下标
            //ArraySArea[ArraySAreaTop] = 0;
            //ArrayInformation->ArrayTemp[ArrayTabTop++] = &ArraySArea[ArraySAreaTop++];
            //ArrayTempArea[ArrayTempTop++] = 0;
        }
        /*symr*/
        //加载
        while(SymbolList[CurSymPos] == LBRACK){//LBRACK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            ConstExp();
            Sem_initAry_templvup();
            //初始化在IntDataTab 下界上界和对应P[i]
            //ArraySArea[ArraySAreaTop] = 0;//下界
            //ArrayInformation->ArrayTemp[ArrayTabTop++] = &ArraySArea[ArraySAreaTop++];
            //ArrayTempArea[ArrayTempTop++] = 0;
            //ArraySArea[ArraySAreaTop] = 0;//上界
            //ArrayInformation->ArrayTemp[ArrayTabTop++] = &ArraySArea[ArraySAreaTop++];
            //ArrayTempArea[ArrayTempTop++] = 0;
            //更改对应上界
            //Sem_gettop(&ArrayTempArea[ArrayTempTop-1]);//将运行栈顶的exp加载到上界位置
            //ArraySArea[ArraySAreaTop] = 0;//P[i]
            //ArrayInformation->ArrayTemp[ArrayTabTop++] = &ArraySArea[ArraySAreaTop++];
            //ArrayTempArea[ArrayTempTop++] = 0;

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
        //计算对应的P(i)
        //i=n p(i) = 1
        //i<n p(i) = ((U(i+1)-L(i+1))+1) 之和
        if(DataTypeIdTemp == Array1){
            //*ArrayInformation->ArrayTemp[4] = 1;
            IntDataTable[IntDataTableTop++] = Array1;
            Sem_getAry_pi(&IntDataTable[IntDataTableTop-1]);
            //ArrayTempArea[ArrayTempBeginIndex+4] = 1;//i=n p(i) = 1
        }
        else if(DataTypeIdTemp == Array2){
            //*ArrayInformation->ArrayTemp[7] = 1;
            IntDataTable[IntDataTableTop++] = Array2;
            Sem_getAry_pi(&IntDataTable[IntDataTableTop-1]);
            //ArrayTempArea[ArrayTempBeginIndex+7] = 1;//i=n=2 p(2) = 1
            //Sem_load(&ArrayTempArea[ArrayTempBeginIndex+6]);//把U2加载到
            //Sem_getAry_pi(&ArrayTempArea[ArrayTempBeginIndex+4]);//计算p(1)值
        }
        SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, DECLFLAG, NULL, ArrayInformation, &IntDataTable[IntDataTableTop-1]);

        //向数据栈中加载NameIndex， FuncIndex, ArrayTempIndex, Value
        IntDataTable[IntDataTableTop++] = NameIndexTemp;
        Sem_load(&IntDataTable[IntDataTableTop-1]);//变量名
        IntDataTable[IntDataTableTop++] = 0;
        Sem_load(&IntDataTable[IntDataTableTop-1]);//函数声明Pcode下标：不是函数，对用下标位置为0
        if(DataTypeIdTemp != Array1&&DataTypeIdTemp != Array2){
            IntDataTable[IntDataTableTop++] = -1;// 不是数组置-1
        }
        else{
            IntDataTable[IntDataTableTop++] = 0;// 是数组置模板初始位置
            Sem_getAry_tempBegin(&IntDataTable[IntDataTableTop-1]);
        }
        Sem_load(&IntDataTable[IntDataTableTop-1]);// 对应数组的模板表初始位置ArrayTempIndex：
        IntDataTable[IntDataTableTop++] = 0;
        Sem_load(&IntDataTable[IntDataTableTop-1]);// 变量值： 初值为0
        //将当前变量插入数据栈中
        Sem_dataStackInsert();
        //更改数组模板表中[1]数组在ArraySArea中初始地址位置
        /*if(DataTypeIdTemp == Array1||DataTypeIdTemp == Array2){
            //以IntDataTop作为数组首地址下标
            //*ArrayInformation->ArrayTemp[1] = ArraySAreaTop;
            ArrayTempArea[ArrayTempBeginIndex+1] = ArraySAreaTop;
        }*/
        if(SymbolList[CurSymPos] == ASSIGN){//ASSIGN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            // int Attr_CInitValue = 0;初值不用作为属性，其初值最后应该在栈顶，用sto指令即可

            ConstInitVal();

            // 在0维情况下在赋值，数组直接在constexp中将对应值，放入以当前存储地址开始的intdata表中
            if(DataTypeIdTemp == Int){
            // 声明赋值，参数是CALLFlag，执行该pcode 将
            IntDataTable[IntDataTableTop++] = DECLFLAG;
            Sem_sto(&IntDataTable[IntDataTableTop-1]);
            // printf("%d\n", *StackSymbolTable.back().IntDataAddr);
            }

        }

    }
    if(ErrorPrintFlag)
        printf("<ConstDef>\n");
}
/*标识符*/
//Ident
void Ident(int& Attr_Index){
    if(SymbolList[CurSymPos] == IDENFR) {//IDENFR
        Attr_Index = CurSymPos;//获取标识在类别码数组中的位置
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
    }
	
}
/*常量初值*/
//ConstInitVal → ConstExp | '{' [ ConstInitVal { ',' ConstInitVal } ] '}'
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
        /*每遇见一个初值，都放到intDatatab里，实现数组元素的存储*/
		ConstExp();
		if(StackSymbolTable[StackSymbolTable.size()-1].DataTypeId == Array1 ||
		   StackSymbolTable[StackSymbolTable.size()-1].DataTypeId == Array2 ){
            //ArraySArea[ArraySAreaTop] = 0;
            //Sem_gettop(&ArraySArea[ArraySAreaTop]);//将初值加载到数组元素存储区中
            //ArraySAreaTop++;
            Sem_initCAry_sArea();
		}
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
        int Plus_Minu = SymbolList[CurSymPos];//记录加减表达式符号
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;

        MulExp();
        //动作子程序
        if(Plus_Minu == PLUS){
            Sem_add();
        }
        else{
            Sem_sub();
        }
        //动作子程序

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
        int Mult_Div_Mod = SymbolList[CurSymPos];//记录乘除模表达式符号
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;

        UnaryExp();
        if(Mult_Div_Mod == MULT){
            Sem_mul();
        }
        else if(Mult_Div_Mod == DIV){
            Sem_div();
        }
        else{
            Sem_mod();
        }
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
        int Attr_Index;
        Ident(Attr_Index);
        /*syml*/
        int NameIndexTemp = CurSymPos-1, IdentTypeIdTemp = Func, DataTypeIdTemp = 0, LineNumIndexTemp = CurSymPos-1;
        /*symr*/
        /*调用函数，查找符号表对应的声明*/
        SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, CALLFLAG, NULL, NULL, 0);

        //获取函数声明在栈式符号表的位置
        int FuncDefPosInSym = SymTabFind(TokenList[NameIndexTemp], CALLFLAG);
        int RParmNum = 0;//记录实参个数
        if(SymbolList[CurSymPos] == LPARENT){//LPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            if(SymbolList[CurSymPos] != RPARENT){

                FuncRParams(RParmNum, StackSymbolTable[FuncDefPosInSym].FuncInformation->FParmList, StackSymbolTable[FuncDefPosInSym].FuncInformation->FParmNum, FuncDefPosInSym);//函数实参表
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
        if(StackSymbolTable[FuncDefPosInSym].FuncInformation->FParmNum != RParmNum){
            Error(ED);
        }
        //将返回地址存放在存储区
        IntDataTable[IntDataTableTop++] = PCodeList.size()+3;//3是存放应该返回位置，返回应该是jsr后一个指令，当前指令表加3
        Sem_str(&IntDataTable[IntDataTableTop-1]);
        // 获取函数PCODE表声明位置
        // 此处加生成指令，将上一行3也要修改
        IntDataTable[IntDataTableTop++] = NameIndexTemp;
        Sem_load(&IntDataTable[IntDataTableTop-1]);
        Sem_dataStackFind();
        // 跳转到PcodeList对应函数声明处，执行函数中指令序列
        Sem_jsr();

    }
    /*PrimaryExp*/
	else if(SymbolList[CurSymPos] == LPARENT||SymbolList[CurSymPos] == IDENFR||SymbolList[CurSymPos] == INTCON){
        PrimaryExp();
    }
	/*UnaryOp UnaryExp*/
    else if(SymbolList[CurSymPos] == PLUS||SymbolList[CurSymPos] == MINU||SymbolList[CurSymPos] == NOT){// + - !
        int UnaryOpType = -1;

        UnaryOp(UnaryOpType);

        UnaryExp();
        /*取正或取负*/
        if(UnaryOpType == PLUS){
            Sem_toplus();//+
        }
        else if(UnaryOpType == MINU){
            Sem_tominu();//+
        }
        else if(UnaryOpType == NOT){
            Sem_not();
        }
        UnaryOpNum = 0;
    }
    if(ErrorPrintFlag)
        printf("<UnaryExp>\n");

}
/*单目运算符*/
//UnaryOp → '+' | '−' | '!'
void UnaryOp(int& UnaryOpType){
    if(SymbolList[CurSymPos] == PLUS||SymbolList[CurSymPos] == MINU||SymbolList[CurSymPos] == NOT){// + - !
        UnaryOpType = SymbolList[CurSymPos];
        UnaryOpNum++;
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
        int Attr_NumValue;
        Number(Attr_NumValue);
        //int* Attr_NumValueAddr = &Attr_NumValue;

        IntDataTable[IntDataTableTop++] = Attr_NumValue;
        Sem_loadi(&IntDataTable[IntDataTableTop-1]);
    }
    else{
        int IdentTypeIdTemp = 0;
        int Attr_StackSymIndex = -1;
        int Attr_IsAssignLeft = 0;
        LVal(IdentTypeIdTemp, Attr_StackSymIndex, Attr_IsAssignLeft);
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
void LVal(int& IdentTypeIdTemp, int& Attr_StackSymIndex, int Attr_IsAssignLeft){
    int Attr_Index;//标识符所在类别码数组下标，根据这下标，可获得对应名字，行号
    Ident(Attr_Index);
    /*syml*/
    int NameIndexTemp = Attr_Index, DataTypeIdTemp = -1, LineNumIndexTemp = Attr_Index;//行号就是标识符所处的行
    /*symr*/
    /*调用变量，查找符号表,获得变量信息， 将DataTypeIdTemp作为维数*/

    Attr_StackSymIndex = SymTabFind(TokenList[NameIndexTemp], CALLFLAG);
    DataTypeIdTemp = StackSymbolTable[Attr_StackSymIndex].DataTypeId;
    IdentTypeIdTemp = StackSymbolTable[Attr_StackSymIndex].IdentTypeId;
    //生成寻找数据栈对应变量的指令
    //先加载寻找的变量名字下标
    IntDataTable[IntDataTableTop++] = NameIndexTemp;
    Sem_load(&IntDataTable[IntDataTableTop-1]);
    Sem_dataStackFind();
    /*对于实参维数的判断,因为获得变量声明时的数据类型，调用时，若遇见一个右中括号说明，将维数减一 如int a[],func(a), 代表a是1维， func(a[]), 代表a是0维*/
    int pi = 4;

    int PiIndexInData = IntDataTableTop-1;
    while(SymbolList[CurSymPos] == LBRACK){//LBRACK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        //load pi
        IntDataTable[IntDataTableTop++] = pi;
        Sem_LoadAry_pi(&IntDataTable[IntDataTableTop-1]);
        Exp();
        Sem_mul();
        Sem_swp();
        pi+=3;//p2= p1+3

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
    //printf("%x ", StackSymbolTable[Attr_StackSymIndex].IntDataAddr);
    //等号右边调用值
    if(Attr_IsAssignLeft == 0){

        if(StackSymbolTable[Attr_StackSymIndex].DataTypeId == Int){
            Sem_loadDataIndex();
        }
        else if(StackSymbolTable[Attr_StackSymIndex].DataTypeId == Array1){
            //计算数组元素位置，获得V(1)，运行栈栈顶
            //printf("%d", Attr_StackSymIndex);
            //printf("%d\n",StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[1]);
            //Sem_load(StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[4]);//P(1)
            //Sem_mul();
            //Sem_load(StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[1]);
            if(DataTypeIdTemp == Int){
                Sem_LoadAry_begin();
                Sem_add();
                Sem_getAry_val();
            }
            else if(DataTypeIdTemp == Array1){
                //函数调用，DataTypeIdtemp没有经过中括号
                //将模板表位置加载到栈顶
                Sem_LoadAry_temp();
            }

        }
        else if(StackSymbolTable[Attr_StackSymIndex].DataTypeId == Array2){
            //计算数组元素位置，获得V(2)，运行栈栈顶
            //Sem_load(StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[7]);
            //Sem_mul();
            //Sem_swp();
            //Sem_load(StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[4]);
            //Sem_mul();
            //Sem_add();
            //Sem_load(StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[1]);
            if(DataTypeIdTemp == Int){
                Sem_LoadAry_begin();
                Sem_add();
                Sem_add();
                Sem_getAry_val();
            }
            else if(DataTypeIdTemp == Array1){
                //新生成一个模板表
                Sem_newAry_temp();

            }
            else if(DataTypeIdTemp == Array2){
                //函数调用，DataTypeIdtemp没有经过中括号
                //将模板表位置加载到栈顶
                Sem_LoadAry_temp();
            }

        }
    }
    //左边调用元素地址
    else{
        if(StackSymbolTable[Attr_StackSymIndex].DataTypeId == Int){
            //Sem_loadDataIndex();
        }
        else if(StackSymbolTable[Attr_StackSymIndex].DataTypeId == Array1){
            //计算数组元素位置，获得V(1)，运行栈栈顶
            //printf("%d", Attr_StackSymIndex);
            //printf("%d\n",StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[1]);
            //Sem_load(StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[4]);
            //Sem_LoadAry_pi();
            //Sem_mul();
            Sem_LoadAry_begin();
            //Sem_load(StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[1]);
            Sem_add();
        }
        else if(StackSymbolTable[Attr_StackSymIndex].DataTypeId == Array2){
            //计算数组元素位置，获得V(2)，运行栈栈顶
            //Sem_load(StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[7]);//p2
            //Sem_mul();
            //Sem_swp();
            //Sem_load(StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[4]);//p1
            //Sem_mul();
            //Sem_add();
            //Sem_load(StackSymbolTable[Attr_StackSymIndex].ArrayInformation->ArrayTemp[1]);
            Sem_LoadAry_begin();
            Sem_add();
            Sem_add();
        }
    }
    if(ErrorPrintFlag)
        printf("<LVal>\n");
}

/*数字*/
//Number → IntConst
void Number(int& Attr_NumValue){
    if(SymbolList[CurSymPos] == INTCON){//INTCON
        Attr_NumValue = atoi(TokenList[CurSymPos].c_str());//将数字字符串转换整数
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
void FuncRParams(int& RParmNum, int FParamList[], int FParamNum, int FuncDefPosInSym){
    int i=0, n = FParamNum;

    Exp();//若进入Lval，更改实参数类型

    //当前只考虑Int型情况，则exp（）完成后，运行栈栈顶是实参值，将实参值通过gettop赋给对应函数形参中的值
    //将值存放在运行栈,exp()已经是相当于把值放在运行栈中。

    //Sem_gettop(StackSymbolTable[FuncDefPosInSym].FuncInformation->FParmInDataIndex[RParmNum]);
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
        //Sem_gettop(StackSymbolTable[FuncDefPosInSym].FuncInformation->FParmInDataIndex[RParmNum]);
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
        int Attr_DataType = Int;
        int Attr_IdentType = Var;

        VarDef(Attr_DataType);

        while(SymbolList[CurSymPos] == COMMA){//COMMA
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            VarDef(Attr_DataType);


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
        printf("<VarDecl>\n");
}

/*变量定义*/
//VarDef → Ident { '[' ConstExp ']' } | Ident { '[' ConstExp ']' } '=' InitVal
void VarDef(int Attr_DataType){
    if(SymbolList[CurSymPos] == IDENFR){

        int Attr_Index;//标识符所在类别码数组下标，根据这下标，可获得对应名字，行号
        Ident(Attr_Index);
        IntDataTable[IntDataTableTop++] = 0;//初始未赋初值都设为0
        //printf("%x\n",&IntDataTable[IntDataTableTop-1]);
        /*syml*/
        int NameIndexTemp = Attr_Index, IdentTypeIdTemp = Var, DataTypeIdTemp = Attr_DataType, LineNumIndexTemp = Attr_Index;//行号就是标识符所处的行号
        int dim = 0;//维数
        // 初始化数组模板表,记录数组维数,对应维数的上下界以及计算对应P[i]
        ArrayInformationTab* ArrayInformation = new ArrayInformationTab;
        int ArrayTabTop = 0;
        //int ArrayTempBeginIndex = 0;
        if(SymbolList[CurSymPos] == LBRACK){
            //ArrayTempBeginIndex = ArrayTempTop;//每个数组模板表长度为8，初始位置8位递增
            Sem_initAry_tempbegin();
            //数组模板表中初始化维数
            //ArraySArea[ArraySAreaTop] = DataTypeIdTemp;//DataTypeIdTemp对应维数
            //ArrayInformation->ArrayTemp[ArrayTabTop++] = &ArraySArea[ArraySAreaTop++];
            //ArrayTempArea[ArrayTempTop++] = DataTypeIdTemp;
            //初始化在数组开始下标
            //ArraySArea[ArraySAreaTop] = 0;
            //ArrayInformation->ArrayTemp[ArrayTabTop++] = &ArraySArea[ArraySAreaTop++];
            //ArrayTempArea[ArrayTempTop++] = 0;
        }
        /*symr*/
        while(SymbolList[CurSymPos] == LBRACK ){//LBRACK
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;

            ConstExp();
            Sem_initAry_templvup();
            //初始化在IntDataTab 下界上界和对应P[i]
            //ArraySArea[ArraySAreaTop] = 0;//下界
            //ArrayInformation->ArrayTemp[ArrayTabTop++] = &ArraySArea[ArraySAreaTop++];
            //ArrayTempArea[ArrayTempTop++] = 0;
            //ArraySArea[ArraySAreaTop] = 0;//上界
            //ArrayInformation->ArrayTemp[ArrayTabTop++] = &ArraySArea[ArraySAreaTop++];
            //ArrayTempArea[ArrayTempTop++] = 0;
            //更改对应上界
            //Sem_gettop(&ArrayTempArea[ArrayTempTop-1]);//将运行栈顶的exp加载到上界位置
            //ArraySArea[ArraySAreaTop] = 0;//P[i]
            //ArrayInformation->ArrayTemp[ArrayTabTop++] = &ArraySArea[ArraySAreaTop++];
            //ArrayTempArea[ArrayTempTop++] = 0;

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
        //计算对应的P(i)
        //i=n p(i) = 1
        //i<n p(i) = ((U(i+1)-L(i+1))+1) 之和
        if(DataTypeIdTemp == Array1){
            //*ArrayInformation->ArrayTemp[4] = 1;
            IntDataTable[IntDataTableTop++] = Array1;
            Sem_getAry_pi(&IntDataTable[IntDataTableTop-1]);
            //ArrayTempArea[ArrayTempBeginIndex+4] = 1;//i=n p(i) = 1
        }
        else if(DataTypeIdTemp == Array2){
            //*ArrayInformation->ArrayTemp[7] = 1;
            IntDataTable[IntDataTableTop++] = Array2;
            Sem_getAry_pi(&IntDataTable[IntDataTableTop-1]);
            //ArrayTempArea[ArrayTempBeginIndex+7] = 1;//i=n=2 p(2) = 1
            //Sem_load(&ArrayTempArea[ArrayTempBeginIndex+6]);//把U2加载到
            //Sem_getAry_pi(&ArrayTempArea[ArrayTempBeginIndex+4]);//计算p(1)值
        }
        SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, DECLFLAG, NULL, ArrayInformation, &IntDataTable[IntDataTableTop-1]);

        //向数据栈中加载NameIndex， FuncIndex, ArrayTempIndex, Value
        IntDataTable[IntDataTableTop++] = NameIndexTemp;
        Sem_load(&IntDataTable[IntDataTableTop-1]);//变量名
        IntDataTable[IntDataTableTop++] = 0;
        Sem_load(&IntDataTable[IntDataTableTop-1]);//函数声明Pcode下标：不是函数，对用下标位置为0
        if(DataTypeIdTemp != Array1&&DataTypeIdTemp != Array2){
            IntDataTable[IntDataTableTop++] = -1;// 不是数组置-1
        }
        else{
            //IntDataTable[IntDataTableTop++] = ArrayTempBeginIndex;// 是数组置模板初始位置
            IntDataTable[IntDataTableTop++] = 0;// 是数组置模板初始位置
            Sem_getAry_tempBegin(&IntDataTable[IntDataTableTop-1]);
        }
        Sem_load(&IntDataTable[IntDataTableTop-1]);// 对应数组的模板表初始位置ArrayTempIndex：
        IntDataTable[IntDataTableTop++] = 0;
        Sem_load(&IntDataTable[IntDataTableTop-1]);//未赋值时变量 为0
        //将当前变量插入数据栈中
        Sem_dataStackInsert();
        //Sem_load(StackSymbolTable[StackSymbolTable.size()-1].IntDataAddr);
        //变量声明有初始值，才直接更改arraytemp[1]初始地址位置
        //更改数组模板表中[1]数组在ArraySArea中初始地址位置
        /*if(DataTypeIdTemp == Array1||DataTypeIdTemp == Array2){
            //以IntDataTop作为数组首地址下标
            //*ArrayInformation->ArrayTemp[1] = ArraySAreaTop;
            ArrayTempArea[ArrayTempBeginIndex+1] = ArraySAreaTop;
        }*/

        if(SymbolList[CurSymPos] == ASSIGN){//ASSIGN
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;


            //int Attr_CInitValue = 0;初值不用作为属性，其初值最后应该在栈顶，用sto指令即可
            InitVal();

            //在0维情况下在赋值，数组直接在constexp中将对应值，放入以当前存储地址开始的intdata表中
            if(DataTypeIdTemp == Int){
                //声明赋值，参数是CALLFlag，执行该pcode 将
                IntDataTable[IntDataTableTop++] = DECLFLAG;
                Sem_sto(&IntDataTable[IntDataTableTop-1]);
            }
        }
        else{
            /*没有赋初值，需要将存储区先划分出来*/
            if(DataTypeIdTemp == Array1){
                //以IntDataTop作为数组首地址下标
                //在执行时，通过U（1）*U(2)获得数组大小
                //设置存储区开始地址
                //Sem_getAry_begin(ArrayInformation->ArrayTemp[1]);
                //先要获得
                //Sem_load(&ArrayTempArea[ArrayTempBeginIndex+3]);//u1
                //IntDataTable[IntDataTableTop++] = 1;
                //Sem_load(&IntDataTable[IntDataTableTop-1]);//1
                IntDataTable[IntDataTableTop++] = Array1;
                Sem_initVAry_sArea(&IntDataTable[IntDataTableTop-1]);
                //Sem_getAry_begin(&ArrayTempArea[ArrayTempBeginIndex+1]);
            }
            else if(DataTypeIdTemp == Array2){
                IntDataTable[IntDataTableTop++] = Array2;
                Sem_initVAry_sArea(&IntDataTable[IntDataTableTop-1]);
                //Sem_load(&ArrayTempArea[ArrayTempBeginIndex+3]);//u1
                //Sem_load(&ArrayTempArea[ArrayTempBeginIndex+6]);//1
                //Sem_getAry_begin(&ArrayTempArea[ArrayTempBeginIndex+1]);
            }
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
        /*每遇见一个初值，都放到intDatatab里，实现数组元素的存储*/

        Exp();
        if(StackSymbolTable[StackSymbolTable.size()-1].DataTypeId == Array1 ||
           StackSymbolTable[StackSymbolTable.size()-1].DataTypeId == Array2 ){
            Sem_loadAry_elm();//将初值加载到数组元素存储区中
        }

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
            int Attr_Index;
            Ident(Attr_Index);
            /*syml*/
            FuncInformationTab* FuncInformation = new FuncInformationTab;
            int NameIndexTemp = CurSymPos-1, IdentTypeIdTemp = 1, DataTypeIdTemp = 0, LineNumIndexTemp = CurSymPos-1;//行号就是标识符所处的行
            /*symr*/
            //插入符号表
            SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, DECLFLAG, FuncInformation, NULL, 0);
            //插入数据栈中
            IntDataTable[IntDataTableTop++] = NameIndexTemp;//函数名对应下标
            Sem_load(&IntDataTable[IntDataTableTop-1]);
            IntDataTable[IntDataTableTop++] = (int)PCodeList.size()+3;//函数所在Pcode位置
            Sem_load(&IntDataTable[IntDataTableTop-1]);
            IntDataTable[IntDataTableTop++] = -1;// 不是数组置-1
            Sem_load(&IntDataTable[IntDataTableTop-1]);// 对应数组的模板表初始位置：
            IntDataTable[IntDataTableTop++] = 0;//值
            Sem_load(&IntDataTable[IntDataTableTop-1]);
            Sem_dataStackInsert();//插入数据栈

            IsFunc = 1;
            /*定位*/
            SymTabLoc((int)StackSymbolTable.size());
            Sem_dataStackFuncLoc();

            if(SymbolList[CurSymPos] == LPARENT){//LPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                if(SymbolList[CurSymPos] != RPARENT){
                    /*syml*/
                    int FParmNum = 0;
                    /*symr*/
                    int CurIntDataTableIndex = IntDataTableTop;
                    FuncFParams(FParmNum, FuncInformation);//获取函数形参个数和各个形参的数据类型
                    //将运行栈中的实参加载到对应形参地址
                    for(int i=0; i<FParmNum; i++){
                        IntDataTable[IntDataTableTop++] = i;
                        if(FuncInformation->FParmList[FParmNum-i-1] == Array1||FuncInformation->FParmList[FParmNum-i-1] == Array2){
                            Sem_stoAry_param(&IntDataTable[IntDataTableTop-1]);
                        }
                        else{
                            Sem_stoInt_param(&IntDataTable[IntDataTableTop-1]);
                        }
                    }
                    /*syml*/
                    FuncInformation->FParmNum = FParmNum;
                    /*symr*/
                }
                else{
                    /*syml*/
                    FuncInformation->FParmNum = 0;
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

                Block(0);
                if(IsIntReturn == 0){
                    Error(EG);
                }
            }
        }

    }
	else if(SymbolList[CurSymPos] == VOIDTK){
		FuncType();
        if(SymbolList[CurSymPos] == IDENFR){//INDEFR
            int Attr_Index;
            Ident(Attr_Index);
            /*syml*/
            FuncInformationTab* FuncInformation = new FuncInformationTab;
            int NameIndexTemp = CurSymPos-1, IdentTypeIdTemp = 1, DataTypeIdTemp = 3, LineNumIndexTemp = CurSymPos-1;//行号就是标识符所处的行号
            /*symr*/
            /*插入符号表*/
            SymTabInsert(NameIndexTemp, IdentTypeIdTemp, DataTypeIdTemp, LineNumIndexTemp, DECLFLAG, FuncInformation, NULL, 0);
            //插入数据栈中
            IntDataTable[IntDataTableTop++] = NameIndexTemp;//函数名对应下标
            Sem_load(&IntDataTable[IntDataTableTop-1]);
            IntDataTable[IntDataTableTop++] = (int)PCodeList.size()+3;//函数所在Pcode位置
            Sem_load(&IntDataTable[IntDataTableTop-1]);
            IntDataTable[IntDataTableTop++] = -1;// 不是数组置-1
            Sem_load(&IntDataTable[IntDataTableTop-1]);// 对应数组的模板表初始位置：
            IntDataTable[IntDataTableTop++] = 0;//函数值
            Sem_load(&IntDataTable[IntDataTableTop-1]);
            Sem_dataStackInsert();//插入数据栈
            IsFunc = 1;
            /*定位*/
            SymTabLoc((int)StackSymbolTable.size());
            Sem_dataStackFuncLoc();

            if(SymbolList[CurSymPos] == LPARENT){//LPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                if(SymbolList[CurSymPos] != RPARENT){
                    /*syml*/
                    int FParmNum = 0;
                    /*symr*/
                    FuncFParams(FParmNum, FuncInformation);
                    /*syml*/
                    FuncInformation->FParmNum = FParmNum;
                    /*symr*/
                    for(int i=0; i<FParmNum; i++){
                        IntDataTable[IntDataTableTop++] = i;
                        if(FuncInformation->FParmList[FParmNum-i-1] == Array1||FuncInformation->FParmList[FParmNum-i-1] == Array2){
                            Sem_stoAry_param(&IntDataTable[IntDataTableTop-1]);
                        }
                        else{
                            Sem_stoInt_param(&IntDataTable[IntDataTableTop-1]);
                        }
                    }
                }
                else{
                    /*syml*/
                    FuncInformation->FParmNum = 0;
                    /*symr*/
                }

                if(SymbolList[CurSymPos] == RPARENT){//RPARENT
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;

                }
                else{
                    Error(EJ);
                }

                IsVoidReturn = 1;//判断错误处理

                Block(1);//是void函数的block
                Sem_return();//生成返回指令，返回到调用点之后,应该在block里面
                if(IsVoidReturn == 0){
                    Error(EF);
                }

            }
        }
	}
    IsFunc = -1;
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
void FuncFParams(int& FParmNum, FuncInformationTab* FuncInformation){
    int FParamDataType = 0;
    int FparmInDataIndex = 0;

    FuncFParam(FParamDataType, FparmInDataIndex);

    FuncInformation->FParmList[FParmNum] = FParamDataType;
    FuncInformation->FParmInDataIndex[FParmNum] = &IntDataTable[FparmInDataIndex];
    FParmNum++;
    /*保持0维*/
    FParamDataType = 0;
    while(SymbolList[CurSymPos] == COMMA){//COMMA
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        FuncFParam(FParamDataType, FparmInDataIndex);

        FuncInformation->FParmList[FParmNum] = FParamDataType;
        FuncInformation->FParmInDataIndex[FParmNum] = &IntDataTable[FparmInDataIndex];
        FParmNum++;
        FParamDataType = 0;
    }
    if(ErrorPrintFlag)
        printf("<FuncFParams>\n");
}

/*函数形参*/
//FuncFParam → BType Ident ['[' ']' { '[' ConstExp ']' }]
void FuncFParam(int& FParamDataType, int& FparmInDataIndex){
    if(SymbolList[CurSymPos] == INTTK){//INTTK
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == IDENFR){
            int Attr_Index;
            Ident(Attr_Index);

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
                        RubbishConst = 0;
                        Sem_gettop(&RubbishConst);//移除constexp在运行栈
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
            //IntDataTable[IntDataTableTop++] = 0;
            //FparmInDataIndex = IntDataTableTop-1;
            //Sem_InsertDataStack(FParamNameIndex, FParamIdentType, FParamDataType, FParamLineNumIndex, DECLFLAG, NULL, NULL, &IntDataTable[IntDataTableTop-1]);
            SymTabInsert(FParamNameIndex, FParamIdentType, FParamDataType, FParamLineNumIndex, DECLFLAG, NULL, NULL, &IntDataTable[IntDataTableTop-1]);
            IntDataTable[IntDataTableTop++] = FParamNameIndex;
            Sem_load(&IntDataTable[IntDataTableTop-1]);
            IntDataTable[IntDataTableTop++] = 0;//函数声明在Pcode中的下标
            Sem_load(&IntDataTable[IntDataTableTop-1]);
            IntDataTable[IntDataTableTop++] = -1;// 初始化数组模板表位置 置-1
            Sem_load(&IntDataTable[IntDataTableTop-1]);// 对应数组的模板表初始位置：
            IntDataTable[IntDataTableTop++] = 0;//初值是0
            Sem_load(&IntDataTable[IntDataTableTop-1]);
            Sem_dataStackInsert();
            //然后将运行栈中加载好的实参，填入数据栈中

        }
    }
    if(ErrorPrintFlag)
        printf("<FuncFParam>\n");
}

/*语句块*/
//Block → '{' { ConstDecl | VarDecl | Stmt } '}'
//BlockItem →
void Block(int IsVoidFunc){
    if(SymbolList[CurSymPos] == LBRACE){//LBRACE
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        while(SymbolList[CurSymPos] == CONSTTK||SymbolList[CurSymPos] == INTTK     ||SymbolList[CurSymPos] == IDENFR  ||
			  SymbolList[CurSymPos] == BREAKTK||SymbolList[CurSymPos] == CONTINUETK||SymbolList[CurSymPos] == IFTK    ||
			  SymbolList[CurSymPos] == ELSETK ||SymbolList[CurSymPos] == PRINTFTK  ||SymbolList[CurSymPos] == RETURNTK||
			  SymbolList[CurSymPos] == LBRACE ||SymbolList[CurSymPos] == LPARENT   ||SymbolList[CurSymPos] == INTCON  ||
			  SymbolList[CurSymPos] == WHILETK||SymbolList[CurSymPos] == SEMICN    ||SymbolList[CurSymPos] == MINU    ||
			  SymbolList[CurSymPos] == NOT    ||SymbolList[CurSymPos] == PLUS){

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
        if(IsVoidFunc == 1){
            Sem_dataStackFuncReLoc();
            Sem_return();
        }
        if(SymbolList[CurSymPos] == RBRACE){//RBRACE
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
        }

    }
    SymTabReLoc();
    Sem_dataStackReLoc();
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

        /*还是在IntData中生成一个标号*/
        IntDataTable[IntDataTableTop++] = -1;
        ILable_inIntTabIndexA = IntDataTableTop-1;
        ILabStack.push_back(ILable_inIntTabIndexA);
        if(SymbolList[CurSymPos] == LPARENT){//LPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            Cond();
            /**/
            /*有条件跳转*/
            Sem_jpc(&IntDataTable[ILabStack[ILabStack.size()-1]]);//A

            if(SymbolList[CurSymPos] == RPARENT){//RPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                /*定位{
                if(SymbolList[CurSymPos] == LBRACE){
                    SymTabLoc((int)StackSymbolTable.size());
                }*/
                Stmt();

                if(SymbolList[CurSymPos] == ELSETK){//ELSETK
                    /*还是在IntData中生成一个标号*/
                    IntDataTable[IntDataTableTop++] = -1;
                    ILable_inIntTabIndexB = IntDataTableTop-1;
                    ILabStack.push_back(ILable_inIntTabIndexB);

                    Sem_jmp(&IntDataTable[ILabStack[ILabStack.size()-1]]);//b

                    Sem_gpi(&IntDataTable[ILabStack[ILabStack.size()-2]]);//-2

                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                    /*if(SymbolList[CurSymPos] == LBRACE){
                        SymTabLoc((int)StackSymbolTable.size());
                        Sem_dataStackLoc();
                    }*/

                    Stmt();
                    Sem_gpi(&IntDataTable[ILabStack[ILabStack.size()-1]]);//-1
                    ILabStack.pop_back();
                    ILabStack.pop_back();
                }
                else{
                    Sem_gpi(&IntDataTable[ILabStack[ILabStack.size()-1]]);
                    ILabStack.pop_back();
                }
            }
            else{
                Error(EJ);
                //缺少右括号后，正常进入else
                /*if(SymbolList[CurSymPos] == LBRACE){
                    SymTabLoc((int)StackSymbolTable.size());
                    Sem_dataStackLoc();
                }*/
                Stmt();

                if(SymbolList[CurSymPos] == ELSETK){//ELSETK
                    Sym_map(SymbolList[CurSymPos]);
                    CurSymPos = CurSymPos+1;
                    /*if(SymbolList[CurSymPos] == LBRACE){
                        SymTabLoc((int)StackSymbolTable.size());
                        Sem_dataStackLoc();
                    }*/
                    Stmt();

                }
            }
        }
        IsIntReturn = 0;
    }
    else if(SymbolList[CurSymPos] == WHILETK){//WHILETK
        /*错误处理：while语句判断*/
        IsWhile.push_back(1);
        /*设置标号，labA*/
        IntDataTable[IntDataTableTop++] = PCodeList.size()-1;
        WLable_inIntTabIndexA = IntDataTableTop-1;
        WLabStack.push_back(WLable_inIntTabIndexA);
        IntDataTable[IntDataTableTop++] = PCodeList.size()-1;
        WLable_inIntTabIndexB = IntDataTableTop-1;
        WLabStack.push_back(WLable_inIntTabIndexB);

        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        if(SymbolList[CurSymPos] == LPARENT){//LPARENT
            Sym_map(SymbolList[CurSymPos]);
            CurSymPos = CurSymPos+1;
            Cond();
            /*有条件跳转*/
            Sem_jpc(&IntDataTable[WLabStack[WLabStack.size()-1]]);//labb
            if(SymbolList[CurSymPos] == RPARENT){//RPARENT
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                /*if(SymbolList[CurSymPos] == LBRACE){
                    SymTabLoc((int)StackSymbolTable.size());
                }*/
                Stmt();
                Sem_jmp(&IntDataTable[WLabStack[WLabStack.size()-2]]);//laba
                Sem_gpi(&IntDataTable[WLabStack[WLabStack.size()-1]]);//labb
                WLabStack.pop_back();
                WLabStack.pop_back();
            }
            else{
                Error(EJ);
                if(SymbolList[CurSymPos] == LBRACE){
                    SymTabLoc((int)StackSymbolTable.size());
                    Sem_dataStackLoc();
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
        Sem_jmp(&IntDataTable[WLabStack[WLabStack.size()-1]]);

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
        Sem_jmp(&IntDataTable[WLabStack[WLabStack.size()-2]]);
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
        Sem_dataStackFuncReLoc();
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

        //IntDataTable[IntDataTableTop++] =

        Sem_return();
        Sem_stop();
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
            IntDataTable[IntDataTableTop++] = CurSymPos;
            //StringStack.(TokenList[CurSymPos]);
            int FormatString_inTokenListIndex = IntDataTableTop-1;
            FormatString(FormatCNum);
            while(SymbolList[CurSymPos]== COMMA){//COMMA
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                Exp();
                Sem_replace(&IntDataTable[FormatString_inTokenListIndex]);
                //printf("%d ", &IntDataTable[FormatString_inTokenListIndex]);
                ExpNum = ExpNum + 1;
            }
            Sem_output(&IntDataTable[FormatString_inTokenListIndex]);
            //printf("%d \n", &IntDataTable[FormatString_inTokenListIndex]);
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
			int Attr_StackSymIndex = -1;
			int Attr_IsAssignLeft = 1;
		    LVal(IdentTypeIdTemp, Attr_StackSymIndex, Attr_IsAssignLeft);
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
        	                Sem_input();
        	                if(SymbolList[CurSymPos] == SEMICN){//SEMICN
        	                    Sym_map(SymbolList[CurSymPos]);
         	                   	CurSymPos = CurSymPos+1;

                                if(StackSymbolTable[Attr_StackSymIndex].DataTypeId == Int){
                                    IntDataTable[IntDataTableTop++] = CALLFLAG;
                                    Sem_sto(&IntDataTable[IntDataTableTop-1]);
                                }
         	                   	else if(StackSymbolTable[Attr_StackSymIndex].DataTypeId == Array1||
                                        StackSymbolTable[Attr_StackSymIndex].DataTypeId == Array2){
         	                   	    Sem_stoAry();
         	                   	}
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
                    if(StackSymbolTable[Attr_StackSymIndex].DataTypeId == Int){
                        IntDataTable[IntDataTableTop++] = CALLFLAG;
                        Sem_sto(&IntDataTable[IntDataTableTop-1]);
                    }
                    else if(StackSymbolTable[Attr_StackSymIndex].DataTypeId == Array1||
                            StackSymbolTable[Attr_StackSymIndex].DataTypeId == Array2){
                        Sem_stoAry();
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
		
        }
        else{
			Exp();
            if(SymbolList[CurSymPos] == SEMICN){//SEMICN
                Sym_map(SymbolList[CurSymPos]);
                CurSymPos = CurSymPos+1;
                IntDataTable[IntDataTableTop++] = 0;
                Sem_gettop(&IntDataTable[IntDataTableTop-1]);//去除runstack的stmt exp（）；保留在栈顶上的值
            }
            else{
                /*不需要加判断*/
                Error(EI);
            }

        }
        
    }
	else if(SymbolList[CurSymPos] == LBRACE){
	    SymTabLoc((int)StackSymbolTable.size());
	    Sem_dataStackLoc();
	    Block(0);

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
                FormatCNum = FormatCNum + 1;//对应 %d 个数
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
    IntDataTable[IntDataTableTop++] = -1;
    OrLable_inIntTabIndexA = IntDataTableTop-1;
    OrLabStack.push_back(OrLable_inIntTabIndexA);
    while(SymbolList[CurSymPos] == OR){//OR

        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        Sem_loadRepeat();
        Sem_not();
        Sem_jpc(&IntDataTable[OrLabStack[OrLabStack.size()-1]]);
        LAndExp();

        Sem_orr();
        if(SymbolList[CurSymPos] == OR){
            if(ErrorPrintFlag)
    		printf("<LOrExp>\n");
		}
		
    }
    Sem_gpi(&IntDataTable[OrLabStack[OrLabStack.size()-1]]);
    OrLabStack.pop_back();
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
    IntDataTable[IntDataTableTop++] = -1;
    AndLable_inIntTabIndexA = IntDataTableTop-1;
    AndLabStack.push_back(AndLable_inIntTabIndexA);
    while(SymbolList[CurSymPos] == AND){//AND
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        Sem_loadRepeat();
        Sem_jpc(&IntDataTable[AndLabStack[AndLabStack.size()-1]]);
        EqExp();

        Sem_and();
        if(SymbolList[CurSymPos] == AND){
            if(ErrorPrintFlag)
        	printf("<LAndExp>\n");
		}
		
    }
    Sem_gpi(&IntDataTable[AndLabStack[AndLabStack.size()-1]]);
    AndLabStack.pop_back();
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
        int Eql_Not = SymbolList[CurSymPos];
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        RelExp();
        //语义分析子程序
        if(Eql_Not == EQL){
            Sem_eql();
        }
        else{
            Sem_neq();
        }
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
        int RelOp = SymbolList[CurSymPos];
        Sym_map(SymbolList[CurSymPos]);
        CurSymPos = CurSymPos+1;
        AddExp();
        if(RelOp == GRE){
            Sem_gre();
        }
        else if(RelOp == LSS){
            Sem_lss();
        }
        else if(RelOp == GEQ){
            Sem_geq();
        }
        else if(RelOp == LEQ){
            Sem_leq();
        }

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
    IntDataTable[IntDataTableTop++] = 0;
    int Maintail = IntDataTableTop-1;
    Sem_str(&IntDataTable[Maintail]);
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
        		Sem_dataStackFuncLoc();
        		/**/
        		IsIntReturn = 0;
        		Block(0);
        		if(IsIntReturn == 0){
        		    Error(EG);
        		}
			}
        	else{
        	    Error(EJ);
                /*缺少右小括号*/
                SymTabLoc((int)StackSymbolTable.size());
                Sem_dataStackLoc();
                Block(0);
        	}
		}
	}
	Sem_gpi(&IntDataTable[Maintail]);
    if(ErrorPrintFlag)
	    cout << "<MainFuncDef>" << endl;
}
