#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int yylineno;
struct Node{
    char name[32];
    char yytext[32];
    struct Node *child[10];
    int childno;
    int lineno;
};
typedef struct Node Node;
Node* createNode(char* name, char* text);

void addNode(int childno, Node* parent, ...);

void printTree(Node *root,int number);

