//
// Created by hby on 22-12-3.
//

#include <available_expressions_analysis.h>

static int IR_val_CMP(IR_val a, IR_val b) {
    if(a.is_const != b.is_const)
        return a.is_const < b.is_const;
    if(a.is_const)
        return a.const_val == b.const_val ? -1 : a.const_val < b.const_val;
    else
        return a.var == b.var ? -1 : a.var < b.var;
}

int Expr_CMP(Expr a, Expr b) {
    if(a.op != b.op)
        return a.op < b.op;
    int rs1_cmp = IR_val_CMP(a.rs1, b.rs1);
    if(rs1_cmp != -1)
        return rs1_cmp;
    int rs2_cmp = IR_val_CMP(a.rs2, b.rs2);
    return rs2_cmp;
}

void Fact_set_var_init(Fact_set_var *fact, bool is_top) {
    fact->is_top = is_top;
    Set_IR_var_init(&fact->set);
}

void Fact_set_var_teardown(Fact_set_var *fact) {
    Set_IR_var_teardown(&fact->set);
}

//// ============================ Dataflow Analysis ============================

static void AvailableExpressionsAnalysis_teardown(AvailableExpressionsAnalysis *t) {
    for_map(IR_block_ptr, Fact_set_var_ptr, i, t->mapInFact)
        RDELETE(Fact_set_var, i->val);
    for_map(IR_block_ptr, Fact_set_var_ptr, i, t->mapOutFact)
        RDELETE(Fact_set_var, i->val);
    for_map(IR_var, Vec_ptr_IR_var, i, t->mapExprKill)
        DELETE(i->val);
    Map_Expr_IR_var_teardown(&t->mapExpr);
    Map_IR_var_Vec_ptr_IR_var_teardown(&t->mapExprKill);
    Map_IR_block_ptr_Fact_set_var_ptr_teardown(&t->mapInFact);
    Map_IR_block_ptr_Fact_set_var_ptr_teardown(&t->mapOutFact);
}

static bool
AvailableExpressionsAnalysis_isForward (AvailableExpressionsAnalysis *t) {
    return true; // Forward Analysis
}

static Fact_set_var*
AvailableExpressionsAnalysis_newBoundaryFact (AvailableExpressionsAnalysis *t, IR_function *func) {
    /* TODO:
     * OutFact[Entry] = (Bottom: empty set) / (Top: universal set) / other?
     * return NEW(Fact_set_var, is_top?);
     */
    //TODO();
    return NEW(Fact_set_var, false);
}

static Fact_set_var*
AvailableExpressionsAnalysis_newInitialFact (AvailableExpressionsAnalysis *t) {
    /* TODO:
     * Must/May Analysis ?
     * InitFact = (Bottom: empty set) / (Top: universal set) / other?
     * return NEW(Fact_set_var, is_top?);
     */
    //TODO();
    return NEW(Fact_set_var, true);
}

static void
AvailableExpressionsAnalysis_setInFact (AvailableExpressionsAnalysis *t,
                                        IR_block *blk,
                                        Fact_set_var *fact) {
    VCALL(t->mapInFact, set, blk, fact);
}

static void
AvailableExpressionsAnalysis_setOutFact (AvailableExpressionsAnalysis *t,
                                         IR_block *blk,
                                         Fact_set_var *fact) {
    VCALL(t->mapOutFact, set, blk, fact);
}

static Fact_set_var*
AvailableExpressionsAnalysis_getInFact (AvailableExpressionsAnalysis *t, IR_block *blk) {
    return VCALL(t->mapInFact, get, blk);
}

static Fact_set_var*
AvailableExpressionsAnalysis_getOutFact (AvailableExpressionsAnalysis *t, IR_block *blk) {
    return VCALL(t->mapOutFact, get, blk);
}

static bool
AvailableExpressionsAnalysis_meetInto (AvailableExpressionsAnalysis *t,
                                       Fact_set_var *fact,
                                       Fact_set_var *target) {
    if(fact->is_top) return false;
    if(target->is_top) {
        // TOP => universal set
        // target->set初始为空集, 清除is_top标记, 直接取union表示赋值
        target->is_top = false;
        VCALL(target->set, union_with, &fact->set);
        return true;
    }
    /* TODO:
     * Must/May Analysis ?
     * IN[blk] = union_with / intersect_with (all OUT[pred_blk]) ?
     * return VCALL(target->set, union_with / intersect_with, &fact->set);
     */
    //TODO();
    return VCALL(target->set, intersect_with, &fact->set);
}

void AvailableExpressionsAnalysis_transferStmt (AvailableExpressionsAnalysis *t,
                                                IR_stmt *stmt,
                                                Fact_set_var *fact) {
    IR_var def = VCALL(*stmt, get_def);
    // e_kill: kill new_def oprand in the expr
    if(def != IR_VAR_NONE && VCALL(t->mapExprKill, exist, def)) {
        Vec_IR_var *killed_expr_var = VCALL(t->mapExprKill, get, def);
        for_vec(IR_var, i, *killed_expr_var)
            VCALL(fact->set, delete, *i);
    }
    // e_gen
    if(stmt->stmt_type == IR_OP_STMT) {
        IR_op_stmt *op_stmt = (IR_op_stmt*)stmt;
        VCALL(fact->set, insert, op_stmt->rd);
    }
}

