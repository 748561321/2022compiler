//
// Created by hby on 22-11-2.
//

#include <IR.h>

IR_program *ir_program_global = NULL;

//// ==============================================================================================================



void IR_block_init(IR_block *block, IR_label label) {
    block->label = label;
    block->dead = false;
    List_IR_stmt_ptr_init(&block->stmts);
}

void IR_block_teardown(IR_block *block) {
    for_list(IR_stmt_ptr, i, block->stmts)
        RDELETE(IR_stmt, i->val);
    List_IR_stmt_ptr_teardown(&block->stmts);
}

void IR_function_init(IR_function *func, const char *func_name) {
    func->func_name = strdup(func_name);
    Vec_IR_var_init(&func->params);
    Map_IR_var_IR_Dec_init(&func->map_dec);
    List_IR_block_ptr_init(&func->blocks);
    IR_block *first_blk = NEW(IR_block, IR_LABEL_NONE);
    VCALL(func->blocks, push_back, first_blk);
    func->entry = func->exit = NULL;
    Map_IR_label_IR_block_ptr_init(&func->map_blk_label);
    Map_IR_block_ptr_List_ptr_IR_block_ptr_init(&func->blk_pred);
    Map_IR_block_ptr_List_ptr_IR_block_ptr_init(&func->blk_succ);
}

IR_var IR_function_insert_dec(IR_function *func, IR_var var, IR_DEC_size_t dec_size) {
    IR_var addr = ir_var_generator();
    VCALL(func->map_dec, insert,
          var, (IR_Dec){.dec_addr = addr, .dec_size = dec_size});
    return addr;
}

void IR_function_closure(IR_function *func) {
    if(func->blocks.tail->val->label == IR_LABEL_NONE &&
       func->blocks.tail->val->stmts.head == NULL) {
        RDELETE(IR_block, func->blocks.tail->val);
        VCALL(func->blocks, pop_back);
    }
    IR_block *entry = NEW(IR_block, IR_LABEL_NONE);
    IR_block *exit = NEW(IR_block, IR_LABEL_NONE);
    func->entry = entry;
    func->exit = exit;
    VCALL(func->blocks, push_front, entry);
    VCALL(func->blocks, push_back, exit);
    IR_function_build_graph(func);
}

static void IR_function_teardown(IR_function *func) {
    for_list(IR_block_ptr, i, func->blocks)
        RDELETE(IR_block, i->val);
    for_map(IR_block_ptr, List_ptr_IR_block_ptr, i, func->blk_pred)
        DELETE(i->val);
    for_map(IR_block_ptr, List_ptr_IR_block_ptr, i, func->blk_succ)
        DELETE(i->val);
    Map_IR_label_IR_block_ptr_teardown(&func->map_blk_label);
    Map_IR_block_ptr_List_ptr_IR_block_ptr_teardown(&func->blk_pred);
    Map_IR_block_ptr_List_ptr_IR_block_ptr_teardown(&func->blk_succ);
    List_IR_block_ptr_teardown(&func->blocks);
    Vec_IR_var_teardown(&func->params);
    Map_IR_var_IR_Dec_teardown(&func->map_dec);
    free(func->func_name);
}

void IR_program_init(IR_program *program) {
    Vec_IR_function_ptr_init(&program->functions);
}

void IR_program_teardown(void *ptr) {
    IR_program *program = ptr;
    for_vec(IR_function *, func_ptr_ptr, program->functions)
        RDELETE(IR_function, *func_ptr_ptr);
    Vec_IR_function_ptr_teardown(&program->functions);
}

void IR_output(const char *output_IR_path) {
    assert(ir_program_global != NULL);
    FILE *ir_file = stdout;
    if(output_IR_path) {
        ir_file = fopen(output_IR_path, "w");
        if(!ir_file) {
            perror(output_IR_path);
            exit(1);
        }
    }
    IR_program_print(ir_program_global, ir_file);
    if(ir_file != stdout)
        fclose(ir_file);
}