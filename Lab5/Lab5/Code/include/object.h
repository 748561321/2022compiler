//
// Created by hby on 22-10-28.
//

#ifndef CODE_OBJECT_H
#define CODE_OBJECT_H

#include <macro.h>

#define CLASS_virtualTable struct{ \
        void (*teardown)(void *ptr);};

typedef struct virtualTable {
    CLASS_virtualTable
} virtualTable;

// 返回已执行init构造函数的指针, 类似于C++的 new obj 语句
#define NEW(TYPE, ...) ({                             \
            TYPE *TMP = (TYPE*)malloc(sizeof(TYPE));  \
            concat(TYPE, _init) (TMP, ##__VA_ARGS__); \
            TMP;                                      \
        })
// 从虚函数表vTable中调用函数, 指针需要解引用
#define VCALL(obj, func, ...) \
        (((obj).vTable)->func(&(obj), ##__VA_ARGS__))
// 执行teardown析构函数并free, 类似于C++的 delete obj 语句
#define DELETE(obj_ptr) \
        do { VCALL(*obj_ptr, teardown); free(obj_ptr); } while(0)
// 虚函数表中没有teardown, 需要显式调用特定类型的析构函数
#define RDELETE(type, obj_ptr) \
        do { concat(type, _teardown)(obj_ptr); free(obj_ptr); } while(0)

#endif //CODE_OBJECT_H
