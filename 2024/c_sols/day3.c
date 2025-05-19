#include <regex.h>
#include <stdio.h>
#include <stdbool.h>

#include "c_macros/datastructures/vec.h"

VEC_DEFINE(String, char)

int main()
{
    const char* mul_regex_str = R"(mul\((-?[0-9]{1,3}),(-?[0-9]{1,3})\))";
    regex_t re; 
    regcomp(&re, mul_regex_str, REG_EXTENDED);

    String input = String_new(0);
    char c;
    while ((c = getchar()) != EOF) {
        if (c == '\n')
            continue;
        String_push(&input, c);
    } 
    String_push(&input, '\0');
    char* str = input.arr;

    long sum = 0;
    long a, b;
    regmatch_t matches[3];
    while (regexec(&re, str, 3, matches, 0) != REG_NOMATCH) {
        sscanf(str+matches[1].rm_so, "%ld", &a);
        sscanf(str+matches[2].rm_so, "%ld", &b);
        sum += a*b;
        str += matches[0].rm_eo;
    }
    printf("part 1: %ld\n", sum);
    regfree(&re);

    //part 2
    const char* p2_re_str = R"(mul\((-?[0-9]{1,3}),(-?[0-9]{1,3})\)|do(n't)?\(\))";
    regcomp(&re, p2_re_str, REG_EXTENDED);

    str = input.arr;
    bool on = true;
    sum = 0;
    while (regexec(&re, str, 3, matches, 0) != REG_NOMATCH) {
        if (*(str+matches[0].rm_so) == 'd')
            on = (*(str+matches[0].rm_so+2) == '(');
        else if (on) {
            sscanf(str+matches[1].rm_so, "%ld", &a);
            sscanf(str+matches[2].rm_so, "%ld", &b);
            sum += a*b;
        }
        str += matches[0].rm_eo;
    }
    printf("part 2: %ld\n", sum);

    regfree(&re);
    String_free(&input);
}
