//
// Created by hby on 22-12-2.
//

#include <IR.h>

//// ==============================================================================================================

void IR_function_push_stmt(IR_function *ir_func, IR_stmt *stmt) {
    IR_block *last_blk = ir_func->blocks.tail->val;
    if(last_blk->stmts.tail != NULL) {
        IR_stmt *last_stmt = last_blk->stmts.tail->val;
        if(last_stmt->stmt_type == IR_GOTO_STMT ||
                last_stmt->stmt_type == IR_IF_STMT ||
                last_stmt->stmt_type == IR_RETURN_STMT) { // jump related
            if(stmt->stmt_type == IR_GOTO_STMT && last_stmt->stmt_type == IR_IF_STMT) {
                IR_goto_stmt *this_goto_stmt = (IR_goto_stmt*)stmt;
                IR_if_stmt *last_if_stmt = (IR_if_stmt*)last_stmt;
                if(last_if_stmt->false_label == IR_LABEL_NONE) { // if_stmt_false_goto
                    last_if_stmt->false_label = this_goto_stmt->label;
                    RDELETE(IR_stmt, stmt);
                    return;
                }
            }
            // New block
            last_blk = NEW(IR_block, IR_LABEL_NONE);
            VCALL(ir_func->blocks, push_back, last_blk);
        }
    }
    VCALL(last_blk->stmts, push_back, stmt);
}

static inline IR_RELOP_TYPE IR_RELOP_NEG(IR_RELOP_TYPE relop) {
    switch (relop) {
        case IR_RELOP_EQ: return IR_RELOP_NE;
        case IR_RELOP_NE: return IR_RELOP_EQ;
        case IR_RELOP_LT: return IR_RELOP_GE;
        case IR_RELOP_GT: return IR_RELOP_LE;
        case IR_RELOP_LE: return IR_RELOP_GT;
        case IR_RELOP_GE: return IR_RELOP_LT;
        default: assert(0);
    }
}

void IR_if_stmt_flip(IR_if_stmt *if_stmt) {
    if_stmt->relop = IR_RELOP_NEG(if_stmt->relop);
    IR_label t = if_stmt->true_label;
    if_stmt->true_label = if_stmt->false_label;
    if_stmt->false_label = t;
    IR_block *b = if_stmt->true_blk;
    if_stmt->true_blk = if_stmt->false_blk;
    if_stmt->false_blk = b;
}

static void IR_block_strip_goto_stmt(IR_block *blk, IR_label label) {
    while(true) {
        if (blk->stmts.tail == NULL) break;
        IR_stmt *last_stmt = blk->stmts.tail->val;
        if (last_stmt->stmt_type == IR_GOTO_STMT) {
            IR_goto_stmt *goto_stmt = (IR_goto_stmt *) last_stmt;
            if (goto_stmt->label == label) {
                RDELETE(IR_stmt, last_stmt);
                List_IR_stmt_ptr_pop_back(&blk->stmts);
                continue;
            }
        } else if (last_stmt->stmt_type == IR_IF_STMT) {
            IR_if_stmt *if_stmt = (IR_if_stmt *) last_stmt;
            if (if_stmt->true_label == label)
                IR_if_stmt_flip(if_stmt);
            if (if_stmt->false_label == label)
                if_stmt->false_label = IR_LABEL_NONE;
        }
        break;
    }
}

void IR_function_push_label(IR_function *ir_func, IR_label label) {
    IR_block *last_blk = ir_func->blocks.tail->val;
    IR_block_strip_goto_stmt(last_blk, label);
    IR_block *new_blk = NEW(IR_block, label);
    VCALL(ir_func->blocks, push_back, new_blk);
}
