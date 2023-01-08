#include "intercode.h"
#include "semantic.h"
#define SIZE 10
int lnum = 1;	//标号
int tnum = 1;	//t 临时变量
int vnum = 1;	//v 变量

InterCode *IRList; // IR表 动态数组
int IRsize;
int IRMAXSIZE;
void repr(Operand op, FILE *fp);

extern FieldList hashTable[HASH_SIZE];
extern int scope_id;
extern int current_id;
extern scope sc_table[50];


//Program     : ExtDefList
void tProgram(Node *root){
    if(root==NULL)
        return;
    if(!strcmp("ExtDefList" , root->child[0]->name))
    {
        tExtDefList(root ->child[0]);
    }
}


// ExtDefList  : ExtDef ExtDefList  
//             |  /* empty */       
//             ;
void tExtDefList(Node *node)
{
    if(node == NULL )return;
    if(node->childno ==2)
    {
        tExtDef(node->child[0]);
        tExtDefList(node->child[1]);  
    }
}

// ExtDef      : Specifier ExtDecList SEMI  
//             | Specifier SEMI             这条产生式也会允许出现像“int;”这样没有意义的语句
//             | Specifier FunDec CompSt   
//             | Specifier FunDec SEMI  
void tExtDef(Node *node)
{
    //Specifier ExtDecList SEMI  
	tSpecifier(node->child[0]);
    if(strcmp(node->child[1]->name,"ExtDecList") == 0)//全局变量
    {
        tExtDecList(node->child[1]);
    }
    //Specifier SEMI   不用管
    else if(strcmp(node->child[1]->name,"FunDec") == 0) 
    //Specifier FunDec CompSt 
    //Specifier FunDec SEMI  
    //FunDec是函数头，CompSt表示函数体
    {
        enter_scope();
        if(strcmp(node->child[2]->name,"CompSt")==0)//定义
        {
            //printf("22");
            Type spec = tFunDec(node->child[1]);
            tCompSt(node->child[2],spec);
        }
        else
        {
            //printf("11");
        tFunDec(node->child[1]);
        }
        exit_scope();
    }
}       

// Specifier   : TYPE            
//             | StructSpecifier 
//             ;
Type tSpecifier(Node *node)
{
    // TYPE
    if(strcmp(node->child[0]->name,"TYPE")==0)
    {
		Type spec = (Type)malloc(sizeof(Type_));
        spec->kind = BASIC;
        if(strcmp(node->child[0]->yytext,"float")==0)
            spec->u.basic=FLOAT_TYPE;
        else // INT INT8 INT16
            spec->u.basic=INT_TYPE;
        return spec;
    }
    else
    {
		Type t = tStructSpecifier(node->child[0]);
		if(t == NULL) return NULL;
        Type t2 = (Type)malloc(sizeof(Type_));
        t2->kind =STRUCTURE;
        t2->u.structure = t->u.structure;
        return t2;
    }
}

// StructSpecifier : STRUCT OptTag LC DefList RC		定义结构体类型
//                 | STRUCT Tag                 		定义过某个结构体 用来定义变量
//                 ;
Type tStructSpecifier(Node *node)
{
    Type spec = (Type)malloc(sizeof(Type_));
    spec->kind = STRUCTURE;
    //printf("debug : %s\n",node->child[1]->name);
    //这里注意 如果opttag为空就会是NULL 所以会出错
	//printf("debug\n");
	//printf("%s\n",node->child[1]->name);
    if(node->child[1] !=NULL && strcmp(node -> child[1]->name ,"Tag") == 0 )
    {//StructSpecifier → STRUCT Tag：如果之前已经定义过某个结构体，比如struct Complex {…}，那么之后可以直接使用该结构体来定义变量 tag->id
        //printf("debug\n");
		Node * Tag = node->child[1];
        Node * ID = Tag->child[0];
        char *str = ID->yytext;
        //找结构体类型
		// printf("%s\n",str);
		// printSymbol();
        FieldList field = search(str,2);
		// InterCode dec = (InterCode)malloc(sizeof(InterCode_));
		// dec->kind = DEC_IR;
		// Operand v = (Operand)malloc(sizeof(Operand_));
		// v->kind = VARIABLE_OP; 
		// strcpy(v->u.value, str);
		// dec->operands[0] = v;
		// dec->size = getSpace(field->type);
		// insertCode(dec);
		// //struct Operands op;
		// //DEC v3 8
		return field->type;
    }


    //STRUCT (OptTag) LC DefList RC 定义结构体类型
    //OptTag为NULL应该也占一个位置 这里以防万一debug
    if(node->childno !=5) printf("debug struct opttag");
    //这里作用域在struct内
    enter_scope();
    //这里定义了结构体类型 
    exit_scope();
	return NULL;

}



// FunDec      : ID LP VarList RP             
//             | ID LP RP                             
//             ;
Type tFunDec(Node *node)
{
	char * funname = node->child[0]->yytext;
	FieldList fun = search(funname,1);

	{//lab3 这里有函数头
	Operand op = (Operand)malloc(sizeof(Operand_));
	//memset(op,0,sizeof(Operand));
	op->kind = FUNCTION_OP;
	strcpy(op->u.value,node->child[0]->yytext);
	InterCode IR = (InterCode)malloc(sizeof(InterCode_));
	//memset(IR,0,sizeof(InterCode_));
	IR->kind = FUNCTION_IR;
	IR->operands[0] = op;
	insertCode(IR);
	}

	FieldList p = fun->type->u.function.params;
	for(int i=0; i<fun->type->u.function.paramNum;i++)
	{
		//lab3 参数 param ope
		Operand pop = NULL;

		if (p->type->kind == BASIC || p->type->kind == ARRAY || p->type->kind == STRUCTURE) 
		{
			pop = (Operand)malloc(sizeof(struct Operand_));
			memset(pop, 0, sizeof(Operand_));
			pop->kind = VARIABLE_OP;
			strcpy(pop->u.value, p->name);
			InterCode paramIR = (InterCode)malloc(sizeof(InterCode_));
			memset(paramIR, 0, sizeof(InterCode_));
			paramIR->kind = PARAM_IR;
			paramIR->operands[0] = pop;
			insertCode(paramIR);
		}
		else
		{
			printf("debug\n");
		}
	p = p->tail;
	}

	FieldList p2 = fun->type->u.function.params;
	if(strcmp(node->child[2]->name,"VarList")==0)//补上正常流程
	{
		Node * varList = node->child[2];
		while(1)
		{
			Node * paramDec =varList->child[0];
			//这里是从函数的参数定义的
			//进入到specifier只是会到dec struct的地方 而这里不需要
			//tSpecifier(paramDec->child[0]); // 不需要DEC struct
			tVarDec(paramDec->child[1],p2->type);
			if(varList->childno == 3)
			{
				varList=varList->child[2];
			}
			else
			{
				break;
			}
		}
		p2=p2->tail;
	}

	Type rtype = fun->type->u.function.funcType;
	return rtype;
}


