//
// Created by hby on 22-11-3.
//

#ifndef CODE_IR_H
#define CODE_IR_H

#include <stdbool.h>
#include <object.h>
#include <container/vector.h>
#include <container/list.h>
#include <container/treap.h>
#include <macro.h>
#include <stdio.h>

//// ================================== IR var & label ==================================

typedef unsigned IR_var;   // 数字表示 v1, v2...
typedef unsigned IR_label; // 数字表示 L1, L2...
typedef unsigned IR_DEC_size_t;
enum {IR_VAR_NONE = 0};
enum {IR_LABEL_NONE = 0};

DEF_VECTOR(IR_var)
extern IR_var ir_var_generator();     // 获取新变量编号
extern IR_label ir_label_generator(); // 获取新label编号
extern void ir_func_var_recycle(IR_var var);
extern void ir_label_recycle(IR_label label);

//// ================================== IR ==================================

//// IR_val

typedef struct IR_val {
    bool is_const;
    union {
        IR_var var;
        int const_val;
    };
} IR_val;

//// IR_stmt

typedef enum {
    IR_OP_STMT, IR_ASSIGN_STMT, IR_LOAD_STMT, IR_STORE_STMT, IR_IF_STMT, IR_GOTO_STMT, IR_CALL_STMT, IR_RETURN_STMT, IR_READ_STMT, IR_WRITE_STMT
} IR_stmt_type;

typedef struct IR_stmt IR_stmt, *IR_stmt_ptr;

typedef struct IR_use {
    unsigned use_cnt; // use 个数
    IR_val *use_vec;  // use 数组
}IR_use;

struct IR_stmt_virtualTable {
    void (*teardown) (IR_stmt *stmt);
    void (*print) (IR_stmt *stmt, FILE *out);
    IR_var (*get_def) (IR_stmt *stmt);        // def 最多只有一个, 不存在则返回 IR_VAR_NONE
    IR_use (*get_use_vec) (IR_stmt *stmt);
};

#define CLASS_IR_stmt struct { \
        struct IR_stmt_virtualTable const *vTable; \
        IR_stmt_type stmt_type; \
        bool dead;};

struct IR_stmt {
    CLASS_IR_stmt
};
DEF_LIST(IR_stmt_ptr)
extern void IR_stmt_teardown(IR_stmt *stmt);

//// IR_block

typedef struct {
    IR_label label;
    bool dead;
    List_IR_stmt_ptr stmts;
} IR_block, *IR_block_ptr;
DEF_LIST(IR_block_ptr)
extern void IR_block_init(IR_block *block, IR_label label);
extern void IR_block_teardown(IR_block *block);

//// IR_function

typedef struct {
    IR_var dec_addr;
    IR_DEC_size_t dec_size;
} IR_Dec;
DEF_MAP(IR_var, IR_Dec)

DEF_MAP(IR_label, IR_block_ptr)
typedef List_IR_block_ptr *List_ptr_IR_block_ptr;
DEF_MAP(IR_block_ptr, List_ptr_IR_block_ptr)

typedef struct IR_function{
    char *func_name;
    Vec_IR_var params;
    Map_IR_var_IR_Dec map_dec; // dec_var => (addr_var, size)
    List_IR_block_ptr blocks;
    // Control Flow Graph
    IR_block *entry, *exit;
    Map_IR_label_IR_block_ptr map_blk_label; // Label -> Block 指针
    Map_IR_block_ptr_List_ptr_IR_block_ptr blk_pred, blk_succ; // Block 指针 -> List<前驱后继Block> 的指针
} IR_function, *IR_function_ptr;
DEF_VECTOR(IR_function_ptr)
extern void IR_function_init(IR_function *func, const char *func_name);
extern IR_var IR_function_insert_dec(IR_function *func, IR_var var, IR_DEC_size_t dec_size);
extern void IR_function_build_graph(IR_function *func); // 建图
extern void IR_function_closure(IR_function *func);

//// IR_program

