#include <stdio.h>

/* power: raise base to n-th power; n >= 0 */
int power_1_8(int base, int n)
{
    int p;
    
    for(p = 1; n > 0; n--)
    {
        p = p * base;
    }
    return p;
}
int main_1_8(void)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        printf("%d %d %d\n", i, power_1_8(2, i), power_1_8(-3, i));
    }
    return 0;
}