// CompSt      : LC DefList StmtList RC                   
//             ;
void tCompSt(Node *node,Type spec)
{
    enter_scope();
    tDefList(node->child[1]);
    ////
    Node * stmtlist =node->child[2];
    // StmtList    : Stmt StmtList               
    //         | /* empty */                   
    //         ;
    while(stmtlist!=NULL)
    {
        tStmt(stmtlist->child[0],spec);//这里原先传的type是函数返回值
        stmtlist = stmtlist->child[1];
    }
    exit_scope();
}

void tStmt(Node *node,Type spec)
{
	if (strcmp(node->child[0]->name, "CompSt") == 0)
    {//return translate_CompSt(CompSt, sym_table)
        tCompSt(node->child[0],spec);
    }
    else if (strcmp(node->child[0]->name, "Exp") == 0)
    {//Exp SEMI 
	//return translate_Exp(Exp, sym_table, NULL)
        tExp(node->child[0],NULL);
    }
    else if (strcmp(node->child[0]->name, "RETURN") == 0)
    {
// t1 = new_temp()
// code1 = translate_Exp(Exp, sym_table, t1)
// code2 = [RETURN t1]
// return code1 + code2

		Operand t1 = new_temp();
		//如果是int这里可以优化
        tExp(node->child[1],t1);

		InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
		code2->kind = RETURN_IR;
		code2->operands[0] = t1;
		insertCode(code2);
    }
    else if (strcmp(node->child[0]->name, "WHILE") == 0)
    {//WHILE LP Exp RP Stmt 
// label1 = new_label()
// label2 = new_label()
// label3 = new_label()
// code1 = translate_Cond(Exp, label2, label3, sym_table)
// code2 = translate_Stmt(Stmt1, sym_table)
// return [LABEL label1] + code1 + [LABEL label2] + code2
// + [GOTO label1] + [LABEL label3]
		Operand label1 = new_label();
		Operand label2 = new_label();
		Operand label3 = new_label();

		InterCode l1 = (InterCode)malloc(sizeof(InterCode_)); 
		l1->kind = LABEL_IR;
		l1->operands[0] = label1;
		insertCode(l1);

		tCond(node->child[2],label2,label3);
        
		InterCode l2 = (InterCode)malloc(sizeof(InterCode_)); 
		l2->kind = LABEL_IR;
		l2->operands[0] = label2;
		insertCode(l2);

		tStmt(node->child[4],spec);

		InterCode goto1 = (InterCode)malloc(sizeof(InterCode_));
		goto1->kind = GOTO_IR;
		goto1->operands[0] = label1;
		insertCode(goto1);

		InterCode l3 = (InterCode)malloc(sizeof(InterCode_)); 
		l3->kind = LABEL_IR;
		l3->operands[0] = label3;
		insertCode(l3);
    }
	else if(node->childno <7)
	{//IF LP Exp RP Stmt

// label1 = new_label()
// label2 = new_label()
// code1 = translate_Cond(Exp, label1, label2, sym_table)
// code2 = translate_Stmt(Stmt1, sym_table)
// return code1 + [LABEL label1] + code2 + [LABEL label2]
		Operand label1 = new_label();
		Operand label2 = new_label();
		tCond(node->child[2],label1,label2);
		InterCode l1 = (InterCode)malloc(sizeof(InterCode_)); 
		l1->kind = LABEL_IR;
		l1->operands[0] = label1;
		insertCode(l1);
        tStmt(node->child[4],spec);
		InterCode l2 = (InterCode)malloc(sizeof(InterCode_)); 
		l2->kind = LABEL_IR;
		l2->operands[0] = label2;
		insertCode(l2);

	}
    else if(node->childno == 7)
	{//IF LP Exp RP Stmt ELSE Stmt 
// label1 = new_label()
// label2 = new_label()
// label3 = new_label()
// code1 = translate_Cond(Exp, label1, label2, sym_table)
// code2 = translate_Stmt(Stmt1, sym_table)
// code3 = translate_Stmt(Stmt2, sym_table)
// return code1 + [LABEL label1] + code2 + [GOTO label3]
// + [LABEL label2] + code3 + [LABEL label3]
		Operand label1 = new_label();
		Operand label2 = new_label();
		Operand label3 = new_label();
		tCond(node->child[2],label1,label2);///code1
		//label1
		InterCode l1 = (InterCode)malloc(sizeof(InterCode_)); 
		l1->kind = LABEL_IR;
		l1->operands[0] = label1;
		insertCode(l1);

		tStmt(node->child[4],spec);//code2

        //goto label3
		InterCode goto3 = (InterCode)malloc(sizeof(InterCode_));
		goto3->kind = GOTO_IR;
		goto3->operands[0] = label3;
		insertCode(goto3);

		//label2
		InterCode l2 = (InterCode)malloc(sizeof(InterCode_)); 
		l2->kind = LABEL_IR;
		l2->operands[0] = label2;
		insertCode(l2);

		tStmt(node->child[6],spec);//code3

		//label3
		InterCode l3 = (InterCode)malloc(sizeof(InterCode_)); 
		l3->kind = LABEL_IR;
		l3->operands[0] = label3;
		insertCode(l3);

        
	}

}

// DefList : Def DefList             
//         | /* empty */              
//         ;
// 每个Def就是一条变量定义
void tDefList(Node *node)
{
    if(node !=NULL)
    {
        tDef(node->child[0]);
        tDefList(node->child[1]);
    }
}

// Def     : Specifier DecList SEMI
//         ;
void tDef(Node *node)
{
	Type spec = tSpecifier(node->child[0]);
    tDecList(node->child[1],spec);
}



