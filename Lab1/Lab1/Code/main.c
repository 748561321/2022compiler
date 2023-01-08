#include<stdio.h>
#include"tree.h"
//extern FILE* yyin;
void perror(const char *__s);
int yyrestart();
int yyparse();
//int yydebug;
int error = 0;
Node * Root = NULL;
extern void printTree(Node *root,int number);
extern int yylineo;
// void debug(char * str)
// {
//     printf("Error type B at line %d: %s\n", yylineno, str);
// }

int main(int argc, char** argv) 
{
    if(argc <=1) return 1;
    FILE* f = fopen(argv[1], "r");
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    //yydebug = 1;
    yyparse();
    if(error == 0)
    {
    printTree(Root,0);
    }
    return 0;
}

/*
flex lexical.l
gcc main.c lex.yy.c -lfl -o scanner
./scanner ../Test/test1.cmm

bison -d syntax.y 这个参数的含义是，将编译的结果分拆成syntax.tab.c和syntax.tab.h两个文件，其中.h文
件里包含着一些词法单元的类型定义之类的内容。
flex lexical.l
gcc main.c syntax.tab.c -lfl -ly -o parser
sudo apt-get install libbison-dev
./parser ../Test/test1.cmm
*/