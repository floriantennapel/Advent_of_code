#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include "list.h"

#define DECLARE_HEAP(HEAP_NAME, HEAP_TYPE, HEAP_COMPARE) \
    DECLARE_LIST(_##HEAP_NAME##List, HEAP_TYPE) \
    \
    typedef struct \
    { \
        _##HEAP_NAME##List arr; \
    } HEAP_NAME; \
    \
    HEAP_NAME HEAP_NAME##_new(long capacity) \
    { \
        return (HEAP_NAME) { _##HEAP_NAME##List_new(capacity) }; \
    } \
    \
    void HEAP_NAME##_free(HEAP_NAME* heap) \
    { \
        if (heap) \
            _##HEAP_NAME##List_free(&(heap->arr)); \
    } \
    \
    int HEAP_NAME##_is_empty(const HEAP_NAME* heap) \
    { \
        if (!heap) { \
            fprintf(stderr, #HEAP_NAME "_is_empty, heap cannot be NULL\n"); \
            exit(1); \
        } \
        return _##HEAP_NAME##List_size(&(heap->arr)) == 0; \
    } \
    \
    const HEAP_TYPE* HEAP_NAME##_peek(const HEAP_NAME* heap) \
    { \
        if (!heap) { \
            fprintf(stderr, #HEAP_NAME "_peek, heap cannot be NULL\n"); \
            exit(1); \
        } \
        return _##HEAP_NAME##List_get(&(heap->arr), 0); \
    } \
    \
    void HEAP_NAME##_push(HEAP_NAME* heap, HEAP_TYPE val) \
    { \
        if (!heap) { \
            fprintf(stderr, #HEAP_NAME "_push, heap cannot be NULL\n"); \
            exit(1); \
        } \
        \
        _##HEAP_NAME##List_push(&(heap->arr), val); \
        \
        size_t ind = _##HEAP_NAME##List_size(&(heap->arr)) - 1; \
        while (ind > 0) { \
            size_t parent_ind = (ind - 1) / 2; \
            HEAP_TYPE* current =  _##HEAP_NAME##List_get(&(heap->arr), ind); \
            HEAP_TYPE* parent =  _##HEAP_NAME##List_get(&(heap->arr), parent_ind); \
            if (HEAP_COMPARE(current, parent) >= 0) \
                break; \
            \
            HEAP_TYPE tmp = *current; \
            *current = *parent; \
            *parent = tmp; \
            ind = parent_ind; \
        } \
    } \
    \
    HEAP_TYPE HEAP_NAME##_pop(HEAP_NAME* heap) \
    { \
        if (!heap) { \
            fprintf(stderr, #HEAP_NAME "_pop, heap cannot be NULL\n"); \
            exit(1); \
        } \
        size_t size = _##HEAP_NAME##List_size(&(heap->arr)); \
        if (size == 0) { \
            fprintf(stderr, #HEAP_NAME "_pop, heap is empty\n"); \
            exit(1); \
        } \
        \
        HEAP_TYPE ret = *_##HEAP_NAME##List_get(&(heap->arr), 0); \
        HEAP_TYPE last = _##HEAP_NAME##List_pop(&(heap->arr)); \
        --size; \
        if (!size) { \
            return ret; \
        } \
        \
        _##HEAP_NAME##List_set(&(heap->arr), last, 0); \
        \
        size_t ind = 0; \
        size_t c1_ind; \
        while ((c1_ind = ind*2 + 1) < size) { \
            HEAP_TYPE* current = (HEAP_TYPE*) _##HEAP_NAME##List_get(&(heap->arr), ind); \
            HEAP_TYPE* min = (HEAP_TYPE*) _##HEAP_NAME##List_get(&(heap->arr), c1_ind); \
            size_t min_ind = c1_ind; \
            \
            if (c1_ind + 1 < size) { \
                HEAP_TYPE* c2 = (HEAP_TYPE*) _##HEAP_NAME##List_get(&(heap->arr), c1_ind+1); \
                if (HEAP_COMPARE(c2, min) < 0) { \
                    min = c2; \
                    ++min_ind; \
                } \
            } \
            \
            if (HEAP_COMPARE(min, current) > 0) \
                break; \
            \
            HEAP_TYPE tmp = *current; \
            *current = *min; \
            *min = tmp; \
            ind = min_ind; \
        } \
        return ret; \
    }
    
#endif