// DecList : Dec                 
//         | Dec COMMA DecList        
//         ;
void tDecList(Node *node,Type spec)
{
    if(node !=NULL)
    {
        tDec(node->child[0],spec);
        if(node->childno == 3)
        {
            tDecList(node->child[2],spec);
        }
    }
}


// Dec     : VarDec               
//         | VarDec ASSIGNOP Exp  a = 5
//         ;
//vardec: 标识符或数组
void tDec(Node *node,Type spec)
{
    if(node == NULL) return;
    FieldList field = tVarDec(node->child[0],spec);
	// Node * temp = node->child[0];
	// while( strcmp(temp->name,"ID") !=0)
	// {
	// 	temp=temp->child[0];
	// }
	// char * name=temp->yytext;
	// printf("%s",name);
	// printSymbol();
	// FieldList field = search(name,0);
	// printf("%s",field->name);
	// if(field == NULL) printf("debug");

{//lab3 变量定义
//变量声明语句DEC用于为一个函数体内的局部变量声明其所需要的空间，该空间的大
//小以字节为单位。这个语句是专门为数组变量和结构体变量这类需要开辟一段连续的内存空间
//的变量所准备的。
	if(spec == NULL){printf("debug 428\n"); return;}
	if (field->type->kind == ARRAY  || (spec!= NULL  && spec->kind  == STRUCTURE) ) 
    {
		Operand op = (Operand)malloc(sizeof(Operand_));
		op->kind = VARIABLE_OP;
		strcpy(op->u.value, field->name);

		InterCode decIR = (InterCode)malloc(sizeof(InterCode_));
		decIR->kind = DEC_IR;
		decIR->operands[0] = op;
		decIR->size = getSpace(field->type);

		// if(spec==NULL || spec->kind  != STRUCTURE )
		// {
		// 	decIR->size = getSpace(field->type);
		// }
		// else if(field->type->kind != ARRAY )
		// {
		// 	decIR->size = getSpace(spec);
		// }
		// else
		// {
		// 	int x1 = getSpace(field->type);
		// 	int x2 = getSpace(spec);
		// 	printf("%d %d\n",x1,x2);
		// 	decIR->size = x1*x2;
		// }
		insertCode(decIR);
	}
	else if (field->type->kind == STRUCTURE || field->type->kind == STR_SPE)
	{
		printf("debug : type :%d",field->type->kind);
	}
	else if(spec->kind  == STR_SPE )
	{
		printf("debug 447");
	}
}
    //VarDec ASSIGNOP Exp
    if(node->childno == 3)
    {
		//------------------
		{//lab3 函数内部局部变量赋值定义
		Operand place = (Operand)malloc(sizeof(Operand_));
		if (strcmp(node->child[2]->child[0]->name, "INT") == 0) 
		{//如果是int 就是个constant 优化一下直接赋值就可
			tExp(node->child[2], NULL);
			place->kind = CONSTANT_OP;
			sprintf(place->u.value, "%s", node->child[2]->child[0]->yytext);
		}
		else {//否则就是局部变量 除非重新定义
			place->kind = TEMPVAR_OP;
			tExp(node->child[2], place);
		}

		if (place->kind != VARIABLE_OP || strcpy(place->u.value, field->name) != 0) 
		//防止同一个变量重复输出
		{
			Operand op1 = (Operand)malloc(sizeof(Operand_));
			op1->kind = VARIABLE_OP;
			strcpy(op1->u.value, field->name);

			InterCode addrIR = (InterCode)malloc(sizeof(InterCode_));
			addrIR->kind = ASSIGN_IR;
			addrIR->operands[0] = op1;
			addrIR->operands[1] = place;
			insertCode(addrIR);
		}
		}
		//-------------------------------

    }
}

// VarDec      : ID                
//             | VarDec LB INT RB  
//             ;
// a a[10][2]
//将变量返回 无需做检查
FieldList tVarDec(Node *node,Type spec)
{
    Node * temp = node;
    int num =0 ;
    // VarDec 循环到最后的ID得到标识名
    while(strcmp(temp->child[0]->name,"ID") != 0)
    {
        temp = temp->child[0];
        num++;
    }
    FieldList field = (FieldList)malloc(sizeof(FieldList_));
    field->scope_id = current_id;
    field->name = temp->child[0]->yytext;


    //num = 0
    if(strcmp(node->child[0]->name,"ID") == 0)
    {
        field->type = spec;
        return field;
    }
    //num > 0
    Node * temp2 = node;
    Type last = spec;
    for(int i=0;i<num;i++)
    {
        Type ti = (Type)malloc(sizeof(Type_));
        ti->kind = ARRAY;
        //值每一维都要递进
        ti->u.array.size = atoi(temp2->child[2]->yytext);
        temp2 = temp2->child[0];
        //类型每一维都要递进
        ti->u.array.elem = last;
        last = ti;

        field->type = ti;
    }
    return field;

}


