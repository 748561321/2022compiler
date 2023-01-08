//
// Created by hby on 22-12-2.
//

#ifndef CODE_COPY_PROPAGATION_H
#define CODE_COPY_PROPAGATION_H

#include <dataflow_analysis.h>

DEF_MAP(IR_var, IR_var)
DEF_LIST(IR_var)

/* 为了避免赋值为全集时需要插入所有元素, 这里用is_top代表全集(TOP), 但set中暂时为空集
 * def := use 属于 Fact 当且仅当 def_to_use[def] = use 且 use_to_def[use] = def
 */
typedef struct {
    bool is_top;
    Map_IR_var_IR_var def_to_use, use_to_def;
} Fact_def_use, *Fact_def_use_ptr;
extern void Fact_def_use_init(Fact_def_use *fact, bool is_top);
extern void Fact_def_use_teardown(Fact_def_use *fact);

DEF_MAP(IR_block_ptr, Fact_def_use_ptr)

typedef struct CopyPropagation CopyPropagation;
typedef struct CopyPropagation {
    struct CopyPropagation_virtualTable {
        void (*teardown) (CopyPropagation *t);
        bool (*isForward) (CopyPropagation *t);
        Fact_def_use *(*newBoundaryFact) (CopyPropagation *t, IR_function *func);
        Fact_def_use *(*newInitialFact) (CopyPropagation *t);
        void (*setInFact) (CopyPropagation *t, IR_block *blk, Fact_def_use *fact);
        void (*setOutFact) (CopyPropagation *t, IR_block *blk, Fact_def_use *fact);
        Fact_def_use *(*getInFact) (CopyPropagation *t, IR_block *blk);
        Fact_def_use *(*getOutFact) (CopyPropagation *t, IR_block *blk);
        bool (*meetInto) (CopyPropagation *t, Fact_def_use *fact, Fact_def_use *target);
        bool (*transferBlock) (CopyPropagation *t, IR_block *block, Fact_def_use *in_fact, Fact_def_use *out_fact);
        void (*printResult) (CopyPropagation *t, IR_function *func);
    } const *vTable;
    Map_IR_block_ptr_Fact_def_use_ptr mapInFact, mapOutFact;
} CopyPropagation;
extern void CopyPropagation_init(CopyPropagation *t);
extern void CopyPropagation_transferStmt (CopyPropagation *t,
                                          IR_stmt *stmt,
                                          Fact_def_use *fact);
extern bool CopyPropagation_transferBlock (CopyPropagation *t,
                                           IR_block *block,
                                           Fact_def_use *in_fact,
                                           Fact_def_use *out_fact);
extern void CopyPropagation_print_result (CopyPropagation *t, IR_function *func);
extern void CopyPropagation_replace_available_use_copy (CopyPropagation *t, IR_function *func);

#endif //CODE_COPY_PROPAGATION_H
