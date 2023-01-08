//
// Created by hby on 22-11-10.
//

#include <IR.h>

//// ==================================== teardown ====================================

static void IR_stmt_teardown_default(IR_stmt *stmt) { }

static void IR_call_stmt_teardown(IR_stmt *stmt) {
    IR_call_stmt *call_stmt = (IR_call_stmt*)stmt;
    free(call_stmt->func_name);
    free(call_stmt->argv);
}

void IR_stmt_teardown(IR_stmt *stmt) {
    if(stmt->stmt_type == IR_CALL_STMT)
        IR_call_stmt_teardown(stmt);
}

//// ==================================== print ====================================

static void IR_val_print(IR_val val, FILE *out) {
    if(val.is_const)
        fprintf(out, "#%d", val.const_val);
    else
        fprintf(out, "v%u", val.var);
}

static void IR_OP_TYPE_print(IR_OP_TYPE ir_op_type, FILE *out) {
    switch (ir_op_type) {
        case IR_OP_ADD: fprintf(out, " + "); break;
        case IR_OP_SUB: fprintf(out, " - "); break;
        case IR_OP_MUL: fprintf(out, " * "); break;
        case IR_OP_DIV: fprintf(out, " / "); break;
        default: assert(0);
    }
}

static void IR_RELOP_TYPE_print(IR_RELOP_TYPE ir_relop_type, FILE *out) {
    switch (ir_relop_type) {
        case IR_RELOP_EQ: fprintf(out, " == "); break;
        case IR_RELOP_NE: fprintf(out, " != "); break;
        case IR_RELOP_LT: fprintf(out, " < "); break;
        case IR_RELOP_GT: fprintf(out, " > "); break;
        case IR_RELOP_LE: fprintf(out, " <= "); break;
        case IR_RELOP_GE: fprintf(out, " >= "); break;
        default: assert(0);
    }
}

static void IR_assign_stmt_print(IR_stmt *stmt, FILE *out) {
    IR_assign_stmt *assign_stmt = (IR_assign_stmt*)stmt;
    fprintf(out, "v%u := ", assign_stmt->rd);
    IR_val_print(assign_stmt->rs, out);
    fprintf(out, "\n");
}

static void IR_op_stmt_print(IR_stmt *stmt, FILE *out) {
    IR_op_stmt *op_stmt = (IR_op_stmt*)stmt;
    fprintf(out, "v%u := ", op_stmt->rd);
    IR_val_print(op_stmt->rs1, out);
    IR_OP_TYPE_print(op_stmt->op, out);
    IR_val_print(op_stmt->rs2, out);
    fprintf(out, "\n");
}

static void IR_load_stmt_print(IR_stmt *stmt, FILE *out) {
    IR_load_stmt *load_stmt = (IR_load_stmt*)stmt;
    fprintf(out, "v%u := *", load_stmt->rd);
    IR_val_print(load_stmt->rs_addr, out);
    fprintf(out, "\n");
}

static void IR_store_stmt_print(IR_stmt *stmt, FILE *out) {
    IR_store_stmt *store_stmt = (IR_store_stmt*)stmt;
    fprintf(out, "*");
    IR_val_print(store_stmt->rd_addr, out);
    fprintf(out, " := ");
    IR_val_print(store_stmt->rs, out);
    fprintf(out, "\n");
}

static void IR_call_stmt_print(IR_stmt *stmt, FILE *out) {
    IR_call_stmt *call_stmt = (IR_call_stmt*)stmt;
    for(unsigned i = call_stmt->argc; i != 0; i --) {
        fprintf(out, "ARG ");
        IR_val_print(call_stmt->argv[i - 1], out);
        fprintf(out, "\n");
    }
    fprintf(out, "v%u := CALL %s\n",
            call_stmt->rd, call_stmt->func_name);
}

static void IR_if_stmt_print(IR_stmt *stmt, FILE *out) {
    IR_if_stmt *if_stmt = (IR_if_stmt*)stmt;
    fprintf(out, "IF ");
    IR_val_print(if_stmt->rs1, out);
    IR_RELOP_TYPE_print(if_stmt->relop, out);
    IR_val_print(if_stmt->rs2, out);
    fprintf(out, " GOTO L%u\n", if_stmt->true_label);
    if(if_stmt->false_label != IR_LABEL_NONE)
        fprintf(out, "GOTO L%u\n", if_stmt->false_label);
}

static void IR_goto_stmt_print(IR_stmt *stmt, FILE *out) {
    IR_goto_stmt *goto_stmt = (IR_goto_stmt*)stmt;
    if(goto_stmt->label != IR_LABEL_NONE)
        fprintf(out, "GOTO L%u\n", goto_stmt->label);
}

static void IR_return_stmt_print(IR_stmt *stmt, FILE *out) {
    IR_return_stmt *return_stmt = (IR_return_stmt*)stmt;
    fprintf(out, "RETURN ");
    IR_val_print(return_stmt->rs, out);
    fprintf(out, "\n");
}

static void IR_read_stmt_print(IR_stmt *stmt, FILE *out) {
    IR_read_stmt *read_stmt = (IR_read_stmt*)stmt;
    fprintf(out, "READ v%u", read_stmt->rd);
    fprintf(out, "\n");
}

