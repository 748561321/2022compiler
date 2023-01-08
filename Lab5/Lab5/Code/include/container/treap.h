//
// Created by hby on 22-11-2.
//

#ifndef CODE_TREAP_H
#define CODE_TREAP_H

#include <macro.h>
#include <object.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned treap_size_t;
#define NUMBER_CMP(a, b) ((a) == (b) ? -1 : (a) > (b))
#define TMP_PTR NULL
#define TREAP_CONTENT_OFFSET(TYPE) \
            (size_t)((void*)&((TYPE*)TMP_PTR)->key - TMP_PTR)

//// =============================== Treap Node Base ===============================

#define CLASS_TREAP_NODE_BASE struct{ \
        struct TreapNodeBase *ch[2], *fa; \
        int fix; \
        treap_size_t size;};
typedef struct TreapNodeBase{
    CLASS_TREAP_NODE_BASE
}TreapNodeBase;
typedef int (*content_cmp_func_t)(void*,void*);
typedef void (*content_teardown_func_t)(void*);
typedef TreapNodeBase *(*new_node_func_t)(void*);

extern void TreapNodeBase_init(TreapNodeBase *x);
extern void TreapNodeBase_teardown(TreapNodeBase *x, size_t content_offset);
extern bool TreapNodeBase_insert(TreapNodeBase **x_ptr, size_t content_offset, content_cmp_func_t cmp_func, void *arg, new_node_func_t new_node_func);
extern bool TreapNodeBase_delete(TreapNodeBase **x_ptr, size_t content_offset, content_cmp_func_t cmp_func, void *arg);
extern TreapNodeBase *TreapNodeBase_find_iter(TreapNodeBase *x, size_t content_offset, content_cmp_func_t cmp_func, void *arg);
extern TreapNodeBase *TreapNodeBase_first_iter(TreapNodeBase *x);
extern TreapNodeBase *TreapNodeBase_last_iter(TreapNodeBase *x);
extern TreapNodeBase *TreapNodeBase_next_iter(TreapNodeBase *x);
extern TreapNodeBase *TreapNodeBase_prev_iter(TreapNodeBase *x);

#define for_treap(TYPE, it, treap) \
            for( \
                TYPE *it = (TYPE*) TreapNodeBase_first_iter((treap).root); \
                it != NULL; \
                it = (TYPE*) TreapNodeBase_next_iter((TreapNodeBase*)it) \
            )

//// =============================== Treap Map ===============================