void tExp(Node * node, Operand  place)
{
	//printf("debug:%d %s %d\n",node->childno,node->name,node->lineno);
	if(node == NULL) return;
    if (node->childno ==3 && strcmp(node->child[1]->name, "ASSIGNOP") == 0)
    {   
		//Exp ASSIGNOP EXP
		//Exp1 ：ID | Exp DOT ID  |  Exp LB Exp RB
		if(strcmp(node->child[0]->child[0]->name, "ID") == 0)
		{
// variable = lookup(sym_table, Exp1.ID)
// t1 = new_temp()
// code1 = translate_Exp(Exp2, sym_table, t1)
// code2 = [variable.name := t1] +4 [place := variable.name]
// return code1 + code2
			FieldList f = search(node->child[0]->child[0]->yytext,0);

			Operand right = new_temp();
			tExp(node->child[2],right);
			Operand left = (Operand)malloc(sizeof(Operand_));
			left->kind = VARIABLE_OP;
			strcpy(left->u.value,f->name);

			InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
			code2->kind = ASSIGN_IR;
			code2->operands[0] = left;
			code2->operands[1] = right;
			insertCode(code2);

			if(place != NULL)
			{
				InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
				code3->kind = ASSIGN_IR;
				code3->operands[0] = place;
				code3->operands[1] = right;
				insertCode(code3);
			}
			insertdebug("ASSIGN");
			return;
		}
		else if(node->childno == 1)
		{
			printf("debug 559\n");
		}
		else if(strcmp(node->child[0]->child[1]->name, "DOT") == 0)
		{//Exp DOT ID 
			Operand left = new_temp();
			tExp(node->child[0],left);
			Operand right = new_temp();
			tExp(node->child[2],right);

			InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
			code2->kind = ASSIGN_IR;
			code2->operands[0] = left;
			code2->operands[1] = right; // 右值如果是结构体kind 已改成ADDR_OP *
			insertCode(code2);

			if(place != NULL)
			{
				InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
				code3->kind = ASSIGN_IR;
				code3->operands[0] = place;//*x= y
				code3->operands[1] = right;
				insertCode(code3);
			}
		}
		else if (strcmp(node->child[0]->child[1]->name, "LB") == 0)
		{//Exp ASSIGNOP EXP
			Operand left = new_temp();
			tExp(node->child[0],left);
			Operand right = new_temp();
			tExp(node->child[2],right);

			InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
			code2->kind = ASSIGN_IR;
			code2->operands[0] = left;
			code2->operands[1] = right; // 右值如果是结构体kind 已改成ADDR_OP *
			insertCode(code2);

			if(place != NULL)
			{
				InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
				code3->kind = ASSIGN_IR;
				code3->operands[0] = place;//*x= y
				code3->operands[1] = right;
				insertCode(code3);
			}
		}
		// else if(strcmp(node->child[0]->child[1]->name, "LB") == 0)
		// {//数组

		// }
    }
    //Exp AND|OR|RELOP Exp
    if (node->childno ==3 &&
       ( strcmp(node->child[1]->name, "AND") == 0 | strcmp(node->child[1]->name, "OR") == 0 
       |strcmp(node->child[1]->name, "RELOP") == 0 ))
    {
// 操作数类型不匹配或操作数类型与操作符不匹配（例如整型变量与数组变
// 量相加减，或数组（或结构体）变量与数组（或结构体）变量相加减）。

// label1 = new_label()
// label2 = new_label()
// code0 = [place := #0]
// code1 = translate_Cond(Exp, label1, label2, sym_table)
// code2 = [LABEL label1] + [place := #1]
// return code0 + code1 + code2 + [LABEL label2]
		Operand label1 = new_label();
		Operand label2 = new_label();
		InterCode code0 = (InterCode)malloc(sizeof(InterCode_));
		code0->kind = ASSIGN_IR;
		code0->operands[0] = place;
		code0->operands[1] = new_constant(0);
		insertCode(code0);
		tCond(node,label1,label2);
		//label1
		InterCode l1 = (InterCode)malloc(sizeof(InterCode_)); 
		l1->kind = LABEL_IR;
		l1->operands[0] = label1;
		insertCode(l1);
		//place := #1place := #1
		InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
		code2->kind = ASSIGN_IR;
		code2->operands[0] = place;
		code2->operands[1] = new_constant(1);
		insertCode(code2);
		//label2
		InterCode l2 = (InterCode)malloc(sizeof(InterCode_)); 
		l2->kind = LABEL_IR;
		l2->operands[0] = label2;
		insertCode(l2);
		return;

    }
    // +-*/
//         | Exp PLUS Exp      a+b
//         | Exp MINUS Exp     a-b
//         | Exp STAR Exp      a*b
//         | Exp DIV Exp       a/b
    if (node->childno ==3 &&(
(strcmp(node->child[1]->name, "PLUS") == 0) || (strcmp(node->child[1]->name, "MINUS") == 0) || (strcmp(node->child[1]->name, "STAR") == 0) || (strcmp(node->child[1]->name, "DIV") == 0))
    )
    {
		Node *Exp1 = node->child[0];
		Node *Exp2 = node->child[2];

// t1 = new_temp()
// t2 = new_temp()
// code1 = translate_Exp(Exp1, sym_table, t1)
// code2 = translate_Exp(Exp2, sym_table, t2)
// code3 = [place := t1 + t2]
// return code1 + code2 + code3
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		tExp(Exp1,t1);
		tExp(Exp2,t2);
		InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
		if(strcmp(node->child[1]->name, "PLUS") == 0)
			code3->kind = PLUS_IR;
		else if(strcmp(node->child[1]->name, "MINUS") == 0)
			code3->kind = MINUS_IR;
		else if(strcmp(node->child[1]->name, "STAR") == 0)
			code3->kind = STAR_IR;
		else 
			code3->kind = DIV_IR;
		code3->operands[0] = place;
		code3->operands[1] = t1;
		code3->operands[2] = t2;
		insertCode(code3);

		return;
    }
    //         | LP Exp RP         (a)
    //         | MINUS Exp         -a
    //         | NOT Exp           ~a
    if ((strcmp(node->child[0]->name, "LP") == 0) || (strcmp(node->child[0]->name, "MINUS") == 0) || (strcmp(node->child[0]->name, "NOT") == 0) )
    {
		if(strcmp(node->child[0]->name, "NOT") == 0)
		{
		Operand label1 = new_label();
		Operand label2 = new_label();
		InterCode code0 = (InterCode)malloc(sizeof(InterCode_));
		code0->kind = ASSIGN_IR;
		code0->operands[0] = place;
		code0->operands[1] = new_constant(0);
		insertCode(code0);
		tCond(node,label1,label2);
		//label1
		InterCode l1 = (InterCode)malloc(sizeof(InterCode_)); 
		l1->kind = LABEL_IR;
		l1->operands[0] = label1;
		insertCode(l1);
		//place := #1place := #1
		InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
		code2->kind = ASSIGN_IR;
		code2->operands[0] = place;
		code2->operands[1] = new_constant(1);
		insertCode(code2);
		//label2
		InterCode l2 = (InterCode)malloc(sizeof(InterCode_)); 
		l2->kind = LABEL_IR;
		l2->operands[0] = label2;
		insertCode(l2);
		return;
		}
		else if((strcmp(node->child[0]->name, "LP") == 0) )
		{//(Exp)
			tExp(node->child[1],place);
		}
		else if((strcmp(node->child[0]->name, "MINUS") == 0))
		{
// t1 = new_temp()
// code1 = translate_Exp(Exp1, sym_table, t1)
// code2 = [place := #0 - t1]
// return code1 + code2
			Operand t1 = new_temp();
			tExp(node->child[1],t1);
			InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
			code2->kind = MINUS_IR;
			code2->operands[0] = place;
			code2->operands[1] = new_constant(0);
			code2->operands[2] = t1;
			insertCode(code2);
		}

		return;
    }

//         | ID                a     左值
//         | INT               1
//         | FLOAT             1.0
    if(node->childno == 1 && (strcmp(node->child[0]->name, "ID") == 0) )
    {//ID
    //找变量 不会增加中间代码 只是填充内容然后让外面的增加
		char* name = node->child[0]->yytext;
		FieldList f = search(name,0 );
		//printf("%s\n",name);
		//printSymbol();
		if(f == NULL)
		{
			printf("debug 733\n");return;
		}
		
		if (place != NULL) 
		{
		//printf("%s\n",name);

		//memset(place,0,sizeof(Operand_));
		if( (f->type->kind  == STRUCTURE || f->type->kind == ARRAY)  && !(strcmp(f->ifparam,"acac") == 0 )				//并且不是参数	
		)
		{
			//printf("%s\n",name);
			place->kind = QU_ADDR_OP;
			
		}
		else
		{
			place->kind = VARIABLE_OP;
			
		}
		place->type = f->type;//满足(f->type->kind  == STRUCTURE || f->type->kind == ARRAY)   就要赋值type 一起赋值了
		//printf("\nturn %s into %s\n",place->u.value, node->child[0]->yytext);
		strcpy(place->u.value, node->child[0]->yytext);

			//printf("%d\n",place->kind);
		}
		return;
    }



    if(strcmp(node->child[0]->name, "INT") == 0)//INT
    {
        Type t = (Type) malloc (sizeof(Type_));
        t->kind = BASIC;
        t->u.basic = INT_TYPE;

		if (place != NULL) {
			InterCode intIR = (InterCode)malloc(sizeof(InterCode_));
			intIR->kind = ASSIGN_IR;
			Operand intOp = (Operand)malloc(sizeof(Operand_));
			intOp->kind = CONSTANT_OP;
			strcpy(intOp->u.value, node->child[0]->yytext);
			intIR->operands[1] = intOp;
			place->kind = TEMPVAR_OP;
			place->u.var_no = tnum++;
			//place->tempint = atoi(node->child[0]->yytext);
			intIR->operands[0] = place;
			insertCode(intIR);
		}
		return;
    }
    if(strcmp(node->child[0]->name, "FLOAT") == 0)
    {
		return;
    }


    if(strcmp(node->child[0]->name, "ID") == 0)
    {
//         | ID LP Args RP     a(b) // 函数调用
//         | ID LP RP          a()
        //找函数名
        FieldList field = search(node->child[0]->yytext,1);
        Type rtype = field->type;
		if (strcmp(node->child[2]->name, "RP") == 0) 
		{
// function = lookup(sym_table, ID)
// if (function.name == “read”) return [READ place]
// return [place := CALL function.name]
			if (strcmp("read", node->child[0]->yytext) == 0) 
			{//read t1
				if (place != NULL) 
				{
					InterCode readIR = (InterCode)malloc(sizeof(InterCode_));
					readIR->kind = READ_IR;
					place->kind = TEMPVAR_OP;
					place->u.var_no = tnum++;
					readIR->operands[0] = place;
					insertCode(readIR);
				}
			}
			else {
				Operand funcOp = (Operand)malloc(sizeof(Operand_));
				funcOp->kind = FUNCTION_OP;
				strcpy(funcOp->u.value, node->child[0]->yytext);
				InterCode callIR = (InterCode)malloc(sizeof(InterCode_));
				if (place == NULL) {
					printf("debug 802\n");
					place = (Operand)malloc(sizeof(Operand_));
				}
				callIR->kind = CALL_IR;
				callIR->operands[0] = place;
				callIR->operands[1] = funcOp;
				place->kind = TEMPVAR_OP;
				place->u.var_no = tnum++;
				insertCode(callIR);
			}
		}
        if(strcmp(node->child[2]->name, "Args") == 0)
        {
// function = lookup(sym_table, ID)
// arg_list = NULL
// code1 = translate_Args(Args, sym_table, arg_list)
// if (function.name == “write”) return code1 + [WRITE arg_list[1]] + [place := #0]
			if (strcmp("write", node->child[0]->yytext) == 0) 
			{
				Operand argOp = (Operand)malloc(sizeof(Operand_));
				//只有一个参数
				Node *exp = node->child[2]->child[0];//Args -> exp
				if (strcmp(exp->child[0]->name, "INT") == 0) { //code1
					tExp(exp, NULL);
					argOp->kind = CONSTANT_OP;
					sprintf(argOp->u.value, "%s", exp->child[0]->yytext);
				}
				else {
					argOp->kind = TEMPVAR_OP;
					tExp(exp, argOp);
				}
				InterCode writeIR = (InterCode)malloc(sizeof(InterCode_));
				writeIR->kind = WRITE_IR;
				// if(argOp->kind = ADDR_OP)//todo
				// {
				// 	Operand tx = (Operand)malloc(sizeof(Operand_));
				// 	tx->kind = TEMPVAR_OP;
				// 	tx->u = argOp->u;
				// 	writeIR->operands[0] = tx;

				// }
				// else
				// {
				// 	writeIR->operands[0] = argOp;
				// }
				writeIR->operands[0] = argOp;

				insertCode(writeIR);//write arg_list[1]

				if(place != NULL)//write 返回0
				{
					Operand t = new_constant(0);
					InterCode pl0 = (InterCode)malloc(sizeof(InterCode_));
					pl0->kind = ASSIGN_IR;
					pl0->operands[0] = t;
					insertCode(pl0);
				}
			}
			else
			{
	// function = lookup(sym_table, ID)
	// arg_list = NULL
	// code1 = translate_Args(Args, sym_table, arg_list)
	// for i = 1 to length(arg_list) code2 = code2 + [ARG arg_list[i]]
	// return code1 + code2 + [place := CALL function.name]

	//         | ID LP Args RP     a(b) // 函数调用
				Node * args = node->child[2];
				Operand* argslist = (Operand*)malloc(50* sizeof(Operand) );
	// t1 = new_temp()
	// code1 = translate_Exp(Exp, sym_table, t1)
	// arg_list = t1 + arg_list
	// code2 = translate_Args(Args1, sym_table, arg_list)
	// return code1 + code2

// Args    : Exp COMMA Args 
//         | Exp            
//         ;

				int i =0;
				while(1)
				{	
					Operand t1 = new_temp();
					tExp(args->child[0],t1);
					argslist[i++] = t1; 
					if(args->childno == 3)
					{
						args = args->child[2];
					}
					else
					{
						break;
					}
				}
				for(int j=0;j<i;j++)
				{
					InterCode code2 =(InterCode)malloc(sizeof(InterCode_));
					code2->kind = ARG_IR;
					code2->operands[0]=argslist[j];
					if(argslist[j]->kind ==ADDR_OP)//todo
					{
						argslist[j]->kind = TEMPVAR_OP;
					}
					insertCode(code2);
				}

				free(argslist);
				argslist = NULL;
				Operand funcOp = (Operand)malloc(sizeof(Operand_));
				funcOp->kind = FUNCTION_OP;
				strcpy(funcOp->u.value, node->child[0]->yytext);

				InterCode callIR = (InterCode)malloc(sizeof(InterCode_));
				callIR->kind = CALL_IR;
				if (place == NULL) {
					printf("debug 901\n");
					place = (Operand)malloc(sizeof(Operand_));
				}
				place->kind = TEMPVAR_OP;
				place->u.var_no = tnum++;
				callIR->operands[0] = place;
				callIR->operands[1] = funcOp;
				insertCode(callIR);
			}

        }
		return;
    }
	//         | Exp LB Exp RB     a[b]  左值
	//(bodies[o_cnt].points[i_cnt]).x 
    if ( node->childno ==4 &&
        ( strcmp(node->child[1]->name, "LB") == 0))
    {
		//t1 数组首地址 最里层是ID t2 整型index
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		Operand t3 = new_temp();
		//printf("%s",node->child[0]->child[0]->yytext);
		tExp(node->child[0],t1);//code1
		tExp(node->child[2],t2);//code2
		if(t1->type == NULL)
		{
			printf("debug 999\n");
			return;
		}
		if(t1->type->kind !=ARRAY)
		{
			printf("debug 942\n");
			return;
		}
		
		int size = getSpace(t1->type->u.array.elem);
		InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
		code3->kind = STAR_IR;
		code3->operands[0] = t3;
		code3->operands[1] = t2;
		code3->operands[2] = new_constant(size);
		insertCode(code3);
		if(t1->type->u.array.elem->kind == ARRAY
		|| t1->type->u.array.elem->kind == STRUCTURE)
		{	//(bodies[o_cnt].points[i_cnt].x) 
			InterCode code4 = (InterCode)malloc(sizeof(InterCode_));
			code4->kind = PLUS_IR;
			if(place == NULL) 
			{
				printf("debug:989\n");
				place = new_temp();
			}
			place->type = t1->type->u.array.elem;
			code4->operands[0] = place;
			code4->operands[1] = t1;
			code4->operands[2] = t3;
			insertCode(code4);//作为地址
		    insertdebug("ARRAY1");

		}
		else
		{
			Operand t4 = new_temp();
			InterCode code4 = (InterCode)malloc(sizeof(InterCode_));
			code4->kind = PLUS_IR;
			code4->operands[0] = t4;
			code4->operands[1] = t1;
			code4->operands[2] = t3;
			if(place == NULL) 
			{
				printf("debug:1015\n");
				place = new_temp();
			}
			
			place->kind = ADDR_OP;//在外面会取*作为值
			place->u.var_no=t4->u.var_no;
			insertCode(code4);
		insertdebug("ARRAY2");

		}

    }
    //         | Exp DOT ID        a.b   左值
    if (node->childno ==3 &&(
        strcmp(node->child[1]->name, "DOT") == 0))
    {

//计算并传地址出去 这个地址就是place 计算完后改kind为ADDR
		Node * exp1 = node->child[0];
		Operand t1= new_temp();
		tExp(exp1,t1);//找到结构体变量名字
		
		//Exp DOT ID
		FieldList stru = t1->type->u.structure;
		//结构体类型信息
		int s = getSpace(t1->type);
		int m = getSpace(stru->type);//计算偏移量
		if(stru->type->kind  ==ARRAY &&  stru->type->u.array.elem->kind == STRUCTURE || STR_SPE)
		{
		 	//int temp = getSpace(stru->type->u.array.elem) ;
			//m = m*temp/4;
		}
		s -= m;
		//printf("%d",s);
		while(stru != NULL)//结构体类型是倒着存的
		{
			//printf("pipei %s %d\n",stru->name,s);
			if(strcmp(stru->name,node->child[2]->yytext )==0)
			{
				InterCode addrIR = (InterCode)malloc(sizeof(InterCode_));
				addrIR->kind = PLUS_IR;
				//Operand t1 = new_temp();
				if(place == NULL) {
					place = new_temp();
					printf("debug struct place\n");}
				// Operand t1 = (Operand)malloc(sizeof(Operand_));
				// t1->kind = place->kind;
				// t1->u = place->u;
				// addrIR->operands[0] = t1;
				// addrIR->operands[1] = t1;
				// Operand t2 = new_constant(s);
				// addrIR->operands[2] = t2;
				// insertCode(addrIR);
				// place->kind = ADDR_OP;//先传出去后改类型表明是地址传输
				if(stru->type->kind == ARRAY ||
				stru->type->kind == STRUCTURE)
				{
					Operand t2 = new_temp();
					InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
					code2->kind = PLUS_IR;
					code2->operands[0] = t2;
					code2->operands[1] = t1;
					code2->operands[2] = new_constant(s);
					insertCode(code2);
					place->type = stru->type;
					place->kind =t2->kind;
					place->u.var_no=t2->u.var_no;
					//place->kind = ADDR_OP;
					char str[50];
					//printf("%s %d %d",stru->name,stru->type->kind,getSpace(stru->type));  points 1 12
					sprintf(str,"STRUCT1%s",stru->name);//points;
					insertdebug(str);
				}
				else
				{
					InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
					code2->kind = PLUS_IR;
					Operand t2 = (Operand)malloc(sizeof(Operand_));
					t2->kind = place->kind;
					t2->u = place->u;
					code2->operands[0] = t2;
					code2->operands[1] = t1;
					code2->operands[2] = new_constant(s);
					place->type = stru->type;
					insertCode(code2);
					place->kind = ADDR_OP;
					char str[50];
					sprintf(str,"STRUCT2%s",stru->name);//x
					insertdebug(str);

				}

				break;
			}
			s -= getSpace(stru->type);
			stru = stru->tail;
		}
		
		

		return;
    }

}