static void IR_write_stmt_print(IR_stmt *stmt, FILE *out) {
    IR_write_stmt *write_stmt = (IR_write_stmt*)stmt;
    fprintf(out, "WRITE ");
    IR_val_print(write_stmt->rs, out);
    fprintf(out, "\n");
}

//// ==================================== def & use ====================================

//// def

static IR_var IR_stmt_get_def_none(IR_stmt *stmt) {
    return IR_VAR_NONE;
}

static IR_var IR_assign_stmt_get_def(IR_stmt *stmt) {
    IR_assign_stmt *assign_stmt = (IR_assign_stmt*)stmt;
    return assign_stmt->rd;
}

static IR_var IR_op_stmt_get_def(IR_stmt *stmt) {
    IR_op_stmt *op_stmt = (IR_op_stmt*)stmt;
    return op_stmt->rd;
}

static IR_var IR_load_stmt_get_def(IR_stmt *stmt) {
    IR_load_stmt *load_stmt = (IR_load_stmt*)stmt;
    return load_stmt->rd;
}

static IR_var IR_call_stmt_get_def(IR_stmt *stmt) {
    IR_call_stmt *call_stmt = (IR_call_stmt*)stmt;
    return call_stmt->rd;
}


static IR_var IR_read_stmt_get_def(IR_stmt *stmt) {
    IR_read_stmt *read_stmt = (IR_read_stmt*)stmt;
    return read_stmt->rd;
}

//// use

static IR_use IR_stmt_get_use_none(IR_stmt *stmt) {
    return (IR_use) {.use_cnt = 0,
                     .use_vec = NULL};
}

static IR_use IR_op_stmt_get_use(IR_stmt *stmt) {
    IR_op_stmt *op_stmt = (IR_op_stmt*)stmt;
    return (IR_use) {.use_cnt = 2,
                     .use_vec = op_stmt->use_vec};
}

static IR_use IR_assign_stmt_get_use(IR_stmt *stmt) {
    IR_assign_stmt *assign_stmt = (IR_assign_stmt*)stmt;
    return (IR_use) {.use_cnt = 1,
                     .use_vec = assign_stmt->use_vec};
}

static IR_use IR_load_stmt_get_use(IR_stmt *stmt) {
    IR_load_stmt *load_stmt = (IR_load_stmt*)stmt;
    return (IR_use) {.use_cnt = 1,
                     .use_vec = load_stmt->use_vec};
}

static IR_use IR_store_stmt_get_use(IR_stmt *stmt) {
    IR_store_stmt *store_stmt = (IR_store_stmt*)stmt;
    return (IR_use) {.use_cnt = 2,
                     .use_vec = store_stmt->use_vec};
}

static IR_use IR_if_stmt_get_use(IR_stmt *stmt) {
    IR_if_stmt *if_stmt = (IR_if_stmt*)stmt;
    return (IR_use) {.use_cnt = 2,
                     .use_vec = if_stmt->use_vec};
}

static IR_use IR_return_stmt_get_use(IR_stmt *stmt) {
    IR_return_stmt *return_stmt = (IR_return_stmt*)stmt;
    return (IR_use) {.use_cnt = 1,
                     .use_vec = return_stmt->use_vec};
}

static IR_use IR_call_stmt_get_use(IR_stmt *stmt) {
    IR_call_stmt *call_stmt = (IR_call_stmt*)stmt;
    return (IR_use) {.use_cnt = call_stmt->argc,
                     .use_vec = call_stmt->argv};
}

static IR_use IR_write_stmt_get_use(IR_stmt *stmt) {
    IR_write_stmt *write_stmt = (IR_write_stmt*)stmt;
    return (IR_use) {.use_cnt = 1,
                         .use_vec = write_stmt->use_vec};
}

//// ==================================== init ====================================


void IR_op_stmt_init(IR_op_stmt *op_stmt, IR_OP_TYPE op,
                     IR_var rd, IR_val rs1, IR_val rs2) {
    const static struct IR_stmt_virtualTable vTable = {
            .teardown = IR_stmt_teardown_default,
            .print = IR_op_stmt_print,
            .get_def = IR_op_stmt_get_def,
            .get_use_vec = IR_op_stmt_get_use,
    };
    op_stmt->vTable = &vTable;
    op_stmt->stmt_type = IR_OP_STMT;
    op_stmt->dead = false;
    op_stmt->op = op;
    op_stmt->rd = rd;
    op_stmt->rs1 = rs1;
    op_stmt->rs2 = rs2;
}

void IR_assign_stmt_init(IR_assign_stmt *assign_stmt, IR_var rd, IR_val rs) {
    const static struct IR_stmt_virtualTable vTable = {
            .teardown = IR_stmt_teardown_default,
            .print = IR_assign_stmt_print,
            .get_def = IR_assign_stmt_get_def,
            .get_use_vec = IR_assign_stmt_get_use,
    };
    assign_stmt->vTable = &vTable;
    assign_stmt->stmt_type = IR_ASSIGN_STMT;
    assign_stmt->dead = false;
    assign_stmt->rd = rd;
    assign_stmt->rs = rs;
}

