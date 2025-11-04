#ifndef VECTOR_H 
#define VECTOR_H 

#include <stdlib.h>

#define DEFINE_VEC(VECTOR_TYPE) \ 
typedef struct { \ 
    VECTOR_TYPE *data; \ 
    size_t sz, cap; \ 
    VECTOR_TYPE (*CopyVoidPtr)(VECTOR_TYPE);  \ 
    void (*DeleteVoidPtr)(VECTOR_TYPE);  \ 
} vector; \ 
\ 
vector create_vector(size_t _cap,  VECTOR_TYPE (*CopyFunc)(VECTOR_TYPE), void (*DeleteFunc)(VECTOR_TYPE)) { \ 
    vector vec = {NULL, 0, _cap, CopyFunc, DeleteFunc};\ 
    vec.data = (VECTOR_TYPE*)malloc(sizeof(VECTOR_TYPE) * _cap);\ 
    if(!vec.data) {\ 
        vec.sz = vec.cap = 0;\ 
    }\ 
    return vec;\ 
}\ 
\ 
void erase_vector(vector* v) {\ 
    for(int i = 0; i < v->sz; ++i) {\ 
        v->DeleteVoidPtr(v->data[i]);\ 
    }\ 
    v->sz = v->cap = 0;\ 
}\ 
\ 
int is_equal_vector(const vector* v1, const vector* v2) {\ 
    if(v1->sz != v2->sz) { \ 
        return 0;\ 
    }\ 
    for(int i = 0; i < v1->sz; ++i) {\ 
        if(v1->data[i] != v2->data[i]) {\ 
            return 0;\ 
        }\ 
    }\ 
    return 1;\ 
}\ 
\ 
void push_back_vector(vector* v, VECTOR_TYPE val) {\ 
    if(v->sz == v->cap) {\ 
        int ncap = v->cap ? v->cap * 2 : 2;\ 
        VECTOR_TYPE* tmp = (VECTOR_TYPE *)realloc(v->data, sizeof(VECTOR_TYPE) * ncap);\ 
        if(!tmp) {\ 
            return;\ 
        }\ 
        v->data = tmp;\ 
        v->cap = ncap;\ 
    }\ 
    v->data[v->sz++] = val;\ 
}\ 
\
VECTOR_TYPE pop_back_vector(vector* v) { \
    return v->data[--v->sz]; \
} \
\ 
void copy_vector(vector* dest, const vector* src) {\ 
    erase_vector(dest);\ 
    for(int i = 0; i < src->sz; ++i) {\ 
        push_back_vector(dest, src->CopyVoidPtr(src->data[i]));\ 
    }\ 
    dest->CopyVoidPtr = src->CopyVoidPtr;\ 
    dest->DeleteVoidPtr = src->DeleteVoidPtr;\ 
    dest->cap = src->cap;\ 
    dest->sz = src->sz;\ 
}\ 
\ 
vector* copy_vector_new(const vector *src) {\ 
    vector* new = (vector *)malloc(sizeof(vector));\ 
    if(!new) {\ 
        return NULL;\ 
    }\ 
    new->data = new->cap = new->sz = 0;\ 
    copy_vector(new, src);\ 
    return new;\ 
}\ 
\ 
void delete_at_vector(vector* v, size_t ind) {\ 
    if(ind >= v->sz) {\ 
        return;\ 
    }\ 
    v->DeleteVoidPtr(v->data[ind]);\ 
    --v->sz;\ 
    for(; ind < v->sz; ++ind) {\ 
        v->data[ind] = v->data[ind + 1];\ 
    }\ 
}\ 
\ 
VECTOR_TYPE get_at_vector(const vector *v, size_t ind) {\ 
    if(ind >= v->sz) {\ 
        return (VECTOR_TYPE)0;\ 
    }\ 
    return v->data[ind];\ 
}\ 
\ 
void delete_vector(vector* v) {\ 
    erase_vector(v);\ 
    free(v->data);\ 
}\

#endif 