#define DEF_MAP_CMP(KEY_TYPE, VAL_TYPE, Map_key_cmp) \
        typedef struct concat4(MapNode_, KEY_TYPE, _, VAL_TYPE) {   \
            CLASS_TREAP_NODE_BASE \
            struct {KEY_TYPE key; VAL_TYPE val;}; \
        } concat4(MapNode_, KEY_TYPE, _, VAL_TYPE); \
        typedef struct concat4(Map_, KEY_TYPE, _, VAL_TYPE) concat4(Map_, KEY_TYPE, _, VAL_TYPE); \
        struct concat4(Map_, KEY_TYPE, _, VAL_TYPE) { \
            struct concat5(Map_, KEY_TYPE, _, VAL_TYPE, _virtualTable) { \
                void (*teardown) (concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t); \
                bool (*insert) (concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t, KEY_TYPE key, VAL_TYPE val); \
                bool (*delete) (concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t, KEY_TYPE key); \
                bool (*exist) (concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t, KEY_TYPE key); \
                VAL_TYPE (*get) (concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t, KEY_TYPE key); \
                void (*set) (concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t, KEY_TYPE key, VAL_TYPE val); \
            } const *vTable; \
            TreapNodeBase *root; \
        }; \
        static inline TreapNodeBase *concat5(MapNode_, KEY_TYPE, _, VAL_TYPE, _new_node) (void *content) { \
            struct {KEY_TYPE key; VAL_TYPE val;} *key_val_pair_ptr = content; \
            concat4(MapNode_, KEY_TYPE, _, VAL_TYPE) *t = \
                (concat4(MapNode_, KEY_TYPE, _, VAL_TYPE)*)malloc(sizeof(concat4(MapNode_, KEY_TYPE, _, VAL_TYPE))); \
            TreapNodeBase_init((TreapNodeBase*)t); \
            t->key = key_val_pair_ptr->key, t->val = key_val_pair_ptr->val; \
            return (TreapNodeBase*)t; \
        } \
        static inline int concat5(MapNode_, KEY_TYPE, _, VAL_TYPE, _cmp_func) (void *a, void *b) { \
            struct {KEY_TYPE key; VAL_TYPE val;} *a_pair_ptr = a, *b_pair_ptr = b; \
            return Map_key_cmp(a_pair_ptr->key, b_pair_ptr->key); \
        } \
        static inline void concat5(Map_, KEY_TYPE, _, VAL_TYPE, _teardown) (concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t) { \
            if(t->root) { \
                TreapNodeBase_teardown(t->root, \
                                       TREAP_CONTENT_OFFSET(concat4(MapNode_, KEY_TYPE, _, VAL_TYPE))); \
                free(t->root); \
            }\
            t->root = NULL; \
        } \
        static inline bool concat5(Map_, KEY_TYPE, _, VAL_TYPE, _insert)(concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t, KEY_TYPE key, VAL_TYPE val) { \
            struct {KEY_TYPE key; VAL_TYPE val;} key_val_pair; \
            key_val_pair.key = key, key_val_pair.val = val; \
            return TreapNodeBase_insert(&t->root, \
                                        TREAP_CONTENT_OFFSET(concat4(MapNode_, KEY_TYPE, _, VAL_TYPE)), \
                                        concat5(MapNode_, KEY_TYPE, _, VAL_TYPE, _cmp_func), \
                                        &key_val_pair, \
                                        concat5(MapNode_, KEY_TYPE, _, VAL_TYPE, _new_node)); \
        } \
        static inline bool concat5(Map_, KEY_TYPE, _, VAL_TYPE, _delete)(concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t, KEY_TYPE key) { \
            struct {KEY_TYPE key; VAL_TYPE val;} key_val_pair; \
            key_val_pair.key = key; \
            return TreapNodeBase_delete(&t->root, \
                                        TREAP_CONTENT_OFFSET(concat4(MapNode_, KEY_TYPE, _, VAL_TYPE)), \
                                        concat5(MapNode_, KEY_TYPE, _, VAL_TYPE, _cmp_func), \
                                        &key_val_pair); \
        } \
        static inline bool concat5(Map_, KEY_TYPE, _, VAL_TYPE, _exist)(concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t, KEY_TYPE key) { \
            struct {KEY_TYPE key; VAL_TYPE val;} key_val_pair; \
            key_val_pair.key = key; \
            return TreapNodeBase_find_iter(t->root, \
                                           TREAP_CONTENT_OFFSET(concat4(MapNode_, KEY_TYPE, _, VAL_TYPE)), \
                                           concat5(MapNode_, KEY_TYPE, _, VAL_TYPE, _cmp_func), \
                                           &key_val_pair) != NULL; \
        } \
        static inline VAL_TYPE concat5(Map_, KEY_TYPE, _, VAL_TYPE, _get)(concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t, KEY_TYPE key) { \
            struct {KEY_TYPE key; VAL_TYPE val;} key_val_pair; \
            key_val_pair.key = key; \
            concat4(MapNode_, KEY_TYPE, _, VAL_TYPE) *x = \
                (concat4(MapNode_, KEY_TYPE, _, VAL_TYPE)*) \
                    TreapNodeBase_find_iter(t->root, \
                                            TREAP_CONTENT_OFFSET(concat4(MapNode_, KEY_TYPE, _, VAL_TYPE)), \
                                            concat5(MapNode_, KEY_TYPE, _, VAL_TYPE, _cmp_func), \
                                            &key_val_pair); \
            assert(x != NULL); \
            return x->val; \
        } \
        static inline void concat5(Map_, KEY_TYPE, _, VAL_TYPE, _set)(concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t, KEY_TYPE key, VAL_TYPE val) { \
            struct {KEY_TYPE key; VAL_TYPE val;} key_val_pair; \
            key_val_pair.key = key; \
            concat4(MapNode_, KEY_TYPE, _, VAL_TYPE) *x = \
                (concat4(MapNode_, KEY_TYPE, _, VAL_TYPE)*) \
                    TreapNodeBase_find_iter(t->root, \
                                            TREAP_CONTENT_OFFSET(concat4(MapNode_, KEY_TYPE, _, VAL_TYPE)), \
                                            concat5(MapNode_, KEY_TYPE, _, VAL_TYPE, _cmp_func), \
                                            &key_val_pair); \
            if(x == NULL) \
                concat5(Map_, KEY_TYPE, _, VAL_TYPE, _insert)(t, key, val); \
            else \
                x->val = val; \
        } \
        static inline void concat5(Map_, KEY_TYPE, _, VAL_TYPE, _init) (concat4(Map_, KEY_TYPE, _, VAL_TYPE) *t) { \
            const static struct concat5(Map_, KEY_TYPE, _, VAL_TYPE, _virtualTable) vTable = { \
                .teardown = concat5(Map_, KEY_TYPE, _, VAL_TYPE, _teardown), \
                .insert = concat5(Map_, KEY_TYPE, _, VAL_TYPE, _insert), \
                .delete = concat5(Map_, KEY_TYPE, _, VAL_TYPE, _delete), \
                .exist = concat5(Map_, KEY_TYPE, _, VAL_TYPE, _exist), \
                .set = concat5(Map_, KEY_TYPE, _, VAL_TYPE, _set), \
                .get = concat5(Map_, KEY_TYPE, _, VAL_TYPE, _get) \
            }; \
            t->vTable = &vTable; \
            t->root = NULL; \
        } \

