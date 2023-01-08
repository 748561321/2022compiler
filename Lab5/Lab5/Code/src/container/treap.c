//
// Created by hby on 22-11-19.
//

#include <container/treap.h>
#include <stdio.h>

#define OFFSET_PTR(ptr, offset) (((void*)(ptr)) + offset)

//// =============================== Treap Node Base ===============================

static void UP(TreapNodeBase *x) {
    treap_size_t size = 1;
    if(x->ch[0])
        x->ch[0]->fa = x, size += x->ch[0]->size;
    if(x->ch[1])
        x->ch[1]->fa = x, size += x->ch[1]->size;
    x->size = size;
}

void TreapNodeBase_init(TreapNodeBase *x) {
    x->ch[0] = x->ch[1] = NULL;
    x->fa = NULL;
    x->fix = rand();
    x->size = 1;
}

void TreapNodeBase_teardown(TreapNodeBase *x,
                            size_t content_offset) {
    if(x->ch[0] != NULL)
        TreapNodeBase_teardown(x->ch[0], content_offset), free(x->ch[0]);
    if(x->ch[1] != NULL)
        TreapNodeBase_teardown(x->ch[1], content_offset), free(x->ch[1]);
}

static void TreapNodeBase_rotate(TreapNodeBase **x_ptr, int d) {
    TreapNodeBase *x = *x_ptr, *y = x->ch[d^1], *fa = x->fa;
    x->ch[d^1] = y->ch[d];
    y->ch[d] = x;
    *x_ptr = y;
    y->fa = fa;
    UP(y->ch[d]); UP(y);
}

bool TreapNodeBase_insert(TreapNodeBase **x_ptr,
                          size_t content_offset,
                          content_cmp_func_t cmp_func,
                          void *arg,
                          new_node_func_t new_node_func) {
    TreapNodeBase *x = *x_ptr;
    if(x == NULL) {
        *x_ptr = new_node_func(arg);
        return true;
    }
    int d = cmp_func(arg, OFFSET_PTR(x, content_offset));
    if(d == -1)
        return false;
    bool ret = TreapNodeBase_insert(&x->ch[d], content_offset, cmp_func, arg, new_node_func);
    if(x->fix < x->ch[d]->fix)
        TreapNodeBase_rotate(x_ptr, d^1), x = *x_ptr;
    UP(x);
    return ret;
}

static void TreapNodeBase_delete_node(TreapNodeBase **x_ptr,
                                      size_t content_offset) {
    TreapNodeBase *x = *x_ptr, *fa = x->fa;
    if(x->ch[0] && x->ch[1]) {
        int d = x->ch[0]->fix > x->ch[1]->fix;
        TreapNodeBase_rotate(x_ptr, d), x = *x_ptr;
        TreapNodeBase_delete_node(&x->ch[d], content_offset);
    } else {
        *x_ptr = x->ch[0] ? x->ch[0] : x->ch[1];
        free(x);
        x = *x_ptr;
    }
    if(x != NULL)
        x->fa = fa, UP(x);
}

bool TreapNodeBase_delete(TreapNodeBase **x_ptr,
                          size_t content_offset,
                          content_cmp_func_t cmp_func,
                          void *arg) {
    TreapNodeBase *x = *x_ptr;
    if(x == NULL)
        return false;
    int d = cmp_func(arg, OFFSET_PTR(x, content_offset));
    if(d != -1) {
        bool ret = TreapNodeBase_delete(&x->ch[d], content_offset, cmp_func, arg);
        UP(x);
        return ret;
    }
    TreapNodeBase_delete_node(x_ptr, content_offset);
    return true;
}

TreapNodeBase *TreapNodeBase_find_iter(TreapNodeBase *x,
                                       size_t content_offset,
                                       content_cmp_func_t cmp_func,
                                       void *arg) {
    if(x == NULL)
        return NULL;
    int d = cmp_func(arg, OFFSET_PTR(x, content_offset));
    return d == -1 ? x : TreapNodeBase_find_iter(x->ch[d], content_offset, cmp_func, arg);
}

TreapNodeBase *TreapNodeBase_first_iter(TreapNodeBase *x) {
    if(x == NULL) return NULL;
    while(x->ch[0]) x = x->ch[0];
    return x;
}

TreapNodeBase *TreapNodeBase_last_iter(TreapNodeBase *x) {
    if(x == NULL) return NULL;
    while(x->ch[1]) x = x->ch[1];
    return x;
}

TreapNodeBase *TreapNodeBase_next_iter(TreapNodeBase *x) {
    if(x->ch[1])
        return TreapNodeBase_first_iter(x->ch[1]);
    while(true) {
        TreapNodeBase *fa = x->fa;
        if(fa == NULL)
            return NULL;
        if(x == fa->ch[0])
            return fa;
        else
            x = fa;
    }
}

TreapNodeBase *TreapNodeBase_prev_iter(TreapNodeBase *x) {
    if(x->ch[0])
        return TreapNodeBase_last_iter(x->ch[0]);
    while(true) {
        TreapNodeBase *fa = x->fa;
        if(fa == NULL)
            return NULL;
        if(x == fa->ch[1])
            return fa;
        else
            x = fa;
    }
}