void IR_load_stmt_init(IR_load_stmt *load_stmt, IR_var rd, IR_val rs_addr) {
    const static struct IR_stmt_virtualTable vTable = {
            .teardown = IR_stmt_teardown_default,
            .print = IR_load_stmt_print,
            .get_def = IR_load_stmt_get_def,
            .get_use_vec = IR_load_stmt_get_use,
    };
    load_stmt->vTable = &vTable;
    load_stmt->stmt_type = IR_LOAD_STMT;
    load_stmt->dead = false;
    load_stmt->rd = rd;
    load_stmt->rs_addr = rs_addr;
}

void IR_store_stmt_init(IR_store_stmt *store_stmt, IR_val rd_addr, IR_val rs) {
    const static struct IR_stmt_virtualTable vTable = {
            .teardown = IR_stmt_teardown_default,
            .print = IR_store_stmt_print,
            .get_def = IR_stmt_get_def_none,
            .get_use_vec = IR_store_stmt_get_use,
    };
    store_stmt->vTable = &vTable;
    store_stmt->stmt_type = IR_STORE_STMT;
    store_stmt->dead = false;
    store_stmt->rs = rs;
    store_stmt->rd_addr = rd_addr;
}

void IR_call_stmt_init(IR_call_stmt *call_stmt, IR_var rd, const char *func_name,
                              unsigned argc, IR_val *argv) {
    const static struct IR_stmt_virtualTable vTable = {
            .teardown = IR_call_stmt_teardown,
            .print = IR_call_stmt_print,
            .get_def = IR_call_stmt_get_def,
            .get_use_vec = IR_call_stmt_get_use,
    };
    call_stmt->vTable = &vTable;
    call_stmt->stmt_type = IR_CALL_STMT;
    call_stmt->dead = false;
    call_stmt->rd = rd;
    call_stmt->func_name = strdup(func_name);
    call_stmt->argc = argc;
    call_stmt->argv = argv;
}

void IR_if_stmt_init(IR_if_stmt *if_stmt, IR_RELOP_TYPE relop,
                            IR_val rs1, IR_val rs2,
                            IR_label true_label, IR_label false_label) {
    const static struct IR_stmt_virtualTable vTable = {
            .teardown = IR_stmt_teardown_default,
            .print = IR_if_stmt_print,
            .get_def = IR_stmt_get_def_none,
            .get_use_vec = IR_if_stmt_get_use,
    };
    if_stmt->vTable = &vTable;
    if_stmt->stmt_type = IR_IF_STMT;
    if_stmt->dead = false;
    if_stmt->relop = relop;
    if_stmt->rs1 = rs1;
    if_stmt->rs2 = rs2;
    if_stmt->true_label = true_label;
    if_stmt->false_label = false_label;
    if_stmt->true_blk = if_stmt->false_blk = NULL;
}

void IR_goto_stmt_init(IR_goto_stmt *goto_stmt, IR_label label) {
    const static struct IR_stmt_virtualTable vTable = {
            .teardown = IR_stmt_teardown_default,
            .print = IR_goto_stmt_print,
            .get_def = IR_stmt_get_def_none,
            .get_use_vec = IR_stmt_get_use_none,
    };
    goto_stmt->vTable = &vTable;
    goto_stmt->stmt_type = IR_GOTO_STMT;
    goto_stmt->dead = false;
    goto_stmt->label = label;
    goto_stmt->blk = NULL;
}

void IR_return_stmt_init(IR_return_stmt *return_stmt, IR_val ret_val) {
    const static struct IR_stmt_virtualTable vTable = {
            .teardown = IR_stmt_teardown_default,
            .print = IR_return_stmt_print,
            .get_def = IR_stmt_get_def_none,
            .get_use_vec = IR_return_stmt_get_use,
    };
    return_stmt->vTable = &vTable;
    return_stmt->stmt_type = IR_RETURN_STMT;
    return_stmt->dead = false;
    return_stmt->rs = ret_val;
}

void IR_read_stmt_init(IR_read_stmt *read_stmt, IR_var rd) {
    const static struct IR_stmt_virtualTable vTable = {
            .teardown = IR_stmt_teardown_default,
            .print = IR_read_stmt_print,
            .get_def = IR_read_stmt_get_def,
            .get_use_vec = IR_stmt_get_use_none,
    };
    read_stmt->vTable = &vTable;
    read_stmt->stmt_type = IR_READ_STMT;
    read_stmt->dead = false;
    read_stmt->rd = rd;
}

void IR_write_stmt_init(IR_write_stmt *write_stmt, IR_val rs) {
    const static struct IR_stmt_virtualTable vTable = {
            .teardown = IR_stmt_teardown_default,
            .print = IR_write_stmt_print,
            .get_def = IR_stmt_get_def_none,
            .get_use_vec = IR_write_stmt_get_use,
    };
    write_stmt->vTable = &vTable;
    write_stmt->stmt_type = IR_WRITE_STMT;
    write_stmt->dead = false;
    write_stmt->rs = rs;
}