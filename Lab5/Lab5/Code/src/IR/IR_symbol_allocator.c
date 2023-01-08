//
// Created by hby on 22-11-8.
//

#include <IR.h>

#define FREE_STACK_SIZE 1024
static IR_var var_id_cnt = 0;
static IR_label label_id_cnt = 0;
static IR_var free_var[FREE_STACK_SIZE];
static IR_label free_label[FREE_STACK_SIZE];
static unsigned free_var_top = 0, free_label_top = 0;

IR_var ir_var_generator() {
    if(free_var_top)
        return free_var[free_var_top--];
    else
        return ++var_id_cnt;
}

IR_label ir_label_generator() {
    if(free_label_top)
        return free_label[free_label_top--];
    else
        return ++label_id_cnt;
}

void ir_func_var_recycle(IR_var var) {
    assert(free_var_top != FREE_STACK_SIZE - 1);
    free_var[++ free_var_top] = var;
}

void ir_label_recycle(IR_label label) {
    assert(free_label_top != FREE_STACK_SIZE - 1);
    free_label[++ free_label_top] = label;
}