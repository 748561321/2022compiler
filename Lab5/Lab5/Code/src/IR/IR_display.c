//
// Created by hby on 22-11-8.
//

#include <IR.h>
#include <stdio.h>

//// =============================== IR print ===============================

void IR_block_print(IR_block *block, FILE *out) {
    if(block->label != IR_LABEL_NONE)
        fprintf(out, "LABEL L%u :\n", block->label);
    for_list(IR_stmt_ptr, i, block->stmts)
        VCALL(*i->val, print, out);
}

void IR_function_print(IR_function *func, FILE *out) {
    fprintf(out, "FUNCTION %s :\n", func->func_name);
    for_vec(IR_var, var, func->params)
        fprintf(out, "PARAM v%u\n", *var);
    for_map(IR_var, IR_Dec, it, func->map_dec) {
        fprintf(out, "DEC v%u %u\n", it->key, it->val.dec_size);
        fprintf(out, "v%u := &v%u\n", it->val.dec_addr, it->key);
    }
    for_list(IR_block_ptr, i, func->blocks)
        IR_block_print(i->val, out);
    fprintf(out, "\n");
}

void IR_program_print(IR_program *program, FILE *out) {
    for_vec(IR_function *, func_ptr_ptr, program->functions) {
        IR_function *func = *func_ptr_ptr;
        IR_function_print(func, out);
    }
}