bool AvailableExpressionsAnalysis_transferBlock (AvailableExpressionsAnalysis *t,
                                                IR_block *block,
                                                Fact_set_var *in_fact,
                                                Fact_set_var *out_fact) {
    Fact_set_var *new_out_fact = AvailableExpressionsAnalysis_newInitialFact(t);
    AvailableExpressionsAnalysis_meetInto(t, in_fact, new_out_fact);
    for_list(IR_stmt_ptr, i, block->stmts) {
        IR_stmt *stmt = i->val;
        AvailableExpressionsAnalysis_transferStmt(t, stmt, new_out_fact);
    }
    bool updated = AvailableExpressionsAnalysis_meetInto(t, new_out_fact, out_fact);
    RDELETE(Fact_set_var, new_out_fact);
    return updated;
}

void AvailableExpressionsAnalysis_print_result (AvailableExpressionsAnalysis *t, IR_function *func) {
    printf("Function %s: Available Expressions Analysis Result\n", func->func_name);
    for_list(IR_block_ptr, i, func->blocks) {
        IR_block *blk = i->val;
        printf("=================\n");
        printf("{Block%s %p}\n", blk == func->entry ? "(Entry)" :
                                 blk == func->exit ? "(Exit)" : "",
               blk);
        IR_block_print(blk, stdout);
        Fact_set_var *in_fact = VCALL(*t, getInFact, blk),
                     *out_fact = VCALL(*t, getOutFact, blk);
        printf("[In(top:%d)]:  ", in_fact->is_top);
        for_set(IR_var, var, in_fact->set)
            printf("v%u ", var->key);
        printf("\n");
        printf("[Out(top:%d)]: ", out_fact->is_top);
        for_set(IR_var, var, out_fact->set)
            printf("v%u ", var->key);
        printf("\n");
        printf("=================\n");
    }
}

void AvailableExpressionsAnalysis_init(AvailableExpressionsAnalysis *t) {
    const static struct AvailableExpressionsAnalysis_virtualTable vTable = {
            .teardown        = AvailableExpressionsAnalysis_teardown,
            .isForward       = AvailableExpressionsAnalysis_isForward,
            .newBoundaryFact = AvailableExpressionsAnalysis_newBoundaryFact,
            .newInitialFact  = AvailableExpressionsAnalysis_newInitialFact,
            .setInFact       = AvailableExpressionsAnalysis_setInFact,
            .setOutFact      = AvailableExpressionsAnalysis_setOutFact,
            .getInFact       = AvailableExpressionsAnalysis_getInFact,
            .getOutFact      = AvailableExpressionsAnalysis_getOutFact,
            .meetInto        = AvailableExpressionsAnalysis_meetInto,
            .transferBlock   = AvailableExpressionsAnalysis_transferBlock,
            .printResult     = AvailableExpressionsAnalysis_print_result
    };
    t->vTable = &vTable;
    Map_Expr_IR_var_init(&t->mapExpr);
    Map_IR_var_Vec_ptr_IR_var_init(&t->mapExprKill);
    Map_IR_block_ptr_Fact_set_var_ptr_init(&t->mapInFact);
    Map_IR_block_ptr_Fact_set_var_ptr_init(&t->mapOutFact);
}

//// ============================ Optimize ============================

static void map_expr_kill_insert(AvailableExpressionsAnalysis *t,
                              IR_var use_var,
                              IR_var expr_var) {
    Vec_IR_var *vec_e_kill;
    if(!VCALL(t->mapExprKill, exist, use_var)) {
        vec_e_kill = NEW(Vec_IR_var);
        VCALL(t->mapExprKill, insert, use_var, vec_e_kill);
    } else vec_e_kill = VCALL(t->mapExprKill, get, use_var);
    VCALL(*vec_e_kill, push_back, expr_var);
}

static IR_var create_new_expr_var_map(AvailableExpressionsAnalysis *t, Expr expr) {
    IR_var expr_var = ir_var_generator();
    VCALL(t->mapExpr, insert, expr, expr_var);
    if(!expr.rs1.is_const) map_expr_kill_insert(t, expr.rs1.var, expr_var);
    if(!expr.rs2.is_const) map_expr_kill_insert(t, expr.rs2.var, expr_var);
    return expr_var;
}

