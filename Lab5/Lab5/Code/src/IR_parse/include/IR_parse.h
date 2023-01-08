//
// Created by hby on 22-11-24.
//

#ifndef CODE_IR_PARSE_H
#define CODE_IR_PARSE_H

#include <stdbool.h>
#include <stdio.h>
#include <config.h>
#include <IR.h>


extern void IR_yyrestart ( FILE *input_file );
extern int IR_yylex();
extern int IR_yyparse();
extern int IR_yyerror(const char *msg);

extern void IR_parse(const char *input_IR_path);

extern IR_var get_IR_var(const char *id);
extern IR_label get_IR_label(const char *id);

#endif //CODE_IR_PARSE_H
