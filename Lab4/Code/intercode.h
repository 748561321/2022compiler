#ifndef __INNERCODE_H__
#define __INNERCODE_H__
#include "semantic.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Operand_* Operand;
typedef struct Operand_ {//操作数
	enum {VARIABLE_OP, TEMPVAR_OP, CONSTANT_OP, ADDR_OP//*
	,
	QU_ADDR_OP // &
	, LABEL_OP, FUNCTION_OP } kind;
	union {
		int var_no;		//临时变量t
		int label_no;		    //标号l
		char value[32];		   //值 		
	}u;

	// 为了便于实验四 这里将输出整合
	char name[32];//整合
	int constant;//仅CONSTANT 

	Type type;
}Operand_;

typedef struct InterCode_* InterCode;
typedef struct InterCode_ {
    //表1
	enum {
			LABEL_IR, FUNCTION_IR, ASSIGN_IR, PLUS_IR, MINUS_IR, STAR_IR, DIV_IR, 
			QU_IR,EQ_ST_IR,ST_EQ_IR,
            // ADDR_IR2,    // x := &y
			// ADDR_IR3,	// x := &y + z
            // ADDR_VALUE_IR, // x := *y 
			// MEMORY_IR, //*x := y 
            GOTO_IR, IF_GOTO_IR, RETURN_IR, DEC_IR, ARG_IR, CALL_IR, PARAM_IR, READ_IR, WRITE_IR,DEBUG_IR
	}kind;
    Operand operands[3];
    int size;
    char relop[32];
}InterCode_;

void initIRList();
void insertCode(InterCode ir);
void printCode(char *filename);
void printdebug(char *filename);
void repr(Operand op,FILE *file);
void deletelastCode();
void insertdebug(char * info);

FieldList allsearch(char *name
,int flag// flag=1:function flag =2: str_spe flag=0:变量 原因在于函数名和变量名可以一样 只有2有用 表明结构体类型不能重名
);

int getSpace(Type type) ;
Operand new_temp();
Operand new_label();
Operand new_constant(int i);


//树
void tProgram(Node *root);
void tExtDefList(Node *node);
void tExtDef(Node *node);
Type tSpecifier(Node *node);
void tExtDecList(Node *node);
Type tFunDec(Node *node);
void tCompSt(Node *node,Type spec);
FieldList tVarDec(Node *node,Type spec);
Type tStructSpecifier(Node *node);
// void tOptTag(Node *node,Type spec);
void tDefList(Node *node);
// // Type VarList(Node *node);
// // void ParamDec(Node *node);
// // void StmtList(Node *node);
void tStmt(Node *node,Type spec);

void tExp(Node * node, Operand  place);

void tDef(Node *node);
void tDecList(Node *node,Type spec);
void tDec(Node *node,Type spec);
void tArgs(Node *node,Operand * arglist);
void tCond(Node* node,Operand label_true,Operand label_false);


void writeCode(char *filename) ;
#endif