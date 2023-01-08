//
// Created by hby on 22-12-2.
//

#ifndef CODE_CONSTANT_PROPAGATION_H
#define CODE_CONSTANT_PROPAGATION_H

#include <dataflow_analysis.h>

typedef struct {
    enum {
        UNDEF, CONST, NAC // 未定义, 常量, 非常量
    } kind;
    int const_val;
} CPValue;
static inline CPValue get_UNDEF() {return (CPValue){.kind = UNDEF, .const_val = 0};}
static inline CPValue get_CONST(int const_val) {return (CPValue){.kind = CONST, .const_val = const_val};}
static inline CPValue get_NAC() {return (CPValue){.kind = NAC, .const_val = 0};}

DEF_MAP(IR_var, CPValue)
typedef Map_IR_var_CPValue *Map_ptr_IR_var_CPValue;
DEF_MAP(IR_block_ptr, Map_ptr_IR_var_CPValue)

typedef struct ConstantPropagation ConstantPropagation;
typedef struct ConstantPropagation {
    struct ConstantPropagation_virtualTable {
        void (*teardown) (ConstantPropagation *t);
        bool (*isForward) (ConstantPropagation *t);
        Map_IR_var_CPValue *(*newBoundaryFact) (ConstantPropagation *t, IR_function *func);
        Map_IR_var_CPValue *(*newInitialFact) (ConstantPropagation *t);
        void (*setInFact) (ConstantPropagation *t, IR_block *blk, Map_IR_var_CPValue *fact);
        void (*setOutFact) (ConstantPropagation *t, IR_block *blk, Map_IR_var_CPValue *fact);
        Map_IR_var_CPValue *(*getInFact) (ConstantPropagation *t, IR_block *blk);
        Map_IR_var_CPValue *(*getOutFact) (ConstantPropagation *t, IR_block *blk);
        bool (*meetInto) (ConstantPropagation *t, Map_IR_var_CPValue *fact, Map_IR_var_CPValue *target);
        bool (*transferBlock) (ConstantPropagation *t, IR_block *block, Map_IR_var_CPValue *in_fact, Map_IR_var_CPValue *out_fact);
        void (*printResult) (ConstantPropagation *t, IR_function *func);
    } const *vTable;
    Map_IR_block_ptr_Map_ptr_IR_var_CPValue mapInFact, mapOutFact;
} ConstantPropagation;
extern void ConstantPropagation_init(ConstantPropagation *t);
extern void ConstantPropagation_transferStmt (ConstantPropagation *t,
                                              IR_stmt *stmt,
                                              Map_IR_var_CPValue *fact);
extern bool ConstantPropagation_transferBlock (ConstantPropagation *t,
                                               IR_block *block,
                                               Map_IR_var_CPValue *in_fact,
                                               Map_IR_var_CPValue *out_fact);
extern void ConstantPropagation_print_result (ConstantPropagation *t, IR_function *func);
extern void ConstantPropagation_constant_folding (ConstantPropagation *t, IR_function *func);

#endif //CODE_CONSTANT_PROPAGATION_H
