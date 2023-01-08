//
// Created by hby on 22-12-1.
//

#include <IR.h>

static void add_edge(IR_function *ir_func, IR_block *src, IR_block *dst) {
    List_IR_block_ptr *src_succs = VCALL(ir_func->blk_succ, get, src);
    List_IR_block_ptr *dst_preds = VCALL(ir_func->blk_pred, get, dst);
    VCALL(*src_succs, push_back, dst);
    VCALL(*dst_preds, push_back, src);
}

void IR_function_build_graph(IR_function *ir_func) {
    for_list(IR_block_ptr, i, ir_func->blocks) {
        VCALL(ir_func->blk_pred, insert, i->val, NEW(List_IR_block_ptr));
        VCALL(ir_func->blk_succ, insert, i->val, NEW(List_IR_block_ptr));
        if(i->val->label != IR_LABEL_NONE)
            VCALL(ir_func->map_blk_label, insert, i->val->label, i->val);
    }
    for_list(IR_block_ptr, i, ir_func->blocks) {
        if(i->val == ir_func->exit)
            continue;
        if(i->val->stmts.tail == NULL) {
            add_edge(ir_func, i->val, i->nxt->val);
            continue;
        }
        IR_stmt *last_stmt = i->val->stmts.tail->val;
        switch (last_stmt->stmt_type) {
            case IR_IF_STMT: {
                IR_if_stmt *if_stmt = (IR_if_stmt*)last_stmt;
                IR_block *next_blk = i->nxt->val;
                IR_block *true_blk = VCALL(ir_func->map_blk_label, get, if_stmt->true_label);
                IR_block *false_blk = if_stmt->false_label == IR_LABEL_NONE ?
                                      next_blk : VCALL(ir_func->map_blk_label, get, if_stmt->false_label);
                if_stmt->true_blk = true_blk;
                if_stmt->false_blk = false_blk;
                add_edge(ir_func, i->val, true_blk);
                add_edge(ir_func, i->val, false_blk);
                break;
            }
            case IR_GOTO_STMT: {
                IR_goto_stmt *goto_stmt = (IR_goto_stmt*)last_stmt;
                IR_block *blk = VCALL(ir_func->map_blk_label, get, goto_stmt->label);
                goto_stmt->blk = blk;
                add_edge(ir_func, i->val, blk);
                break;
            }
            case IR_RETURN_STMT: {
                add_edge(ir_func, i->val, ir_func->exit);
                break;
            }
            default:
                add_edge(ir_func, i->val, i->nxt->val);
        }
    }
}

