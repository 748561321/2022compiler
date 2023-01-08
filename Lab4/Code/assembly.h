#ifndef _ASSEMBLY_H_
#define _ASSEMBLY_H_

#include "intercode.h"

typedef struct _register Register;
typedef struct varible Varible;
typedef struct registers Registers;
typedef struct varList VarList;
typedef struct varTable VarTable;
typedef enum reg {ZERO,AT,V0,V1,A0,A1,A2,A3,T0,T1,T2,T3,T4,T5,T6,T7,S0,S1,S2,S3,S4,S5,S6,S7,T8,T9,K0,K1,GP,SP,FP,RA,} reg;

struct _register{
    char* name;
    unsigned isEmpty;
};// 寄存器： 是否为空，存储内容

struct varible {
    int reg;
    Operand op;
    Varible* next;
};//变量： 存储的寄存器-操作数本身 链条


struct varList {
    Varible* head;
    Varible* tail;
};//变量列表


extern VarList* varListReg;//寄存器变量表
extern VarList* varListMem;//内存的变量表
extern int offset;
extern Register* regList[32];
extern int last;

void clearVarList(VarList* varList);

//在某个列表中添加变量: 寄存器-操作数 
void addVarible(VarList* varList, int reg, Operand op);
//在某个列表中删去变量
void delVarible(VarList* varList, Varible* var);
//给一个操作数分配寄存器，返回寄存器编号
int saveToReg(FILE* fp, Operand op);
//分配寄存器算法
int assignReg(Operand op);
//存到栈里-将寄存器内op的值写回内存里对应的变量
void saveToStack(FILE* fp, int reg, Operand op);

void printAssemblyCode(FILE* fp);
void transToAssem(FILE* fp, int index);


#endif