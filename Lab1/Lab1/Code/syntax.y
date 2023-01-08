%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    #include "lex.yy.c"
    //void yyerror(char *str);
    extern int yylineno;
    extern Node* Root;
    extern int error;


    int lastline;
    int flag=1;
    void yyerror(char const *msg)
    {
        if(strcmp(msg,"syntax error") == 0)
        {
            printf("Error type B at Line %d: %s\n", yylineno,msg);
        }
    }
%}

%union {
    struct Node* node;
}

%token <node> INT FLOAT ID SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE

%right ASSIGNOP  
%left OR 
%left AND 
%left RELOP
%left PLUS MINUS 
%left STAR DIV
%right NOT
%left DOT LB RB LP RP

%nonassoc LOWER_THAN_ELSE 
%nonassoc ELSE

%type <node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args


%%


Program     : ExtDefList        {$$=createNode("Program","");addNode(1, $$, $1);Root=$$;}
            ;

ExtDefList  : ExtDef ExtDefList     {$$=createNode("ExtDefList","");addNode(2, $$, $1, $2);}
            |  /* empty */           {$$=NULL;}
            ;
                
ExtDef      : Specifier ExtDecList SEMI     {$$=createNode("ExtDef","");addNode(3, $$, $1, $2, $3);}
            | Specifier SEMI                {$$=createNode("ExtDef","");addNode(2, $$, $1, $2);}    
            | Specifier FunDec CompSt       {$$=createNode("ExtDef","");addNode(3, $$, $1, $2, $3);}
            //| error SEMI                    {error++;yyerror("Syntax error.");}
            | Specifier error               {error++;yyerror("Syntax error.");}
            ;
ExtDecList  : VarDec                        {$$=createNode("ExtDecList","");addNode(1, $$, $1);} 
            | VarDec COMMA ExtDecList       {$$=createNode("ExtDecList","");addNode(3, $$, $1, $2, $3);} 
            ;

            



Specifier   : TYPE                  {$$=createNode("Specifier","");addNode(1, $$, $1);}
            | StructSpecifier       {$$=createNode("Specifier","");addNode(1, $$, $1);}
            ;
            
StructSpecifier : STRUCT OptTag LC DefList RC   {$$=createNode("StructSpecifier","");addNode(5, $$, $1, $2, $3, $4, $5);}
                | STRUCT Tag                    {$$=createNode("StructSpecifier","");addNode(2, $$, $1, $2);}
                ;
            
OptTag  : ID                {$$=createNode("OptTag","");addNode(1, $$, $1);}
        | /* empty */        {$$=NULL;}
        ;
        
Tag     : ID                {$$=createNode("Tag","");addNode(1, $$, $1);}
        ;




VarDec      : ID                            {$$=createNode("VarDec","");addNode(1, $$, $1);}
            | VarDec LB INT RB              {$$=createNode("VarDec","");addNode(4, $$, $1, $2, $3, $4);}
            | VarDec LB error RB            {error++; yyerror("Missing \"]\".");}
            ;
            
FunDec      : ID LP VarList RP              {$$=createNode("FunDec","");addNode(4, $$, $1, $2, $3, $4);}
            | ID LP RP                      {$$=createNode("FunDec","");addNode(3, $$, $1, $2, $3);}
            | ID LP error RP                {error++;yyerror("Syntax error.");}
            ;
            
VarList     : ParamDec COMMA VarList        {$$=createNode("VarList","");addNode(3, $$, $1, $2, $3);}
            | ParamDec                      {$$=createNode("VarList","");addNode(1, $$, $1);}
            ;
            
ParamDec    : Specifier VarDec              {$$=createNode("ParamDec","");addNode(2, $$, $1, $2);}
            ;

            


CompSt      : LC DefList StmtList RC        {$$=createNode("CompSt","");addNode(4, $$, $1, $2, $3, $4);}
            | LC error RC                   {error++;yyerror("CompSt error.");}
            ;
            
StmtList    : Stmt StmtList                 {$$=createNode("StmtList","");addNode(2, $$, $1, $2);}
            | /* empty */                     {$$=NULL;}
            ;
            
Stmt    : Exp SEMI                                      {$$=createNode("Stmt","");addNode(2, $$, $1, $2);}
        | CompSt                                        {$$=createNode("Stmt","");addNode(1, $$, $1);}
        | RETURN Exp SEMI                               {$$=createNode("Stmt","");addNode(3, $$, $1, $2, $3);}
        | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE       {$$=createNode("Stmt","");addNode(5, $$, $1, $2, $3, $4, $5);}
        | IF LP Exp RP Stmt ELSE Stmt                   {$$=createNode("Stmt","");addNode(7, $$, $1, $2, $3, $4, $5, $6, $7);}
        | IF LP Exp RP error ELSE Stmt                  {error++;yyerror("Missing \";\".");}
        | WHILE LP Exp RP Stmt                          {$$=createNode("Stmt","");addNode(5, $$, $1, $2, $3, $4, $5);}
        ;   




DefList : Def DefList               {$$=createNode("DefList","");addNode(2, $$, $1, $2);}
        | /* empty */               {$$=NULL;}
        ;
        
Def     : Specifier DecList SEMI    {$$=createNode("Def","");addNode(3, $$, $1, $2, $3);}
        | Specifier error SEMI      {error++;yyerror("Def error.");}
        ;

DecList : Dec                       {$$=createNode("DecList","");addNode(1, $$, $1);}
        | Dec COMMA DecList         {$$=createNode("DecList","");addNode(3, $$, $1, $2, $3);}
        | Dec error DecList         {error++;yyerror("DecList error.");}
        | Dec error                 {error++;yyerror("DecList error.");}
        ;
        
Dec     : VarDec                    {$$=createNode("Dec","");addNode(1, $$, $1);}
        | VarDec ASSIGNOP Exp       {$$=createNode("Dec","");addNode(3, $$, $1, $2, $3);}
        | VarDec ASSIGNOP error     {error++;yyerror("Dec error.");}
        ;
            
        

Exp     : Exp ASSIGNOP Exp      {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | Exp AND Exp           {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | Exp OR Exp            {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | Exp RELOP Exp         {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | Exp PLUS Exp          {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | Exp MINUS Exp         {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | Exp STAR Exp          {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | Exp DIV Exp           {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | LP Exp RP             {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | MINUS Exp             {$$=createNode("Exp","");addNode(2, $$, $1, $2);}
        | NOT Exp               {$$=createNode("Exp","");addNode(2, $$, $1, $2);}
        | ID LP Args RP         {$$=createNode("Exp","");addNode(4, $$, $1, $2, $3, $4);}
        | ID LP RP              {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | Exp LB Exp RB         {$$=createNode("Exp","");addNode(4, $$, $1, $2, $3, $4);}
        | Exp LB error RB       {error++;yyerror("Missing \"]\".");}
        | Exp DOT ID            {$$=createNode("Exp","");addNode(3, $$, $1, $2, $3);}
        | ID                    {$$=createNode("Exp","");addNode(1, $$, $1);}
        | INT                   {$$=createNode("Exp","");addNode(1, $$, $1);}
        | FLOAT                 {$$=createNode("Exp","");addNode(1, $$, $1);}
        ;
    
Args    : Exp COMMA Args        {$$=createNode("Args","");addNode(3, $$, $1, $2, $3);}
        | Exp                   {$$=createNode("Args","");addNode(1, $$, $1);}
        ;

%%