void tCond(Node* node,Operand label_true,Operand label_false)
{
	//Exp1 RELOP Exp2
	if(node->childno == 3 && strcmp(node->child[1]->name, "RELOP") == 0)
	{
// t1 = new_temp()
// t2 = new_temp()
// code1 = translate_Exp(Exp1, sym_table, t1)
// code2 = translate_Exp(Exp2, sym_table, t2)
// op = get_relop(RELOP);
// code3 = [IF t1 op t2 GOTO label_true]
// return code1 + code2 + code3 + [GOTO label_false]
		Operand t1 = new_temp();
		Operand t2 = new_temp();
		tExp(node->child[0],t1);//code1
		tExp(node->child[2],t2);//code2
		char * op = node->child[1]->yytext;
		InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
		code3->kind = IF_GOTO_IR;
		code3->operands[0] = t1;
		code3->operands[1] = t2;
		code3->operands[2] = label_true;
		strcpy(code3->relop,op);
		insertCode(code3);//code3

		InterCode code4 = (InterCode)malloc(sizeof(InterCode_));
		code4->kind = GOTO_IR;
		code4->operands[0] = label_false;
		insertCode(code4);
	}
	//NOT Exp1
	else if (node->childno == 2 && strcmp(node->child[0]->name, "NOT") == 0)
	{//translate_Cond(Exp1, label_false, label_true, sym_table)
		Node* exp1 = node->child[1];
		tCond(exp1,label_false,label_true);
	}
	//Exp1 AND Exp2
	else if(node->childno == 3 && strcmp(node->child[1]->name, "AND") == 0)
	{
// label1 = new_label()
// code1 = translate_Cond(Exp1, label1, label_false, sym_table)
// code2 = translate_Cond(Exp2, label_true, label_false, sym_table)
// return code1 + [LABEL label1] + code2
		Operand label1 = new_label();
		tCond(node->child[0],label1,label_false);
		InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
		code3->kind = LABEL_IR;
		code3->operands[0] = label1;
		insertCode(code3);
		tCond(node->child[2],label_true,label_false);
	}
	//Exp1 OR Exp2
	else if(node->childno == 3 && strcmp(node->child[1]->name, "OR") == 0)
	{
// label1 = new_label()
// code1 = translate_Cond(Exp1, label_true, label1, sym_table)
// code2 = translate_Cond(Exp2, label_true, label_false, sym_table)
// return code1 + [LABEL label1] + code2
		Operand label1 = new_label();
		tCond(node->child[0],label_true,label1);
		InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
		code3->kind = LABEL_IR;
		code3->operands[0] = label1;
		insertCode(code3);
		tCond(node->child[2],label_true,label_false);
	}
	else
	{
// t1 = new_temp()
// code1 = translate_Exp(Exp, sym_table, t1)
// code2 = [IF t1 != #0 GOTO label_true]
// return code1 + code2 + [GOTO label_false]
		Operand t1 = new_temp();
		tExp(node,t1);
		InterCode code2 = (InterCode)malloc(sizeof(InterCode_));
		code2->kind = IF_GOTO_IR;
		code2->operands[0] = t1;
		strcpy(code2->relop ,"!=");
		//#0
		Operand t2 = (Operand)malloc(sizeof(Operand_));
		t2->kind = CONSTANT_OP;
		strcpy(t2->u.value ,"0");
		code2->operands[1] = t2;
		code2->operands[2] = label_true;
		insertCode(code2);
		InterCode code3 = (InterCode)malloc(sizeof(InterCode_));
		code3->kind = GOTO_IR;
		code3->operands[0] = label_false;
		insertCode(code3);
	}
}


