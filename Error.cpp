//
// Created by 86156 on 2021-10-19.
//
#include <stdio.h>
#include "Error.h"
#include "lexical_analysis.h"
void Error(int ErrorType){
    switch (ErrorType){
        case 0:     //a 非法符号
            printf("%d a\n", SymbolListLine[CurSymPos]);
            CurSymPos = CurSymPos + 1;
            break;
        case 1:     //b 名字重定义
            printf("%d b\n", SymbolListLine[CurSymPos-1]);
            break;
        case 2:     //c 未定义的名字
            printf("%d c\n", SymbolListLine[CurSymPos-1]);
            break;
        case 3:     //d 函数参数不匹配
            printf("%d d\n", SymbolListLine[CurSymPos]);
            break;
        case 4:     //e 函数参数类型不匹配
            printf("%d e\n", SymbolListLine[CurSymPos]);
            break;
        case 5:     //f 无返回值的函数存在不匹配的return语句
            printf("%d f\n", SymbolListLine[CurSymPos-2]);
            break;
        case 6:     //g 有返回值的函数缺少return语句
            printf("%d g\n", SymbolListLine[CurSymPos-1]);
            break;
        case 7:     //h 不能改变常量得知
            printf("%d h\n", SymbolListLine[CurSymPos-1]);
            break;
        case 8:     //i 缺少分号
            printf("%d i\n", SymbolListLine[CurSymPos-1]);
            break;
        case 9:     //j 缺少右小括号
            printf("%d j\n", SymbolListLine[CurSymPos-1]);
            break;
        case 10:    //k 缺少右中括号
            printf("%d k\n", SymbolListLine[CurSymPos-1]);
            break;
        case 11:    //l pritnf中格式字符与表达式个数不匹配
            printf("%d l\n", SymbolListLine[CurSymPos-1]);
            break;
        case 12:    //m 报错行号为`break`与`continue`所在行号
            printf("%d m\n", SymbolListLine[CurSymPos]);
            break;
        default:
            break;
    }
}