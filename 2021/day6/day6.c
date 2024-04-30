#include <stdio.h>
#include <string.h>

#define MAX_DAYS 300

int fishes[] = {3,5,1,5,3,2,1,3,4,2,5,1,3,3,2,5,1,3,1,5,5,1,1,1,2,4,1,4,5,2,1,2,4,3,1,2,3,4,3,4,4,5,1,1,1,1,5,5,3,4,4,4,5,3,4,1,4,3,3,2,1,1,3,3,3,2,1,3,5,2,3,4,2,5,4,5,4,4,2,2,3,3,3,3,5,4,2,3,1,2,1,1,2,2,5,1,1,4,1,5,3,2,1,4,1,5,1,4,5,2,1,1,1,4,5,4,2,4,5,4,2,4,4,1,1,2,2,1,1,2,3,3,2,5,2,1,1,2,1,1,1,3,2,3,1,5,4,5,3,3,2,1,1,1,3,5,1,1,4,4,5,4,3,3,3,3,2,4,5,2,1,1,1,4,2,4,2,2,5,5,5,4,1,1,5,1,5,2,1,3,3,2,5,2,1,2,4,3,3,1,5,4,1,1,1,4,2,5,5,4,4,3,4,3,1,5,5,2,5,4,2,3,4,1,1,4,4,3,4,1,3,4,1,1,4,3,2,2,5,3,1,4,4,4,1,3,4,3,1,5,3,3,5,5,4,4,1,2,4,2,2,3,1,1,4,5,3,1,1,1,1,3,5,4,1,1,2,1,1,2,1,2,3,1,1,3,2,2,5,5,1,5,5,1,4,4,3,5,4,4};
long memo[MAX_DAYS][9];

long numberOfLanternfish(int daysLeft, int daysToRepr) {
    if (memo[daysLeft][daysToRepr] != -1) {
        return memo[daysLeft][daysToRepr];
    }

    long sum = 1;

    int r = daysToRepr;
    for (int i = daysLeft; i > 0; i--) {
        if (r == 0) {
            sum += numberOfLanternfish(i - 1, 8);
            r = 6;
        } else {
            --r;
        }
    }

    memo[daysLeft][daysToRepr] = sum;
    return sum;
}


long solve(int days) {
    long sum = 0;
    int inputLength = sizeof(fishes) / sizeof(fishes[0]);

    for (int i = 0; i < inputLength; i++) {
        sum += numberOfLanternfish(days, fishes[i]);
    }

    return sum;
}

int main() {
    for (int i = 0; i < MAX_DAYS; i++) {
        memset(memo[i], -1, 9 * sizeof(long));
    }

    printf("part 1: %ld\n", solve(80));
    printf("part 2: %ld\n", solve(256));

    return 0;
}