void tExtDecList(Node *node)
{

    // // 定义全局变量
    // FieldList field = VarDec(node->child[0],spec);
    
    // if(ifexist(field->name,field->scope_id) != NULL)
    //     printf("Error type 3 at Line %d: Redefined variable %s.\n",node->child[0]->lineno,field->name);
    // else
    //     insert(field);
    
    // if(node->childno == 3)
    // {
    //     ExtDecList(node->child[2],spec);
    // }
}




void initIRList() {
	IRList = (InterCode*)malloc(SIZE * sizeof(InterCode));
	if (IRList == NULL) {
		printf("error\n");
		return;
	}
	IRMAXSIZE = SIZE;
	//printf("debug : %d\n",IRMAXSIZE);
	IRsize = 0;

    scope_id = 0;
    scope sc;
    sc.id = 0;
    sc.parent_id = -1;//表示自己是最外层的
    sc.w[0] = 0;
    sc.wno =1;
    current_id = 0;
    sc_table[current_id] = sc;//注意！给表加上别漏了
}

void insertCode(InterCode ir) {
	if (IRsize >= IRMAXSIZE) {
		IRList = (InterCode*)realloc(IRList, sizeof(InterCode)*IRMAXSIZE * 2);
		IRMAXSIZE = IRMAXSIZE * 2;
	}
	//printf("%d\n",IRMAXSIZE);
	IRList[IRsize] = ir;
	IRsize++;
}
void deletelastCode()
{
	IRsize--;
	IRList[IRsize] = NULL;
}

