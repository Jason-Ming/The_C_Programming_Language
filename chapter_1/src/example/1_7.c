#include <stdio.h>

/* power: raise base to n-th power; n >= 0 */
int power_1_7(int base, int n)
{
    int i;
    int p;
    p = 1;
    for(i = 1; i <= n; i++)
    {
        p = p * base;
    }
    return p;
}
int main_1_7(void)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("%d %d %d\n", i, power_1_7(2, i), power_1_7(-3, i));
    }
    return 0;
}

