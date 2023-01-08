//
// Created by hby on 22-10-21.
//

#ifndef CODE_VECTOR_H
#define CODE_VECTOR_H

#include <stdlib.h>
#include <macro.h>
#include <assert.h>
#include <stdbool.h>
#include <object.h>

//// ================================== Vector ==================================

typedef unsigned int vec_size_t;

#define INIT_VECTOR_NR_ARR 4
static inline vec_size_t new_arr_alloc_size(vec_size_t old_size) {
    return old_size == 0 ? INIT_VECTOR_NR_ARR : old_size * 2;
}

#define DEF_VECTOR(type) \
    typedef struct concat(Vec_, type) concat(Vec_, type); \
    struct concat(Vec_, type) { \
        struct concat3(Vec_, type, _virtualTable) { \
            void (*teardown) (concat(Vec_, type) *vec); \
            void (*resize) (concat(Vec_, type) *vec, vec_size_t new_size); \
            void (*push_back) (concat(Vec_, type) *vec, type item); \
            void (*pop_back) (concat(Vec_, type) *vec); \
            vec_size_t (*find) (concat(Vec_, type) *vec, bool (*check)(type *arr_item, void *arg), void *arg); \
            vec_size_t (*lower_bound) (concat(Vec_, type) *vec, bool (*check)(type *arr_item, void *arg), void *arg); \
            void (*insert) (concat(Vec_, type) *vec, vec_size_t idx, type item); \
            void (*delete) (concat(Vec_, type) *vec, vec_size_t idx); \
        } const *vTable; \
        vec_size_t len; \
        vec_size_t nr_arr; \
        type *arr; \
    };\
    static inline void concat3(Vec_, type, _resize) (concat(Vec_, type) *vec, vec_size_t new_size) { \
        vec->nr_arr = new_size; \
        vec->arr = (type *)realloc(vec->arr, sizeof(type[new_size])); \
    } \
    static inline void concat3(Vec_, type, _teardown) (concat(Vec_, type) *vec) { \
        if(vec->nr_arr != 0) free(vec->arr); \
        vec->len = vec->nr_arr = 0; \
        vec->arr = NULL; \
    } \
    static inline void concat3(Vec_, type, _push_back) \
            (concat(Vec_, type) *vec, type item) { \
        if(vec->len == vec->nr_arr) {       \
            concat3(Vec_, type, _resize)(vec, new_arr_alloc_size(vec->nr_arr)); \
        } \
        vec->arr[vec->len ++] = item; \
    } \
    static inline void concat3(Vec_, type, _pop_back) \
            (concat(Vec_, type) *vec) { \
        assert(vec->len); \
        vec->len --; \
    } \
    static inline vec_size_t concat3(Vec_, type, _find) \
        (concat(Vec_, type) *vec, bool (*check)(type *arr_item, void *arg), void *arg) { \
        for(vec_size_t idx = 0; idx < vec->len; idx ++) { \
            if(check(&vec->arr[idx], arg)) return idx; \
        } \
        return -1; \
    }                    \
    static inline vec_size_t concat3(Vec_, type, _lower_bound) \
        (concat(Vec_, type) *vec, bool (*check)(type *arr_item, void *arg), void *arg) { \
        vec_size_t l = 0, r = vec->len; \
        while(l < r) {   \
            vec_size_t mid = (l + r) / 2;             \
            if(check(&vec->arr[mid], arg)) r = mid;         \
            else l = mid + 1;             \
        } \
        return l; \
    } \
    static inline void concat3(Vec_, type, _insert) \
            (concat(Vec_, type) *vec, vec_size_t idx, type item) { \
        assert(idx <= vec->len); \
        concat3(Vec_, type, _push_back) (vec, item); \
        for(vec_size_t i = vec->len - 1; i > idx ; i --) vec->arr[i] = vec->arr[i - 1]; \
        vec->arr[idx] = item; \
    } \
    static inline void concat3(Vec_, type, _delete) \
            (concat(Vec_, type) *vec, vec_size_t idx) { \
        assert(idx < vec->len); \
        vec->len --; \
        for(vec_size_t i = idx; i < vec->len ; i ++) vec->arr[i] = vec->arr[i + 1]; \
    } \
    static inline void concat3(Vec_, type, _init_resize) (concat(Vec_, type) *vec, vec_size_t size) { \
        const static struct concat3(Vec_, type, _virtualTable) vTable = { \
            .teardown = concat3(Vec_, type, _teardown), \
            .resize = concat3(Vec_, type, _resize), \
            .push_back = concat3(Vec_, type, _push_back), \
            .pop_back = concat3(Vec_, type, _pop_back), \
            .find = concat3(Vec_, type, _find), \
            .lower_bound = concat3(Vec_, type, _lower_bound), \
            .insert = concat3(Vec_, type, _insert), \
            .delete = concat3(Vec_, type, _delete) \
        }; \
        vec->vTable = &vTable; \
        vec->len = 0; \
        vec->nr_arr = size; \
        if(size == 0) vec->arr = NULL; \
        else vec->arr = (type *)malloc(sizeof(type[size])); \
    } \
    static inline void concat3(Vec_, type, _init) (concat(Vec_, type) *vec) { \
        concat3(Vec_, type, _init_resize) (vec, INIT_VECTOR_NR_ARR); \
    } \

#define for_vec(type, item, vec) for(type *item = (vec).arr; item != (vec).arr + (vec).len; item ++)

#endif //CODE_VECTOR_H
