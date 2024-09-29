#include <stdio.h>

int fuel(int weight)
{
    int f = weight / 3 - 2;
    if (f <= 0) return 0;
    return f + fuel(f);
}

int main()
{
    int n;
    int sum1 = 0;
    int sum2 = 0;

    while (scanf("%d\n", &n) != EOF) {
        sum1 += n / 3 - 2;
        sum2 += fuel(n);
    }

    printf("part1: %d\npart2: %d\n", sum1, sum2);
}
