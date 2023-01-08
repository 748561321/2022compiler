#include<stdio.h>
#include "intercode.h"
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
    //printTree(Root,0);
    if(error == 0)
    {
        //printTree(Root,0);
        initHashtable();
        Program(Root);
        check_declar();

        //printSymbol();
        //lab3
        //initHashtable();
        initIRList();
        tProgram(Root);
        if(argc == 2)
        {
            printCode("stdout");
        }
        else if(argc == 3)
        {
            printCode(argv[2]);
        }
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


// Program (1)
//   ExtDefList (1)
//     ExtDef (1)
//       Specifier (1)
//         TYPE: int
//       FunDec (1)
//         ID: main                                 FUNCTION main :
//         LP
//         RP
//       CompSt (2)
//         LC
//         DefList (3)
//           Def (3)
//             Specifier (3)
//               TYPE: int
//             DecList (3)
//               Dec (3)
//                 VarDec (3)
//                   ID: n
//             SEMI
//         StmtList (4)
//           Stmt (4)
//             Exp (4)
//               Exp (4)
//                 ID: n
//               ASSIGNOP                               v1 := t1
//               Exp (4)
//                 ID: read                             READ t1
//                 LP
//                 RP
//             SEMI
//           StmtList (5)
//             Stmt (5)
//               IF                                     IF  v1 > t2 GOTO label1 GOTO label2
//               LP
//               Exp (5)
//                 Exp (5)
//                   ID: n                              v1 > t2
//                 RELOP
//                 Exp (5)
//                   INT: 0                             t2 := #0
//               RP
//               Stmt (5)
//                 Exp (5)
//                   ID: write                          WRITE t3
//                   LP
//                   Args (5)
//                     Exp (5)
//                       INT: 1                         t3 := #1
//                   RP
//                 SEMI
//               ELSE
//               Stmt (7)
//                 IF                                   IF v1 < t4 GOTO label4  GOTO label5 GOTO label6
//                 LP
//                 Exp (7)
//                   Exp (7)
//                     ID: n
//                   RELOP                              
//                   Exp (7)
//                     INT: 0                           t4 := #0
//                 RP
//                 Stmt (7)
//                   Exp (7)
//                     ID: write                         t6 := #0 - t5
//                     LP
//                     Args (7)
//                       Exp (7)                        t6 := #0 - t5
//                         MINUS
//                         Exp (7)
//                           INT: 1                     t5 := #1
//                     RP
//                   SEMI
//                 ELSE
//                 Stmt (8)
//                   Exp (8)
//                     ID: write                        
//                     LP
//                     Args (8)
//                       Exp (8)
//                         INT: 0                       
//                     RP
//                   SEMI
//             StmtList (9)
//               Stmt (9)
//                 RETURN
//                 Exp (9)
//                   INT: 0
//                 SEMI
//         RC