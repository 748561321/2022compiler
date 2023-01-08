#include "semantic.h"

Node* createNode(char* name,char * yytext)
{
    Node *p = (Node*)malloc(sizeof(Node));
    strcpy(p->name, name);
    strcpy(p->yytext,yytext);
    p->lineno = yylineno;
    for(int i=0;i<10;i++){
        p->child[i] = NULL;
    }
    p->childno = 0;
    return p;
}


// va_list arg_ptr：定义一个指向个数可变的参数列表指针；

// va_start(arg_ptr, argN)：使参数列表指针arg_ptr指向函数参数列表中的第一个可选参数，
// 说明：argN是位于第一个可选参数之前的固定参数，（或者说，最后一个固定参数；…之前的一个参数），
// 函数参数列表中参数在内存中的顺序与函数声明时的顺序是一致的。
// 如果有一va函数的声明是void va_test(char a, char b, char c, …)，
// 则它的固定参数依次是a,b,c，最后一个固定参数argN为c，因此就是va_start(arg_ptr, c)。

// va_arg(arg_ptr, type)：返回参数列表中指针arg_ptr所指的参数，返回类型为type，并使指针arg_ptr指向参数列表中下一个参数。

// va_copy(dest, src)：dest，src的类型都是va_list，va_copy()用于复制参数列表指针，将dest初始化为src。

// va_end(arg_ptr)：清空参数列表，并置参数指针arg_ptr无效。
// 说明：指针arg_ptr被置无效后，可以通过调用va_start ()、va_copy()恢复arg_ptr。
// 每次调用va_start() / va_copy()后，必须得有相应的va_end()与之匹配。
// 参数指针可以在参数列表中随意地来回移动，但必须在va_start() … va_end()之内。


void addNode(int childno, Node* parent, ...){
    va_list ap; 
    va_start(ap,parent);
    parent ->childno = childno;
    for(int i=0; i<childno; i++)
    {
        parent->child[i] = va_arg(ap, Node*);
    }
    parent->lineno = parent->child[0]->lineno;
    va_end(ap);
}

void printTree(Node *root,int number){
    if(root == NULL){
        return;
    }
    for(int i=0;i<number;i++)
    {
        printf(" ");
    }
    
    if(root->childno!=0)
    {
        printf("%s (%d)\n", root->name, root->lineno);
        for(int i=0; i<root->childno; i++)
        {
            printTree(root->child[i],number+2);
        }
    }
    // 如果当前结点是一个词法单元，则只要打印该词法单元的名称，而无需打印该词法单元的行号。
    else
    {
        if(strcmp("ID",root->name) == 0)
        {
            printf("%s: %s\n", root->name, root->yytext);
        }
        else if(strcmp("TYPE",root->name) == 0)
        {
            printf("%s: %s\n", root->name, root->yytext);
        }
        else if(strcmp("INT",root->name) == 0)
        {
            printf("%s: %d\n", root->name, atoi(root->yytext));
        }
        // else if(strcmp("INT8",root->name) == 0)
        // {
        //     char * temp = root->yytext;
        //     temp++;
        //     char * end =NULL;
        //     int res = strtol(temp,&end,8);
        //     printf("%s: %d\n", "INT", res);
        // }
        // else if(strcmp("INT16",root->name) == 0)
        // {
        //     char * temp = root->yytext;
        //     temp++;temp++;
        //     char * end =NULL;
        //     int res = strtol(temp,&end,16);
        //     printf("%s: %d\n", "INT", res);
        // }
        else if(strcmp("FLOAT",root->name) == 0)
        {
            printf("%s: %f\n", root->name, atof(root->yytext));
        }
        else
        {
            printf("%s\n", root->name);
        }
        
    }
}