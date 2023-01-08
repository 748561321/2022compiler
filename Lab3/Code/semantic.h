#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define HASH_SIZE 0x3fff

#define INT_TYPE 1
#define FLOAT_TYPE 2
#define DECLA 1
#define DEFIN 2

typedef struct Type_ *Type;
typedef struct FieldList_ *FieldList;

typedef struct Type_ {
	enum {BASIC, ARRAY, STRUCTURE, FUNCTION, STR_SPE} kind;//结构类型和结构定义不是一个东西
    union{
		//基本类型
		int basic;
		//数组类型信息包括元素类型与数组大小构成
		struct {
			Type elem;
            int size;
		}array;
		// 结构体类型信息是一个链表
		FieldList structure;
		//函数
		struct{
			FieldList params;//参数
			Type funcType;//返回值类型
			int paramNum;//参数数量
			int state;//状态 
			int lineno;//行数 
		}function;
	}u;
}Type_;

//作用域
typedef struct scope{
	int id;
	int parent_id;//自己外面一层的作用域
	int wno;//自己和自己所有外层作用域的数量
	int w[50];//自己和自己所有外层作用域的id
}scope;


//FieldList = 变量
typedef struct FieldList_ {
	char *name;//域的名字
	Type type;//域的类型
	FieldList tail;//下一个域
	int scope_id;//作用域
	char ifparam[4]; //是不是param 是就是acac
}FieldList_;

void enter_scope();
void exit_scope();

//符号表
unsigned int hash_pjw(char *name);
void initHashtable();
int insert(FieldList f);
//search会找外层的 用于判断是否未定义以使用 所以肯定是从当前层找
FieldList search(char *name,int flag);
//ifexist会找同层的 用于判断是否重复定义
FieldList ifexist(char *name,int id);
int TypeEqual(Type type1,Type type2);
void printSymbol();

//树
void Program(Node *root);
void ExtDefList(Node *node);
void ExtDef(Node *node);
Type Specifier(Node *node);
void ExtDecList(Node *node,Type spec);
void FunDec(Node *node,Type spec,int state);
void CompSt(Node *node,Type ftype);
FieldList VarDec(Node *node,Type spec);
Type StructSpecifier(Node *node);
void OptTag(Node *node,Type spec);
void DefList(Node *node);
// Type VarList(Node *node);
// void ParamDec(Node *node);
// void StmtList(Node *node);
void Stmt(Node *node,Type ftype);
Type Exp(Node *root);
void Def(Node *node);
void DecList(Node *node,Type spec);
void Dec(Node *node,Type spec);
// void Args(Node *node);

void check_declar();
#endif