// 简单等价表达式替换
bool simple_expr_optimize(IR_stmt **stmt_ptr_ptr) {
    IR_stmt *stmt = *stmt_ptr_ptr;
    IR_op_stmt *op_stmt = (IR_op_stmt*)stmt;
    switch (op_stmt->op) {
        case IR_OP_ADD: {
            if(op_stmt->rs1.is_const && op_stmt->rs1.const_val == 0) {
                *stmt_ptr_ptr = (IR_stmt*)NEW(IR_assign_stmt, op_stmt->rd, op_stmt->rs2);
                RDELETE(IR_stmt, stmt);
                return true;
            }
            if(op_stmt->rs2.is_const && op_stmt->rs2.const_val == 0) {
                *stmt_ptr_ptr = (IR_stmt*)NEW(IR_assign_stmt, op_stmt->rd, op_stmt->rs1);
                RDELETE(IR_stmt, stmt);
                return true;
            }
            break;
        }
        case IR_OP_SUB: {
            if(op_stmt->rs2.is_const && op_stmt->rs2.const_val == 0) {
                *stmt_ptr_ptr = (IR_stmt*)NEW(IR_assign_stmt, op_stmt->rd, op_stmt->rs1);
                RDELETE(IR_stmt, stmt);
                return true;
            }
            break;
        }
        case IR_OP_MUL: {
            if(op_stmt->rs1.is_const && op_stmt->rs1.const_val == 1) {
                *stmt_ptr_ptr = (IR_stmt*)NEW(IR_assign_stmt, op_stmt->rd, op_stmt->rs2);
                RDELETE(IR_stmt, stmt);
                return true;
            }
            if(op_stmt->rs2.is_const && op_stmt->rs2.const_val == 1) {
                *stmt_ptr_ptr = (IR_stmt*)NEW(IR_assign_stmt, op_stmt->rd, op_stmt->rs1);
                RDELETE(IR_stmt, stmt);
                return true;
            }
            break;
        }
        case IR_OP_DIV: {
            if(op_stmt->rs2.is_const && op_stmt->rs2.const_val == 1) {
                *stmt_ptr_ptr = (IR_stmt*)NEW(IR_assign_stmt, op_stmt->rd, op_stmt->rs1);
                RDELETE(IR_stmt, stmt);
                return true;
            }
            break;
        }
    }
    return false;
}


// 将公共表达式标记为相同变量
void AvailableExpressionsAnalysis_merge_common_expr(AvailableExpressionsAnalysis *t,
                                                    IR_function *func) {
    for_list(IR_block_ptr, i, func->blocks) {
        IR_block *blk = i->val;
        for_list(IR_stmt_ptr, j, i->val->stmts) {
            IR_stmt *stmt = j->val;
            if(stmt->stmt_type == IR_OP_STMT) {
                IR_op_stmt *op_stmt = (IR_op_stmt*)stmt;
                if(simple_expr_optimize(&j->val)) continue;
                Expr expr = {.op = op_stmt->op, .rs1 = op_stmt->rs1, .rs2 = op_stmt->rs2};
                if(expr.op == IR_OP_ADD || expr.op == IR_OP_MUL) {
                    if(IR_val_CMP(expr.rs1, expr.rs2) == 0) {
                        IR_val tmp = expr.rs1;
                        expr.rs1 = expr.rs2;
                        expr.rs2 = tmp;
                    }
                }
                IR_var expr_var;
                if(!VCALL(t->mapExpr, exist, expr)) {
                    expr_var = create_new_expr_var_map(t, expr);
                } else expr_var = VCALL(t->mapExpr, get, expr);
                VCALL(blk->stmts, insert_back, j,
                      (IR_stmt*)NEW(IR_assign_stmt,
                                    op_stmt->rd,
                                    (IR_val){.is_const = false, .var = expr_var}));
                op_stmt->rd = expr_var;
            }
        }
    }
}

// 消除公共表达式
static void block_remove_available_expr_def (AvailableExpressionsAnalysis *t, IR_block *blk) {
    Fact_set_var *blk_in_fact = VCALL(*t, getInFact, blk);
    Fact_set_var *new_in_fact = AvailableExpressionsAnalysis_newInitialFact(t);
    AvailableExpressionsAnalysis_meetInto(t, blk_in_fact, new_in_fact);
    for_list(IR_stmt_ptr, i, blk->stmts) {
        IR_stmt *stmt = i->val;
        if(stmt->stmt_type == IR_OP_STMT) {
            IR_op_stmt *op_stmt = (IR_op_stmt*)stmt;
            IR_var expr_var = op_stmt->rd;
            if(VCALL(new_in_fact->set, exist, expr_var)) // available
                stmt->dead = true;
        }
        AvailableExpressionsAnalysis_transferStmt(t, stmt, new_in_fact);
    }
    RDELETE(Fact_set_var, new_in_fact);
    remove_dead_stmt(blk); // 删除标记为 dead 的可用表达式赋值
}

void AvailableExpressionsAnalysis_remove_available_expr_def (AvailableExpressionsAnalysis *t, IR_function *func) {
    for_list(IR_block_ptr, j, func->blocks) {
        IR_block *blk = j->val;
        block_remove_available_expr_def(t, blk);
    }
}