void repr(Operand op, FILE *fp) {
	if (op == NULL) {
		fputs("t0	", fp);
		return;
	}
	char str[50];
	memset(str, 0, sizeof(str));
	switch (op->kind) {

	case VARIABLE_OP:
		if (op->u.value != NULL) {
			sprintf(str, "%s", op->u.value);
			fputs(str, fp);
		}
		break;
	case TEMPVAR_OP:
		sprintf(str, "temp%d", op->u.var_no);
		fputs(str, fp);
		break;
	case CONSTANT_OP:
		sprintf(str, "#%s", op->u.value);
		fputs(str, fp);
		break;
	case ADDR_OP:
		sprintf(str, "*temp%d", op->u.var_no);
		fputs(str, fp);
		break;
	case QU_ADDR_OP:
		sprintf(str, "&%s", op->u.value);
		fputs(str, fp);
		break;
	case LABEL_OP:
		sprintf(str, "label%d", op->u.label_no);
		fputs(str, fp);
		break;
	case FUNCTION_OP:
		sprintf(str, "%s", op->u.value);
		fputs(str, fp);
		break;
	}
}
void printCode(char *filename) {
	FILE *fp;
	if (strcmp(filename, "stdout") == 0) {
		fp = stdout;
	}
	else {
		fp = fopen(filename, "w");
	}
	if (fp == NULL) {
		printf("open file error!\n");
		return;
	}
	//printf("the number of IR:%d\n",IRsize);
	for (int i = 0; i < IRsize; i++) {
		InterCode ir = IRList[i];
		if (ir == NULL) {
			continue;
		}
		switch (ir->kind) 
		{
		case LABEL_IR:
			fputs("LABEL ", fp);
			repr(ir->operands[0], fp);
			fputs(" : ", fp);
			break;
		case FUNCTION_IR:
			fputs("FUNCTION ", fp);
			repr(ir->operands[0], fp);
			fputs(" : ", fp);
			break;
		case ASSIGN_IR:
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			break;
		case PLUS_IR:
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			fputs(" + ", fp);
			repr(ir->operands[2], fp);
			break;
		case MINUS_IR:
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			fputs(" - ", fp);
			repr(ir->operands[2], fp);
			break;
		case STAR_IR:
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			fputs(" * ", fp);
			repr(ir->operands[2], fp);
			break;
		case DIV_IR:
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			fputs(" / ", fp);
			repr(ir->operands[2], fp);
			break;
		case ADDR_IR2:
			repr(ir->operands[0], fp);
			fputs(" := &", fp);
			repr(ir->operands[1], fp);
			break;
		case ADDR_IR3:
			repr(ir->operands[0], fp);
			fputs(" := &", fp);
			repr(ir->operands[1], fp);
			fputs(" + ", fp);
			repr(ir->operands[2], fp);
			break;
		case ADDR_VALUE_IR:
			repr(ir->operands[0], fp);
			fputs(" := *", fp);
			repr(ir->operands[1], fp);
			break;
		case MEMORY_IR:
			fputs("*", fp);
			repr(ir->operands[0], fp);
			fputs(" := ", fp);
			repr(ir->operands[1], fp);
			break;
		case GOTO_IR:
			fputs("GOTO ", fp);
			repr(ir->operands[0], fp);
			break;
		case IF_GOTO_IR:
			fputs("IF ", fp);
			repr(ir->operands[0], fp);
			fputs(" ", fp);
			fputs(ir->relop, fp);
			fputs(" ", fp);
			repr(ir->operands[1], fp);
			fputs(" GOTO ", fp);
			repr(ir->operands[2], fp);
			break;
		case RETURN_IR:
			fputs("RETURN ", fp);
			repr(ir->operands[0], fp);
			break;
		case DEC_IR:
			fputs("DEC ", fp);
			repr(ir->operands[0], fp);
			char str[10];
			memset(str, 0, sizeof(str));
			sprintf(str, " %d ", ir->size);
			fputs(str, fp);
			break;
		case ARG_IR:
			fputs("ARG ", fp);
			repr(ir->operands[0], fp);
			break;
		case CALL_IR:
			repr(ir->operands[0], fp);
			fputs(" := CALL ", fp);
			repr(ir->operands[1], fp);
			break;
		case PARAM_IR:
			fputs("PARAM ", fp);
			repr(ir->operands[0], fp);
			break;
		case READ_IR:
			fputs("READ ", fp);
			repr(ir->operands[0], fp);
			break;
		case WRITE_IR:
			fputs("WRITE ", fp);
			repr(ir->operands[0], fp);
			break;
		case DEBUG_IR:
			fputs("DEBUG", fp);
			fputs(ir->operands[0]->u.value,fp);
			break;
		}
		fputs("\n", fp);
	}
	fclose(fp);
}


