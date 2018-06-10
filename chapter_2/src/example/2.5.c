#include <stdio.h>
#include "s_mem.h"
#include "2.5.h"

int main_2_5(void)
{
    int year;
    printf("input year:\n");
    scanf("%d", &year);

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        printf("%d is a leap year\n", year); 
    }
    else
    {
        printf("%d is not a leap year\n", year); 
    }
    
    return 0;
}

