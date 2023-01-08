%{
#include "syntax.tab.h"
//#define DEBUG

// int yycolumn = 1;
// #define YY_USER_ACTION \
// yylloc.first_line = yylloc.last_line = yylineno; \
// yylloc.first_column = yycolumn; \
// yylloc.last_column = yycolumn + yyleng - 1; \
// yycolumn += yyleng;
//\n { yycolumn = 1; }

void handle(char * match,char * yytext)
{
    #ifdef DEBUG
    printf("lex:line %d | %s | %s\n",yylineno,match,yytext);
    #endif
    yylval.node = createNode(match,yytext);
}

extern int error;
%}

%option yylineno
delim   [ \t\r\n]
ws      {delim}+
letter  [_a-zA-Z]
digit   [0-9]
relop   >|<|>=|<=|==|!=
type    int|float
id      {letter}({letter}|{digit})*
int10   [1-9]{digit}*|0
int8    0[0-7]+
int16   0[xX][0-9a-fA-F]+
float   {digit}*\.{digit}+|{digit}+\.
efloat  ({digit}*\.{digit}+|{digit}+\.)[eE][+-]?{digit}+

%%

"//" {
	char c = input();
	while (c!= '\n')
		c = input();
}

"/*" {
	char pre = input(), next = input();
	while (next) 
    {
		if(pre == '*' && next == '/') break;
        pre = next;
        next = input();
	}
	if (!next) 
    {
		printf("Error type B at line %d: Illegal /*.\n", yylineno);
		error++;
	}
}


{ws} {handle("ws",yytext);}
";" {handle("SEMI",yytext);return SEMI;}
"," {handle("COMMA",yytext);return COMMA;}
"=" {handle("ASSIGNOP",yytext);return ASSIGNOP;}//right
{relop} {handle("RELOP",yytext);return RELOP;}//left
"+" {handle("PLUS",yytext);return PLUS;}//left
"-" {handle("MINUS",yytext);return MINUS;}//right|left
"*" {handle("STAR",yytext);return STAR;}//left
"/" {handle("DIV",yytext);return DIV;}//left
"&&" {handle("AND",yytext);return AND;}//left
"||" {handle("OR",yytext);return OR;}//left
"." {handle("DOT",yytext);return DOT;}//left
"!" {handle("NOT",yytext);return NOT;}//right
{type} {handle("TYPE",yytext);return TYPE;}
"(" {handle("LP",yytext);return LP;}//left
")" {handle("RP",yytext);return RP;}//left
"[" {handle("LB",yytext);return LB;}//left
"]" {handle("RB",yytext);return RB;}//left
"{" {handle("LC",yytext);return LC;}
"}" {handle("RC",yytext);return RC;}
struct {handle("STRUCT",yytext);return STRUCT;}
return {handle("RETURN",yytext);return RETURN;}
if {handle("IF",yytext);return IF;}
else {handle("ELSE",yytext);return ELSE;}
while {handle("WHILE",yytext);return WHILE;}
{id} {handle("ID",yytext);return ID;}
{int10} {handle("INT",yytext);return INT;}
{int8} {handle("INT8",yytext);return INT;}
{int16} {handle("INT16",yytext);return INT;}
{float} {handle("FLOAT",yytext);return FLOAT;}
{efloat} {handle("FLOAT",yytext);return FLOAT;}
0[xX][0-9a-zA-Z]*  {printf("Error type A at Line %d: Illegal hexadecimal number \'%s\'.\n", yylineno, yytext);error++;return INT;}
0[0-9a-zA-Z]+      {printf("Error type A at Line %d: Illegal octal number \'%s\'.\n", yylineno, yytext);error++;return INT;}
[0-9]*[.]|[.][0-9]* {printf("Error type A at Line %d: Illegal floating number \'%s\'.\n", yylineno, yytext);error++;return FLOAT;}
. {
printf("Error type A at Line %d: Mysterious characters \'%s\'\n",
yylineno, yytext);
error++;
}

%%


// . {
// 	char c = input();
// 	while (c !=NULL)
// 	{
// 		printf("%c",c);
// 		c = input();
// 	}
// }