//
// Created by hby on 22-11-21.
//

#ifndef CODE_LIST_H
#define CODE_LIST_H

#include <assert.h>
#include <stdlib.h>
#include <macro.h>
#include <object.h>

#define DEF_LIST(TYPE) \
        typedef struct concat(ListNode_, TYPE) { \
            struct concat(ListNode_, TYPE) *pre, *nxt; \
            TYPE val; \
        } concat(ListNode_, TYPE); \
        typedef struct concat(List_, TYPE) concat(List_, TYPE); \
        struct concat(List_, TYPE) { \
            struct concat3(List_, TYPE, _virtualTable) { \
                void (*teardown) (concat(List_, TYPE) *l); \
                void (*insert_front) (concat(List_, TYPE) *l, concat(ListNode_, TYPE) *x, TYPE val); \
                void (*insert_back) (concat(List_, TYPE) *l, concat(ListNode_, TYPE) *x, TYPE val); \
                void (*push_front) (concat(List_, TYPE) *l, TYPE val); \
                void (*push_back) (concat(List_, TYPE) *l, TYPE val); \
                concat(ListNode_, TYPE) *(*delete) (concat(List_, TYPE) *l, concat(ListNode_, TYPE) *x); \
                void (*pop_front) (concat(List_, TYPE) *l); \
                void (*pop_back) (concat(List_, TYPE) *l); \
            } const *vTable; \
            struct concat(ListNode_, TYPE) *head, *tail; \
        }; \
        static inline void concat3(ListNode_, TYPE, _init) \
                (concat(ListNode_, TYPE) *x, TYPE val) { \
            *x = (concat(ListNode_, TYPE)){.pre = NULL, .nxt = NULL, .val = val}; \
        } \
        static inline void concat3(List_, TYPE, _teardown) (concat(List_, TYPE) *l) { \
            concat(ListNode_, TYPE) *x = l->head, *pre; \
            while(x) { \
                pre = x, x = x->nxt; \
                free(pre); \
            } \
        } \
        static inline void concat3(List_, TYPE, _insert_front) (concat(List_, TYPE) *l, concat(ListNode_, TYPE) *x, TYPE val) { \
            concat(ListNode_, TYPE) *new_x = NEW(concat(ListNode_, TYPE), val); \
            if(x == NULL) { \
                l->head = l->tail = new_x; \
                return; \
            } \
            new_x->nxt = x; \
            new_x->pre = x->pre; \
            if(x->pre != NULL) \
                x->pre->nxt = new_x; \
            else \
                l->head = new_x; \
            x->pre = new_x; \
        } \
        static inline void concat3(List_, TYPE, _insert_back) (concat(List_, TYPE) *l, concat(ListNode_, TYPE) *x, TYPE val) { \
            concat(ListNode_, TYPE) *new_x = NEW(concat(ListNode_, TYPE), val); \
            if(x == NULL) { \
                l->head = l->tail = new_x; \
                return; \
            } \
            new_x->pre = x; \
            new_x->nxt = x->nxt; \
            if(x->nxt != NULL) \
                x->nxt->pre = new_x; \
            else \
                l->tail = new_x; \
            x->nxt = new_x; \
        } \
        static inline void concat3(List_, TYPE, _push_front) (concat(List_, TYPE) *l, TYPE val) { \
            concat3(List_, TYPE, _insert_front) (l, l->head, val); \
        } \
        static inline void concat3(List_, TYPE, _push_back) (concat(List_, TYPE) *l, TYPE val) { \
            concat3(List_, TYPE, _insert_back) (l, l->tail, val); \
        } \
        static inline concat(ListNode_, TYPE) *concat3(List_, TYPE, _delete) (concat(List_, TYPE) *l, concat(ListNode_, TYPE) *x) { \
            assert(x != NULL); \
            concat(ListNode_, TYPE) *pre = x->pre, *nxt = x->nxt; \
            if(x == l->head) l->head = nxt; \
            if(x == l->tail) l->tail = pre; \
            if(pre != NULL) pre->nxt = nxt; \
            if(nxt != NULL) nxt->pre = pre; \
            free(x); \
            return nxt; \
        } \
        static inline void concat3(List_, TYPE, _pop_front) (concat(List_, TYPE) *l) { \
            concat3(List_, TYPE, _delete)(l, l->head); \
        } \
        static inline void concat3(List_, TYPE, _pop_back) (concat(List_, TYPE) *l) { \
            concat3(List_, TYPE, _delete)(l, l->tail); \
        } \
        static inline void concat3(List_, TYPE, _init) (concat(List_, TYPE) *l) { \
            const static struct concat3(List_, TYPE, _virtualTable) vTable = { \
                .teardown = concat3(List_, TYPE, _teardown), \
                .insert_front = concat3(List_, TYPE, _insert_front), \
                .insert_back = concat3(List_, TYPE, _insert_back), \
                .push_front = concat3(List_, TYPE, _push_front), \
                .push_back = concat3(List_, TYPE, _push_back), \
                .delete = concat3(List_, TYPE, _delete), \
                .pop_front = concat3(List_, TYPE, _pop_front), \
                .pop_back = concat3(List_, TYPE, _pop_back) \
            }; \
            l->vTable = &vTable; \
            l->head = l->tail = NULL; \
        } \

#define for_list(type, it, list) for(concat(ListNode_, type) *it = (list).head; it; it = it->nxt)
#define rfor_list(type, it, list) for(concat(ListNode_, type) *it = (list).tail; it; it = it->pre)

#endif //CODE_LIST_H
