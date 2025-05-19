#include <stdio.h>

#include "c_macros/datastructures/vec.h"
#include "c_macros/datastructures/hashmap.h"
#include "c_macros/tuple.h"

TUPLE_DEFINE(Rule, int a, int b)
HASHMAP_DEFINE(Set, Rule, HASHMAP_NO_VALUE, Rule_hasher, Rule_eq)
VEC_DEFINE(IntVec, int)
VEC_DEFINE(LineVec, IntVec)

Set rules;
bool is_ordered(const IntVec* page) 
{
    for (int i = 0; i < page->size-1; i++) {
        for (int j = i+1; j < page->size; j++) {
            int a = page->arr[i], b = page->arr[j];
            if (Set_contains(&rules, &((Rule){b, a})))
                return false;
        }
    }
    return true;
}

int cmp(const void* a, const void* b)
{
    int ai = *(int*)a, bi = *(int*)b;
    if (Set_contains(&rules, &((Rule){ai, bi})))
        return -1;
    else if (Set_contains(&rules, &((Rule){bi, ai})))
        return 1;
    else return 0;
}

int main()
{
    rules = Set_new(0);
    LineVec pages = LineVec_new(0);

    int buf_size = 10000;
    char buf[buf_size];

    int a, b;
    while (fgets(buf, buf_size, stdin) && buf[0] != '\n') {
        sscanf(buf, "%d|%d", &a, &b);
        Set_search(&rules, &((Rule){a, b}), true);
    }
    
    while (fgets(buf, buf_size, stdin)) {
        FILE* stream = fmemopen(buf, buf_size, "r");
        LineVec_push(&pages, IntVec_new(0));
        IntVec* page = pages.arr+pages.size-1;
        while (fscanf(stream, "%d%*[,\n]", &a) == 1)
            IntVec_push(page, a);

        fclose(stream);
    }

    IntVec not_ordered = IntVec_new(0);
    long sum = 0;
    for (int i = 0; i < pages.size; i++) {
        IntVec* page = pages.arr+i;
        if (is_ordered(page))
            sum += page->arr[page->size/2];
        else
            IntVec_push(&not_ordered, i);
    }
    printf("part 1: %ld\n", sum);

    // part 2;
    sum = 0;
    for (int i = 0; i < not_ordered.size; i++) {
        IntVec* page = pages.arr+(not_ordered.arr[i]);
        qsort(page->arr, page->size, sizeof(int), cmp);
        sum += page->arr[page->size/2];
    }
    printf("part 2: %ld\n", sum);
    
    for (int i = 0; i < pages.size; i++)
        IntVec_free(pages.arr+i);
    LineVec_free(&pages);
    IntVec_free(&not_ordered);
    Set_free(&rules);
}