int getSpace(Type type) {
	if (type == NULL) {
		return 0;
	}
	if (type->kind  == ARRAY)//数组 
	{
		// int size = 4;
		// //BASIC
		// while (type->u.array.elem->kind ==ARRAY) //返回4*index 如果同时是struct就不对了
		// {
		// 	size = type->u.array.size * size;
		// 	type = type->u.array.elem;
		// }
		// size = type->u.array.size * size;
		int size = type->u.array.size * getSpace(type->u.array.elem);

		return size;
	}
	else if (type->kind == STRUCTURE || type->kind == STR_SPE) 
	{
		// Body -> tag + points[3] = 4+36 = 40
		// points -> x+y+z = 12
		FieldList f = type->u.structure;
		int size = 0;
		while(f!= NULL)
		{
			int m = getSpace(f->type);
			// if(f->type->kind == ARRAY)
			// {
			// 	m = m*f->type->u.array.size;
			// }
			size += m;
			//printf("%d\n",size);
			f= f->tail;
		}
		return size;

	}
	else if(type->kind == BASIC)
	{
		if(type->u.basic == INT_TYPE)
		{
			return 4;
		}
	}
	else
	{
		printf("debug: getspace type:%d",type->kind);
	}
	printf("debug 1558");
	return 1;
}

Operand new_temp()
{
	Operand t = (Operand)malloc(sizeof(Operand_));
	t->kind = TEMPVAR_OP;
	t->u.var_no = tnum++;
	return t;
}


Operand new_label()
{
	Operand t = (Operand)malloc(sizeof(Operand_));
	t->kind = LABEL_OP;
	t->u.label_no = lnum++;
	return t;
}

Operand new_constant(int i)
{
	Operand t = (Operand)malloc(sizeof(Operand_));
	t->kind = CONSTANT_OP;
	sprintf(t->u.value ,"%d",i);
	//printf("%s",t->u.value);
	return t;
}


FieldList allsearch(char *name
,int flag// flag=1:function flag =2: str_spe flag=0:变量 原因在于函数名和变量名可以一样 只有2有用 表明结构体类型不能重名
)
{
	if(name == NULL){
		return NULL;
	}
	unsigned int key;
    key = hash_pjw(name);
	FieldList p=hashTable[key];
	while(p!=NULL)
    {
		if(strcmp(name,p->name)==0)
        {
            return p;
		}
		key=(++key)%HASH_SIZE;
		p=hashTable[key];
	}
	return NULL;
}

void insertdebug(char * info)
{
	// InterCode code  = (InterCode)malloc(sizeof(InterCode_));
	// code->kind = DEBUG_IR;
	// Operand debug = (Operand)malloc(sizeof(Operand));
	// strcpy(debug->u.value , info);
	// code->operands[0] = debug;
	// insertCode(code);
}
