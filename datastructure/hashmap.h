#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <stdio.h>

#ifndef HASHMAP_LOAD_FACTOR
#define HASHMAP_LOAD_FACTOR 0.75
#endif

#define DECLARE_HASHMAP(HASHMAP_NAME, HASHMAP_KEYTYPE, HASHMAP_VALTYPE, HASHMAP_KEY_EQ, HASHMAP_HASH) \
    typedef struct _##HASHMAP_NAME##Entry \
    { \
        HASHMAP_KEYTYPE key; \
        HASHMAP_VALTYPE value; \
        struct _##HASHMAP_NAME##Entry* next; \
    } _##HASHMAP_NAME##Entry; \
    \
    typedef struct \
    { \
        size_t capacity; \
        size_t size; \
        _##HASHMAP_NAME##Entry** arr; \
    } HASHMAP_NAME; \
    \
    HASHMAP_NAME HASHMAP_NAME##_new(long initial_capacity) \
    { \
        long capacity; \
        for (capacity = 16; capacity < initial_capacity; capacity <<= 1) {} \
        HASHMAP_NAME ret = { .capacity = capacity, .size = 0 }; \
        if (!(ret.arr = calloc(capacity, sizeof(void*)))) { \
            perror(#HASHMAP_NAME "_new, calloc"); \
            exit(1); \
        } \
        return ret; \
    } \
    \
    void _##HASHMAP_NAME##_free_ll(_##HASHMAP_NAME##Entry* e) \
    { \
        if (!e) return; \
        _##HASHMAP_NAME##_free_ll(e->next); \
        free(e); \
    } \
    \
    void HASHMAP_NAME##_free(HASHMAP_NAME* map) \
    { \
        if (!map || !map->arr) return; \
        for (size_t i = 0; i < map->capacity; i++) \
             _##HASHMAP_NAME##_free_ll(map->arr[i]); \
        free(map->arr); \
        map->arr = NULL; \
    } \
    \
    _##HASHMAP_NAME##Entry* _##HASHMAP_NAME##_get_entry(const HASHMAP_NAME* map, const HASHMAP_KEYTYPE* key) \
    { \
        size_t ind = HASHMAP_HASH(key) % map->capacity; \
        _##HASHMAP_NAME##Entry* current; \
        for (current = map->arr[ind]; current; current = current->next) \
            if (HASHMAP_KEY_EQ(&(current->key), key)) break; \
        return current; \
    } \
    \
    int HASHMAP_NAME##_contains_key(const HASHMAP_NAME* map, const HASHMAP_KEYTYPE* key) \
    { \
        if (!map) { \
            fprintf(stderr, #HASHMAP_NAME "_contains_key, map cannot be NULL\n"); \
            exit(1); \
        } \
        return _##HASHMAP_NAME##_get_entry(map, key) != NULL; \
    } \
    \
    void _##HASHMAP_NAME##_grow(HASHMAP_NAME* map) \
    { \
        size_t old_capacity = map->capacity; \
        map->capacity *= 2; \
        \
        _##HASHMAP_NAME##Entry** new_arr = calloc(map->capacity, sizeof(void*)); \
        if (!new_arr) { \
            perror("_" #HASHMAP_NAME "_grow, calloc"); \
            exit(1); \
        } \
        \
        for (size_t i = 0; i < old_capacity; i++) { \
            _##HASHMAP_NAME##Entry* current = map->arr[i]; \
            while (current) { \
                _##HASHMAP_NAME##Entry* next = current->next; \
                size_t hash_ind = HASHMAP_HASH(&(current->key)) % map->capacity; \
                current->next = new_arr[hash_ind]; \
                new_arr[hash_ind] = current; \
                current = next; \
            } \
        } \
        \
        free(map->arr); \
        map->arr = new_arr; \
    } \
    \
    void HASHMAP_NAME##_insert(HASHMAP_NAME* map, HASHMAP_KEYTYPE key, HASHMAP_VALTYPE value) \
    { \
        if (!map) { \
            fprintf(stderr, #HASHMAP_NAME "_insert, map cannot be NULL\n"); \
            exit(1); \
        } \
        size_t ind = HASHMAP_HASH(&key) % map->capacity; \
        _##HASHMAP_NAME##Entry** prev = map->arr + ind; \
        _##HASHMAP_NAME##Entry* current; \
        while ((current = *prev)) { \
            if (HASHMAP_KEY_EQ(&current->key, &key)) { \
                current->value = value; \
                return; \
            } \
            prev = &((*prev)->next); \
        } \
        \
        _##HASHMAP_NAME##Entry* new_entry; \
        if (!(new_entry = malloc(sizeof(_##HASHMAP_NAME##Entry)))) { \
            perror(#HASHMAP_NAME "_insert, malloc"); \
            exit(1); \
        } \
        *new_entry = (_##HASHMAP_NAME##Entry) { .key = key, .value = value, .next = NULL }; \
        *prev = new_entry; \
        ++(map->size); \
        \
        if (map->size > HASHMAP_LOAD_FACTOR * map->capacity) \
            _##HASHMAP_NAME##_grow(map); \
    } \
    \
    HASHMAP_VALTYPE* HASHMAP_NAME##_get(const HASHMAP_NAME* map, const HASHMAP_KEYTYPE* key) \
    { \
        if (!map) { \
            fprintf(stderr, #HASHMAP_NAME "_get, map cannot be NULL\n"); \
            exit(1); \
        } \
        \
        _##HASHMAP_NAME##Entry* entry = _##HASHMAP_NAME##_get_entry(map, key); \
        if (!entry) \
            return NULL; \
        else \
            return &(entry->value); \
    } \
    \
    void HASHMAP_NAME##_all_keys(const HASHMAP_NAME* map, const HASHMAP_KEYTYPE** arr) \
    { \
        if (!map) { \
            fprintf(stderr, #HASHMAP_NAME "_all_keys, map cannot be NULL\n"); \
            exit(1); \
        } \
        if (!arr) { \
            fprintf(stderr, #HASHMAP_NAME "_all_keys, arr cannot be NULL\n"); \
            exit(1); \
        } \
        size_t ind = 0; \
        for (size_t i = 0; i < map->capacity; i++) { \
            _##HASHMAP_NAME##Entry* current = map->arr[i]; \
            while (current) { \
                arr[ind++] = &(current->key); \
                current = current->next; \
            } \
        } \
    } \
    \
    void HASHMAP_NAME##_remove(HASHMAP_NAME* map, const HASHMAP_KEYTYPE* key) \
    { \
        if (!map) { \
            fprintf(stderr, #HASHMAP_NAME "_remove, map cannot be NULL\n"); \
            exit(1); \
        } \
        size_t ind = HASHMAP_HASH(key) % map->capacity; \
        _##HASHMAP_NAME##Entry** prev = map->arr + ind; \
        _##HASHMAP_NAME##Entry* current; \
        while ((current = *prev)) { \
            if (HASHMAP_KEY_EQ(&(current->key), key)) { \
                *prev = current->next; \
                free(current); \
                --(map->size); \
                return; \
            } \
            prev = &((*prev)->next); \
        } \
    }

        


#endif
