#include <stdlib.h>
#include <stdio.h>

#include "c_macros/datastructures/vec.h"
#include "c_macros/datastructures/hashmap.h"

#define ABS(digit) ((digit) < 0 ? -(digit) : (digit)) 
#define LONG_HASH(val) ((size_t)*(val)) 
#define LONG_EQ(a, b) (*(a) == *(b))

VEC_DEFINE(Vec, long)
HASHMAP_DEFINE(Map, long, int, LONG_HASH, LONG_EQ)

int cmp(const void* a, const void* b) {
    return *(long*)a - *(long*)b; 
}

int main() {
    Vec col_a = Vec_new(0);
    Vec col_b = Vec_new(0);
    Map b_counter = Map_new(0);
    long d;
    while (scanf("%ld", &d) != EOF) {
        Vec_push(&col_a, d);
        scanf("%ld", &d);
        Vec_push(&col_b, d);
        (Map_search(&b_counter, &d, true)->value)++;
    }
    int n = col_a.size;
    qsort(col_a.arr, n, sizeof(long), cmp);
    qsort(col_b.arr, n, sizeof(long), cmp);

    long sum = 0;
    for (int i = 0; i < n; i++)
        sum += ABS(col_a.arr[i] - col_b.arr[i]); 
    printf("part 1: %ld\n", sum);

    //part 2
    sum = 0;
    for (int i = 0; i < n; i++) {
        int count = Map_search(&b_counter, col_a.arr+i, true)->value; 
        sum += count*col_a.arr[i];
    }
    printf("part 2: %ld\n", sum); 

    Map_free(&b_counter); 
    Vec_free(&col_a);
    Vec_free(&col_b);
}