#define for_map(KEY_TYPE, VAL_TYPE, it, map) \
            for_treap(concat4(MapNode_, KEY_TYPE, _, VAL_TYPE), it, map)

//// =============================== Treap Set ===============================

#define DEF_SET_CMP(KEY_TYPE, Set_key_cmp) \
        typedef struct concat2(SetNode_, KEY_TYPE) {   \
            CLASS_TREAP_NODE_BASE \
            KEY_TYPE key; \
        } concat2(SetNode_, KEY_TYPE); \
        typedef struct concat2(Set_, KEY_TYPE) concat2(Set_, KEY_TYPE); \
        struct concat2(Set_, KEY_TYPE) { \
            struct concat3(Set_, KEY_TYPE, _virtualTable) { \
                void (*teardown) (concat2(Set_, KEY_TYPE) *t); \
                bool (*insert) (concat2(Set_, KEY_TYPE) *t, KEY_TYPE key); \
                bool (*delete) (concat2(Set_, KEY_TYPE) *t, KEY_TYPE key); \
                bool (*exist) (concat2(Set_, KEY_TYPE) *t, KEY_TYPE key);  \
                bool (*union_with) (concat2(Set_, KEY_TYPE) *t, concat2(Set_, KEY_TYPE) *s); \
                bool (*intersect_with) (concat2(Set_, KEY_TYPE) *t, concat2(Set_, KEY_TYPE) *s); \
            } const *vTable; \
            TreapNodeBase *root; \
        }; \
        static inline void concat3(Set_, KEY_TYPE, _init) (concat2(Set_, KEY_TYPE) *t); \
        static inline TreapNodeBase *concat3(SetNode_, KEY_TYPE, _new_node) (void *content) { \
            KEY_TYPE *key_ptr = content;\
            concat2(SetNode_, KEY_TYPE) *t = \
                (concat2(SetNode_, KEY_TYPE)*)malloc(sizeof(concat2(SetNode_, KEY_TYPE))); \
            TreapNodeBase_init((TreapNodeBase*)t); \
            t->key = *key_ptr; \
            return (TreapNodeBase*)t; \
        } \
        static inline int concat3(SetNode_, KEY_TYPE, _cmp_func) (void *a, void *b) { \
            KEY_TYPE *a_ptr = a, *b_ptr = b; \
            return Set_key_cmp(*a_ptr, *b_ptr); \
        }\
        static inline void concat3(Set_, KEY_TYPE, _teardown) (concat2(Set_, KEY_TYPE) *t) { \
            if(t->root) { \
                TreapNodeBase_teardown(t->root, \
                                       TREAP_CONTENT_OFFSET(concat2(SetNode_, KEY_TYPE))); \
                free(t->root); \
            } \
            t->root = NULL; \
        } \
        static inline bool concat3(Set_, KEY_TYPE, _insert)(concat2(Set_, KEY_TYPE) *t, KEY_TYPE key) { \
            return TreapNodeBase_insert(&t->root, \
                                        TREAP_CONTENT_OFFSET(concat2(SetNode_, KEY_TYPE)), \
                                        concat3(SetNode_, KEY_TYPE, _cmp_func), \
                                        &key, \
                                        concat3(SetNode_, KEY_TYPE, _new_node)); \
        } \
        static inline bool concat3(Set_, KEY_TYPE, _delete)(concat2(Set_, KEY_TYPE) *t, KEY_TYPE key) { \
            return TreapNodeBase_delete(&t->root, \
                                       TREAP_CONTENT_OFFSET(concat2(SetNode_, KEY_TYPE)), \
                                       concat3(SetNode_, KEY_TYPE, _cmp_func), \
                                       &key); \
        } \
        static inline bool concat3(Set_, KEY_TYPE, _exist)(concat2(Set_, KEY_TYPE) *t, KEY_TYPE key) { \
            return TreapNodeBase_find_iter(t->root, \
                                           TREAP_CONTENT_OFFSET(concat2(SetNode_, KEY_TYPE)), \
                                           concat3(SetNode_, KEY_TYPE, _cmp_func), \
                                           &key) != NULL; \
        } \
        static inline bool concat3(Set_, KEY_TYPE, _union_with)(concat2(Set_, KEY_TYPE) *t, concat2(Set_, KEY_TYPE) *s) { \
            bool updated = false; \
            for_set(KEY_TYPE, it, *s) \
                updated |= VCALL(*t, insert, it->key); \
            return updated; \
        } \
        static inline bool concat3(Set_, KEY_TYPE, _intersect_with)(concat2(Set_, KEY_TYPE) *t, concat2(Set_, KEY_TYPE) *s) { \
            bool updated = false; \
            concat2(Set_, KEY_TYPE) not_exist; \
            concat3(Set_, KEY_TYPE, _init)(&not_exist); \
            for_set(KEY_TYPE, it, *t) \
                if(!VCALL(*s, exist, it->key)) { \
                    VCALL(not_exist, insert, it->key); \
                    updated = true; \
                } \
            for_set(KEY_TYPE, it, not_exist) \
                VCALL(*t, delete, it->key); \
            concat3(Set_, KEY_TYPE, _teardown)(&not_exist); \
            return updated; \
        } \
        static inline void concat3(Set_, KEY_TYPE, _init) (concat2(Set_, KEY_TYPE) *t) { \
            const static struct concat3(Set_, KEY_TYPE, _virtualTable) vTable = { \
                .teardown = concat3(Set_, KEY_TYPE, _teardown), \
                .insert = concat3(Set_, KEY_TYPE, _insert), \
                .delete = concat3(Set_, KEY_TYPE, _delete), \
                .exist = concat3(Set_, KEY_TYPE, _exist), \
                .union_with = concat3(Set_, KEY_TYPE, _union_with), \
                .intersect_with = concat3(Set_, KEY_TYPE, _intersect_with) \
            }; \
            t->vTable = &vTable; \
            t->root = NULL; \
        } \


#define for_set(KEY_TYPE, it, set) \
            for_treap(concat2(SetNode_, KEY_TYPE), it, set)


//// =============================== Usage ===============================

#define DEF_MAP(KEY_TYPE, VAL_TYPE) DEF_MAP_CMP(KEY_TYPE, VAL_TYPE, NUMBER_CMP)
#define DEF_SET(TYPE) DEF_SET_CMP(TYPE, NUMBER_CMP)

#endif //CODE_TREAP_H