typedef struct IR_program {
    Vec_IR_function_ptr functions;
} IR_program;
typedef struct NodeProgram NodeProgram;
extern IR_program *ir_program_global;
extern void IR_program_init(IR_program *program);
extern void IR_program_teardown(void *ptr);
extern void IR_function_push_stmt(IR_function *func, IR_stmt *stmt);
extern void IR_function_push_label(IR_function *func, IR_label label);

//// ================================== IR print api ==================================

// 输出函数, out可赋为stdout

extern void IR_output(const char *output_IR_path);
extern void IR_block_print(IR_block *block, FILE *out);
extern void IR_function_print(IR_function *func, FILE *out);
extern void IR_program_print(IR_program *program, FILE *out);

//// ================================== Stmt ==================================

typedef enum {
    IR_OP_ADD, IR_OP_SUB, IR_OP_MUL, IR_OP_DIV
} IR_OP_TYPE;
typedef struct {
    CLASS_IR_stmt
    IR_OP_TYPE op;
    IR_var rd;
    union {
        IR_val use_vec[2];
        struct { IR_val rs1, rs2; };
    };
} IR_op_stmt;
extern void IR_op_stmt_init(IR_op_stmt *op_stmt, IR_OP_TYPE op,
                            IR_var rd, IR_val rs1, IR_val rs2);

typedef struct {
    CLASS_IR_stmt
    IR_var rd;
    union {
        IR_val use_vec[1];
        struct { IR_val rs; };
    };
} IR_assign_stmt;
extern void IR_assign_stmt_init(IR_assign_stmt *assign_stmt, IR_var rd, IR_val rs);

typedef struct {
    CLASS_IR_stmt
    IR_var rd;
    union {
        IR_val use_vec[1];
        struct { IR_val rs_addr; };
    };
} IR_load_stmt;
extern void IR_load_stmt_init(IR_load_stmt *load_stmt, IR_var rd, IR_val rs_addr);

typedef struct {
    CLASS_IR_stmt
    union {
        IR_val use_vec[2];
        struct { IR_val rd_addr, rs; };
    };
} IR_store_stmt;
extern void IR_store_stmt_init(IR_store_stmt *store_stmt, IR_val rd_addr, IR_val rs);

typedef enum {
    IR_RELOP_EQ, IR_RELOP_NE, IR_RELOP_GT, IR_RELOP_GE, IR_RELOP_LT, IR_RELOP_LE
} IR_RELOP_TYPE;
typedef struct {
    CLASS_IR_stmt
    IR_RELOP_TYPE relop;
    union {
        IR_val use_vec[2];
        struct { IR_val rs1, rs2; };
    };
    IR_label true_label, false_label;
    IR_block *true_blk, *false_blk;
} IR_if_stmt;
extern void IR_if_stmt_init(IR_if_stmt *if_stmt, IR_RELOP_TYPE relop,
                            IR_val rs1, IR_val rs2,
                            IR_label true_label, IR_label false_label);
extern void IR_if_stmt_flip(IR_if_stmt *if_stmt);

typedef struct {
    CLASS_IR_stmt
    IR_label label;
    IR_block *blk;
} IR_goto_stmt;
extern void IR_goto_stmt_init(IR_goto_stmt *goto_stmt, IR_label label);

typedef struct {
    CLASS_IR_stmt
    union {
        IR_val use_vec[1];
        struct { IR_val rs; };
    };
} IR_return_stmt;
extern void IR_return_stmt_init(IR_return_stmt *return_stmt, IR_val ret_val);

typedef struct {
    CLASS_IR_stmt
    IR_var rd;
    char *func_name;
    unsigned argc;
    IR_val *argv;
} IR_call_stmt;
extern void IR_call_stmt_init(IR_call_stmt *call_stmt, IR_var rd, const char *func_name,
                              unsigned argc, IR_val *argv);

typedef struct {
    CLASS_IR_stmt
    IR_var rd;
} IR_read_stmt;
extern void IR_read_stmt_init(IR_read_stmt *read_stmt, IR_var rd);

typedef struct {
    CLASS_IR_stmt
    union {
        IR_val use_vec[1];
        struct { IR_val rs; };
    };
} IR_write_stmt;
extern void IR_write_stmt_init(IR_write_stmt *write_stmt, IR_val rs);

#endif //CODE_IR_H
