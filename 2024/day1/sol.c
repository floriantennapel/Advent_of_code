#include <stdio.h>
#include <stdlib.h>
#include "../../datastructure/list.h"

int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }

DECLARE_LIST(List, int)

int main()
{
    int a, b;
    List l1 = List_new(0);
    List l2 = List_new(0);
    while (scanf("%d %d", &a, &b) != EOF) {
        List_push(&l1, a);
        List_push(&l2, b);
    }

    // part 1
    qsort(l1.arr, l1.size, sizeof(int), cmp);
    qsort(l2.arr, l2.size, sizeof(int), cmp);
    long sum = 0;
    for (int i = 0; i < l1.size; i++)
        sum += abs(l1.arr[i] - l2.arr[i]);
    printf("%ld\n", sum);

    // part 2
    int* counter = calloc(100000, sizeof(int));
    for (int i = 0; i < l2.size; i++)
        ++counter[l2.arr[i]];
    sum = 0;
    for (int i = 0; i < l1.size; i++)
        sum += l1.arr[i]*counter[l1.arr[i]];
    printf("%ld\n", sum);

    List_free(&l1);
    List_free(&l2);
    free(counter);
}
