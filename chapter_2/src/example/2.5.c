#include <stdio.h>
#include "s_time.h"
#include "2.5.h"

ENUM_RETURN main_2_5(_VOID)
{
    _U32 year;
    printf("input year:\n");
    scanf("%u", &year);

    if (is_leapyear(year) == BOOLEAN_TRUE)
    {
        printf("%d is a leap year\n", year); 
    }
    else
    {
        printf("%d is not a leap year\n", year); 
    }
    
    return RETURN_SUCCESS;
}

