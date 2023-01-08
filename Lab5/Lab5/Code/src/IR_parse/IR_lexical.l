%option noyywrap
%option prefix="IR_yy"

%{

#include <stdbool.h>
#include <string.h>
#include <IR_parse.h>
#include <IR_syntax.tab.h>

#define IR_LEXICAL_ERROR(fmt, ...) \
        fprintf(YYERROR_OUTPUT, "IR lexical error: " fmt "\n", ##__VA_ARGS__)

%}

%%

":"                     { return IR_TOKEN_COLON; }
"FUNCTION"              { return IR_TOKEN_FUNCTION; }
"LABEL"                 { return IR_TOKEN_LABEL; }
"#"                     { return IR_TOKEN_SHARP; }
-?[0-9]+                {
                            char *endptr;
                            int val = strtol(yytext, &endptr, 0);
                            if(endptr != yytext + strlen(yytext)) {
                                IR_LEXICAL_ERROR("Illegal integer '%s'.", yytext);
                            }
                            IR_yylval.INT = val;
                            return IR_TOKEN_INT;
                        }
":="                    { return IR_TOKEN_ASSIGN; }
"+"                     { IR_yylval.IR_op_type = IR_OP_ADD;  return IR_TOKEN_OP; }
"-"                     { IR_yylval.IR_op_type = IR_OP_SUB;  return IR_TOKEN_OP; }
"*"                     { IR_yylval.IR_op_type = IR_OP_MUL;  return IR_TOKEN_STAR; }
"/"                     { IR_yylval.IR_op_type = IR_OP_DIV;  return IR_TOKEN_OP; }
"=="                    { IR_yylval.IR_relop_type = IR_RELOP_EQ;  return IR_TOKEN_RELOP; }
"!="                    { IR_yylval.IR_relop_type = IR_RELOP_NE;  return IR_TOKEN_RELOP; }
">"                     { IR_yylval.IR_relop_type = IR_RELOP_GT;  return IR_TOKEN_RELOP; }
">="                    { IR_yylval.IR_relop_type = IR_RELOP_GE;  return IR_TOKEN_RELOP; }
"<"                     { IR_yylval.IR_relop_type = IR_RELOP_LT;  return IR_TOKEN_RELOP; }
"<="                    { IR_yylval.IR_relop_type = IR_RELOP_LE;  return IR_TOKEN_RELOP; }
"&"                     { return IR_TOKEN_ADDR_OF; }
"IF"                    { return IR_TOKEN_IF; }
"GOTO"                  { return IR_TOKEN_GOTO; }
"RETURN"                { return IR_TOKEN_RETURN; }
"DEC"                   { return IR_TOKEN_DEC; }
"ARG"                   { return IR_TOKEN_ARG; }
"CALL"                  { return IR_TOKEN_CALL; }
"PARAM"                 { return IR_TOKEN_PARAM; }
"READ"                  { return IR_TOKEN_READ; }
"WRITE"                 { return IR_TOKEN_WRITE; }
[a-zA-Z_][a-zA-Z0-9_]*  {
                            IR_yylval.id = strdup(yytext);
                            return IR_TOKEN_ID;
                        }

[ \t]                   /* ignored */
\n+                     { return IR_TOKEN_EOL; }

.	                    { IR_LEXICAL_ERROR("Mysterious token \"%s\".", yytext); }

%%

