//
// Created by hby on 22-12-2.
//

#include <live_variable_analysis.h>

//// ============================ Dataflow Analysis ============================

static void LiveVariableAnalysis_teardown(LiveVariableAnalysis *t) {
    for_map(IR_block_ptr, Set_ptr_IR_var, i, t->mapInFact)
        DELETE(i->val);
    for_map(IR_block_ptr, Set_ptr_IR_var, i, t->mapOutFact)
        DELETE(i->val);
    Map_IR_block_ptr_Set_ptr_IR_var_teardown(&t->mapInFact);
    Map_IR_block_ptr_Set_ptr_IR_var_teardown(&t->mapOutFact);
}

static bool
LiveVariableAnalysis_isForward (LiveVariableAnalysis *t) {
    // TODO: return isForward?;
    //TODO();
    return false;
}

static Set_IR_var*
LiveVariableAnalysis_newBoundaryFact (LiveVariableAnalysis *t, IR_function *func) {
    return NEW(Set_IR_var);
}

static Set_IR_var*
LiveVariableAnalysis_newInitialFact (LiveVariableAnalysis *t) {
    return NEW(Set_IR_var); // May Analysis => Bottom
}

static void
LiveVariableAnalysis_setInFact (LiveVariableAnalysis *t,
                                IR_block *blk,
                                Set_IR_var *fact) {
    VCALL(t->mapInFact, set, blk, fact);
}

static void
LiveVariableAnalysis_setOutFact (LiveVariableAnalysis *t,
                                 IR_block *blk,
                                 Set_IR_var *fact) {
    VCALL(t->mapOutFact, set, blk, fact);
}

static Set_IR_var*
LiveVariableAnalysis_getInFact (LiveVariableAnalysis *t, IR_block *blk) {
    return VCALL(t->mapInFact, get, blk);
}

static Set_IR_var*
LiveVariableAnalysis_getOutFact (LiveVariableAnalysis *t, IR_block *blk) {
    return VCALL(t->mapOutFact, get, blk);
}

static bool
LiveVariableAnalysis_meetInto (LiveVariableAnalysis *t,
                               Set_IR_var *fact,
                               Set_IR_var *target) {
    /* TODO:
     * meet: union/intersect?
     * return VCALL(*target, union_with/intersect_with?, fact);
     */
   // TODO();
    return VCALL(*target, union_with, fact);
}

void LiveVariableAnalysis_transferStmt (LiveVariableAnalysis *t,
                                        IR_stmt *stmt,
                                        Set_IR_var *fact) {
    IR_var def = VCALL(*stmt, get_def);
    IR_use use = VCALL(*stmt, get_use_vec);
    /* TODO:
     * kill/gen?
     * 先执行kill还是先执行gen?
     * use:
     *  for(unsigned i = 0; i < use.use_cnt; i ++) {
     *      IR_val use_val = use.use_vec[i];
     *      if(!use_val.is_const) {
     *          IR_var use = use_val.var;
     *          VCALL(*fact, insert/delete?, use); // kill/gen ?
     *      }     
     *  }
     * def:
     *  if(def != IR_VAR_NONE) { // 生成新def
     *      VCALL(*fact, insert/delete?, def); // kill/gen ?
     *  }
     */
    //TODO();
    //先kill
    if(def != IR_VAR_NONE) { // 生成新def
           VCALL(*fact, delete, def); // kill
    }
    for(unsigned i = 0; i < use.use_cnt; i ++) 
    {
        IR_val use_val = use.use_vec[i];
        if(!use_val.is_const) {
            IR_var use = use_val.var;
            VCALL(*fact, insert, use); // gen 
        }  
    }
}

bool LiveVariableAnalysis_transferBlock (LiveVariableAnalysis *t,
                                         IR_block *block,
                                         Set_IR_var *in_fact,
                                         Set_IR_var *out_fact) {
    Set_IR_var *new_in_fact = LiveVariableAnalysis_newInitialFact(t);
    LiveVariableAnalysis_meetInto(t, out_fact, new_in_fact);
    rfor_list(IR_stmt_ptr, i, block->stmts) { // 倒序遍历
        IR_stmt *stmt = i->val;
        LiveVariableAnalysis_transferStmt(t, stmt, new_in_fact);
    }
    bool updated = LiveVariableAnalysis_meetInto(t, new_in_fact, in_fact);
    DELETE(new_in_fact);
    return updated;
}

