//
// Created by hby on 22-12-2.
//

#ifndef CODE_LIVE_VARIABLE_ANALYSIS_H
#define CODE_LIVE_VARIABLE_ANALYSIS_H

#include <dataflow_analysis.h>

typedef struct LiveVariableAnalysis LiveVariableAnalysis;
typedef struct LiveVariableAnalysis {
    struct LiveVariableAnalysis_virtualTable {
        void (*teardown) (LiveVariableAnalysis *t);
        bool (*isForward) (LiveVariableAnalysis *t);
        Set_IR_var *(*newBoundaryFact) (LiveVariableAnalysis *t, IR_function *func);
        Set_IR_var *(*newInitialFact) (LiveVariableAnalysis *t);
        void (*setInFact) (LiveVariableAnalysis *t, IR_block *blk, Set_IR_var *fact);
        void (*setOutFact) (LiveVariableAnalysis *t, IR_block *blk, Set_IR_var *fact);
        Set_IR_var *(*getInFact) (LiveVariableAnalysis *t, IR_block *blk);
        Set_IR_var *(*getOutFact) (LiveVariableAnalysis *t, IR_block *blk);
        bool (*meetInto) (LiveVariableAnalysis *t, Set_IR_var *fact, Set_IR_var *target);
        bool (*transferBlock) (LiveVariableAnalysis *t, IR_block *block, Set_IR_var *in_fact, Set_IR_var *out_fact);
        void (*printResult) (LiveVariableAnalysis *t, IR_function *func);
    } const *vTable;
    Map_IR_block_ptr_Set_ptr_IR_var mapInFact, mapOutFact; // Fact 为变量的集合
} LiveVariableAnalysis;
extern void LiveVariableAnalysis_init(LiveVariableAnalysis *t);
extern void LiveVariableAnalysis_transferStmt (LiveVariableAnalysis *t,
                                               IR_stmt *stmt,
                                               Set_IR_var *fact);
extern bool LiveVariableAnalysis_transferBlock (LiveVariableAnalysis *t,
                                                IR_block *block,
                                                Set_IR_var *in_fact,
                                                Set_IR_var *out_fact);
extern void LiveVariableAnalysis_print_result (LiveVariableAnalysis *t, IR_function *func);
extern bool LiveVariableAnalysis_remove_dead_def (LiveVariableAnalysis *t, IR_function *func);

#endif //CODE_LIVE_VARIABLE_ANALYSIS_H
