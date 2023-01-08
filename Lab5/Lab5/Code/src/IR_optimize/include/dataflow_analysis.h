//
// Created by hby on 22-12-2.
//

#ifndef CODE_DATAFLOW_ANALYSIS_H
#define CODE_DATAFLOW_ANALYSIS_H

#include <IR.h>

//// ============================ Dataflow Analysis ============================

typedef struct DataflowAnalysis DataflowAnalysis;

typedef void *Fact;

typedef struct DataflowAnalysis DataflowAnalysis;
struct DataflowAnalysis {
    struct {
        void (*teardown) (DataflowAnalysis *t);
        bool (*isForward) (DataflowAnalysis *t);
        Fact *(*newBoundaryFact) (DataflowAnalysis *t, IR_function *func);
        Fact *(*newInitialFact) (DataflowAnalysis *t);
        void (*setInFact) (DataflowAnalysis *t, IR_block *blk, Fact *fact);
        void (*setOutFact) (DataflowAnalysis *t, IR_block *blk, Fact *fact);
        Fact *(*getInFact) (DataflowAnalysis *t, IR_block *blk);
        Fact *(*getOutFact) (DataflowAnalysis *t, IR_block *blk);
        bool (*meetInto) (DataflowAnalysis *t, Fact *fact, Fact *target);
        bool (*transferBlock) (DataflowAnalysis *t, IR_block *block, Fact *in_fact, Fact *out_fact);
        void (*printResult) (DataflowAnalysis *t, IR_function *func);
    } const *vTable;
};

//// Fact

// set

DEF_SET(IR_var)
typedef Set_IR_var *Set_ptr_IR_var;
DEF_MAP(IR_block_ptr, Set_ptr_IR_var)

//// ============================ Optimize ============================

extern void remove_dead_block(IR_function *func);
extern void remove_dead_stmt(IR_block *blk);

extern void iterative_solver(DataflowAnalysis *t, IR_function *func);
extern void worklist_solver(DataflowAnalysis *t, IR_function *func);

#endif //CODE_DATAFLOW_ANALYSIS_H