void LiveVariableAnalysis_print_result(LiveVariableAnalysis *t, IR_function *func) {
    printf("Function %s: Live Variable Analysis Result\n", func->func_name);
    for_list(IR_block_ptr, i, func->blocks) {
        IR_block *blk = i->val;
        printf("=================\n");
        printf("{Block%s %p}\n", blk == func->entry ? "(Entry)" :
                                      blk == func->exit ? "(Exit)" : "",
                                      blk);
        IR_block_print(blk, stdout);
        Set_IR_var *in_fact = VCALL(*t, getInFact, blk),
                *out_fact = VCALL(*t, getOutFact, blk);
        printf("[In]:  ");
        for_set(IR_var, var, *in_fact)
            printf("v%u ", var->key);
        printf("\n");
        printf("[Out]: ");
        for_set(IR_var, var, *out_fact)
            printf("v%u ", var->key);
        printf("\n");
        printf("=================\n");
    }
}

void LiveVariableAnalysis_init(LiveVariableAnalysis *t) {
    const static struct LiveVariableAnalysis_virtualTable vTable = {
            .teardown        = LiveVariableAnalysis_teardown,
            .isForward       = LiveVariableAnalysis_isForward,
            .newBoundaryFact = LiveVariableAnalysis_newBoundaryFact,
            .newInitialFact  = LiveVariableAnalysis_newInitialFact,
            .setInFact       = LiveVariableAnalysis_setInFact,
            .setOutFact      = LiveVariableAnalysis_setOutFact,
            .getInFact       = LiveVariableAnalysis_getInFact,
            .getOutFact      = LiveVariableAnalysis_getOutFact,
            .meetInto        = LiveVariableAnalysis_meetInto,
            .transferBlock   = LiveVariableAnalysis_transferBlock,
            .printResult     = LiveVariableAnalysis_print_result
    };
    t->vTable = &vTable;
    Map_IR_block_ptr_Set_ptr_IR_var_init(&t->mapInFact);
    Map_IR_block_ptr_Set_ptr_IR_var_init(&t->mapOutFact);
}

//// ============================ Optimize ============================

static bool block_remove_dead_def (LiveVariableAnalysis *t, IR_block *blk) {
    bool updated = false;
    Set_IR_var *blk_out_fact = VCALL(*t, getOutFact, blk);
    Set_IR_var *new_out_fact = LiveVariableAnalysis_newInitialFact(t);
    LiveVariableAnalysis_meetInto(t, blk_out_fact, new_out_fact);
    rfor_list(IR_stmt_ptr, i, blk->stmts) {
        IR_stmt *stmt = i->val;
        if(stmt->stmt_type == IR_OP_STMT || stmt->stmt_type == IR_ASSIGN_STMT) {
            IR_var def = VCALL(*stmt, get_def);
            if(def == IR_VAR_NONE) continue;
            /* TODO:
             * def具有什么性质可以被标记为死代码?
             * if(VCALL(*new_out_fact, exist, def) == true/false?) {
             *      stmt->dead = true;
             *      updated = true;
             *  }
             */
            //TODO();
            if(VCALL(*new_out_fact, exist, def) == false) {
                stmt->dead = true;
                updated = true;
            }
        }
        LiveVariableAnalysis_transferStmt(t, stmt, new_out_fact);
    }
    DELETE(new_out_fact);
    remove_dead_stmt(blk); // 删除标记为 dead 的变量赋值, 完成死代码消除工作
    return updated;
}

bool LiveVariableAnalysis_remove_dead_def (LiveVariableAnalysis *t, IR_function *func) {
    bool updated = false;
    for_list(IR_block_ptr, j, func->blocks) {
        IR_block *blk = j->val;
        updated |= block_remove_dead_def(t, blk);
    }
    return updated;
}
