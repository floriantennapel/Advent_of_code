#include <stdio.h>
#include <stdbool.h>

#include "c_macros/datastructures/vec.h"

VEC_DEFINE(NumsVec, long)
VEC_DEFINE(LinesVec, NumsVec)

bool valid_data(const NumsVec* data, int skip)
{
    if (data->size - (skip >= 0) <= 1) 
        return true;
    
    bool inc;
    if (skip == 0)
        inc = data->arr[1] < data->arr[2];
    else if (skip == 1)
        inc = data->arr[0] < data->arr[2];
    else
        inc = data->arr[0] < data->arr[1];

    for (int i = 0; i < data->size-1; i++) {
        if (i == skip)
            continue;

        int next = i+1;
        if (i+1 == skip) {
            if (i+1 == data->size-1)
                break;
            next = i+2;
        }

        long diff = data->arr[next] - data->arr[i];
        if (inc && (diff < 1 || diff > 3))
            return false;
        if (!inc && (diff > -1 || diff < -3))
            return false;
    }
    return true;
}

int main()
{
    int line_len = 10000;
    char buf[line_len];
    long d;
    LinesVec lines = LinesVec_new(0);
    while (fgets(buf, line_len, stdin)) {
        FILE* string_stream = fmemopen(buf, line_len, "r");
        LinesVec_push(&lines, NumsVec_new(0));
        NumsVec* nums = lines.arr+lines.size-1;
        while (fscanf(string_stream, "%ld", &d) == 1) {
            NumsVec_push(nums, d); 
        }
        fclose(string_stream);
    }

    int counter = 0;
    for (int i = 0; i < lines.size; i++)
        counter += valid_data(lines.arr+i, -1);
    printf("part 1: %d\n", counter);


    //part 2
    counter = 0;
    for (int i = 0; i < lines.size; i++) {
        if (valid_data(lines.arr+i, -1)) {
            counter++;
            continue;
        }
        for (int j = 0; j < (lines.arr+i)->size; j++) {
            if (valid_data(lines.arr+i, j)) {
                counter++;
                break;
            }
        }
    }
    printf("part 2: %d\n", counter);

    for (int i = 0; i < lines.size; i++)
        NumsVec_free(lines.arr+i);
    LinesVec_free(&lines);
}
