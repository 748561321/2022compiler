//
// Created by hby on 22-12-2.
//

#include <IR_optimize.h>
#include <live_variable_analysis.h>
#include <constant_propagation.h>
#include <available_expressions_analysis.h>
#include <copy_propagation.h>

void remove_dead_block(IR_function *func) {
    // remove
    for(ListNode_IR_block_ptr *i = func->blocks.head; i;) {
        IR_block *blk = i->val;
        if(blk->dead) { // remove dead block
            RDELETE(IR_block, blk); // IR_block_teardown(blk); free(blk);
            i = VCALL(func->blocks, delete, i);
        } else i = i->nxt;
    }
}

void remove_dead_stmt(IR_block *blk) {
    for(ListNode_IR_stmt_ptr *j = blk->stmts.head; j;) {
        IR_stmt *stmt = j->val;
        if(stmt->dead) { // remove dead stmt
            RDELETE(IR_stmt, stmt); // IR_stmt_teardown(stmt); free(stmt);
            j = VCALL(blk->stmts, delete, j);
            continue;
        } else j = j->nxt;
    }
}


void IR_optimize() {
    ConstantPropagation *constantPropagation;
    AvailableExpressionsAnalysis *availableExpressionsAnalysis;
    CopyPropagation *copyPropagation;
    LiveVariableAnalysis *liveVariableAnalysis;
    for_vec(IR_function_ptr, i, ir_program_global->functions) {
        IR_function *func = *i;

        //// 全局公共表达式消除, 可替换为局部
        {
            //// Constant Propagation

            constantPropagation = NEW(ConstantPropagation);
            worklist_solver((DataflowAnalysis*)constantPropagation, func);
            // VCALL(*constantPropagation, printResult, func);
            ConstantPropagation_constant_folding(constantPropagation, func);
            DELETE(constantPropagation);

            //// Available Expressions Analysis

            availableExpressionsAnalysis = NEW(AvailableExpressionsAnalysis);
            AvailableExpressionsAnalysis_merge_common_expr(availableExpressionsAnalysis, func);
            worklist_solver((DataflowAnalysis*)availableExpressionsAnalysis, func); // 将子类强制转化为父类
            // VCALL(*availableExpressionsAnalysis, printResult, func);
            AvailableExpressionsAnalysis_remove_available_expr_def(availableExpressionsAnalysis, func);
            DELETE(availableExpressionsAnalysis);

            //// Copy Propagation

            copyPropagation = NEW(CopyPropagation);
            worklist_solver((DataflowAnalysis*)copyPropagation, func);
            // VCALL(*copyPropagation, printResult, func);
            CopyPropagation_replace_available_use_copy(copyPropagation, func);
            DELETE(copyPropagation);
        }
        

        //// Constant Propagation (2nd)

        constantPropagation = NEW(ConstantPropagation);
        worklist_solver((DataflowAnalysis*)constantPropagation, func);
        // VCALL(*constantPropagation, printResult, func);
        ConstantPropagation_constant_folding(constantPropagation, func);
        DELETE(constantPropagation);

        //// Live Variable Analysis

        while(true) {
            liveVariableAnalysis = NEW(LiveVariableAnalysis);
            worklist_solver((DataflowAnalysis*)liveVariableAnalysis, func); // 将子类强制转化为父类
            // VCALL(*liveVariableAnalysis, printResult, func);
            bool updated = LiveVariableAnalysis_remove_dead_def(liveVariableAnalysis, func);
            DELETE(liveVariableAnalysis);
            if(!updated) break;
        }

    }
}
