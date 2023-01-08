%define api.prefix {IR_yy}
%define api.token.prefix {IR_TOKEN_}
%define parse.error verbose

%{

#include <macro.h>
#include <object.h>
#include <IR_parse.h>

static void args_stack_push(IR_val arg);
static void args_stack_pop(unsigned *argc_ptr, IR_val **argv_ptr);

static IR_function *now_function = NULL;

%}

%union{
    int INT;
    char *id;
    IR_OP_TYPE IR_op_type;
    IR_RELOP_TYPE IR_relop_type;
    IR_program *IR_program_ptr_node;
    IR_function *IR_function_ptr_node;
    IR_stmt *IR_stmt_ptr_node;
    IR_val IR_val_node;
    IR_label IR_label_node;
    IR_var IR_var_node;
}


/* declare tokens */

%token EOL
%token COLON
%token FUNCTION
%token LABEL
%token SHARP
%token<INT> INT
%token ASSIGN
%token<IR_op_type> STAR
%token<IR_op_type> OP
%token IF
%token<IR_relop_type> RELOP
%token ADDR_OF
%token GOTO
%token RETURN
%token DEC
%token ARG
%token CALL
%token PARAM
%token READ
%token WRITE
%token<id> ID

%type<IR_program_ptr_node> IR_globol
%type<IR_program_ptr_node> IR_program
%type<IR_function_ptr_node> IR_function
%type<IR_stmt_ptr_node> IR_stmt
%type<IR_val_node> IR_val
%type<IR_val_node> val_deref
%type<IR_val_node> IR_val_rs
%type<IR_label_node> IR_label
%type<IR_var_node> IR_var

%%

IR_globol   : MUL_EOL IR_program                        { ir_program_global = $2; }
            ;       
IR_program  : IR_program IR_function                    {
                                                            $$ = $1;
                                                            IR_function_closure($2);
                                                            VCALL($$->functions, push_back, $2);
                                                        }
            |                                           { $$ = NEW(IR_program); }
            ;
IR_function : FUNCTION ID COLON EOL                     { $$ = NEW(IR_function, $2); now_function = $$; free($2); }
            | IR_function PARAM IR_var EOL              { $$ = $1; VCALL($$->params, push_back, $3); }
            | IR_function DEC IR_var INT EOL            { $$ = $1; IR_function_insert_dec($$, $3, (unsigned)$4); }
            | IR_function ARG IR_val_rs EOL             { $$ = $1; args_stack_push($3); }
            | IR_function LABEL IR_label COLON EOL      { $$ = $1; IR_function_push_label($$, $3); }
            | IR_function IR_stmt EOL                   { $$ = $1; IR_function_push_stmt($$, $2); }
            ;
IR_stmt     : IR_var ASSIGN IR_val                      { $$ = (IR_stmt*)NEW(IR_assign_stmt, $1, $3); }
            | IR_var ASSIGN val_deref                   { $$ = (IR_stmt*)NEW(IR_load_stmt, $1, $3); }
            | val_deref ASSIGN IR_val_rs                { $$ = (IR_stmt*)NEW(IR_store_stmt, $1, $3); }
            | IR_var ASSIGN IR_val_rs OP IR_val_rs      { $$ = (IR_stmt*)NEW(IR_op_stmt, $4, $1, $3, $5); }
            | IR_var ASSIGN IR_val_rs STAR IR_val_rs    { $$ = (IR_stmt*)NEW(IR_op_stmt, $4, $1, $3, $5); }
            | GOTO IR_label                             { $$ = (IR_stmt*)NEW(IR_goto_stmt, $2); }
            | IF IR_val_rs RELOP IR_val_rs GOTO IR_label
                                                        { $$ = (IR_stmt*)NEW(IR_if_stmt, $3, $2, $4, $6, IR_LABEL_NONE); }
            | RETURN IR_val                             { $$ = (IR_stmt*)NEW(IR_return_stmt, $2); }
            | IR_var ASSIGN CALL ID                     {
                                                             unsigned argc;
                                                             IR_val *argv;
                                                             args_stack_pop(&argc, &argv);
                                                             $$ = (IR_stmt*)NEW(IR_call_stmt, $1, $4, argc, argv);
                                                             free($4);
                                                        }
            | READ IR_var                               { $$ = (IR_stmt*)NEW(IR_read_stmt, $2); }
            | WRITE IR_val_rs                           { $$ = (IR_stmt*)NEW(IR_write_stmt, $2); }
            ;
IR_val      : IR_var                                    { $$ = (IR_val){.is_const = false, .var = $1}; }
            | SHARP INT                                 { $$ = (IR_val){.is_const = true, .const_val = $2}; }
            | ADDR_OF IR_var                            { $$ = (IR_val){.is_const = false,
                                                                        .var = VCALL(now_function->map_dec, get, $2).dec_addr}; }
            ;
val_deref   : STAR IR_val                               { $$ = $2; }
IR_val_rs   : IR_val                                    { $$ = $1; }
            | val_deref                                 {
                                                            IR_var content = ir_var_generator();
                                                            IR_function_push_stmt(now_function,
                                                                                  (IR_stmt*)NEW(IR_load_stmt, content, $1));
                                                            $$ = (IR_val){.is_const = false, .var = content};
                                                        }
IR_var      : ID                                        { $$ = get_IR_var($1); free($1); }
            ;
IR_label    : ID                                        { $$ = get_IR_label($1); free($1); }
            ;
MUL_EOL     : MUL_EOL EOL
            |
            ;

%%

int IR_yyerror(const char *msg) {
    fprintf(YYERROR_OUTPUT, "IR syntax error: %s\n", msg);
    return 0;
}

//// ================================== args stack ==================================

unsigned args_stack_top = 0;
static IR_val args_stack[16];

static void args_stack_push(IR_val arg) {
    args_stack[args_stack_top ++] = arg;
}

static void args_stack_pop(unsigned *argc_ptr, IR_val **argv_ptr) {
    unsigned argc = args_stack_top;
    IR_val *argv = (IR_val*)malloc(sizeof(IR_val[argc]));
    for(int i = 0; i < argc; i ++)
        argv[i] = args_stack[i];
    *argc_ptr = argc;
    *argv_ptr = argv;
    args_stack_top = 0;
}

