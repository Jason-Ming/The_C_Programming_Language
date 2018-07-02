#include <stdio.h>
#include <time.h>
#include <string.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"
#include "s_limits.h"

#include "exercise.4.13.h"

_VOID my_reverse(_S8 source[], _S32 left, _S32 right)
{
    printf("%d, %c, %d, %c\n", left, source[left], right, source[right]);
    
    if(left >= right)
    {
        return;
    }

    _S8 temp = source[left];
    source[left] = source[right];
    source[right] = temp;

    my_reverse(source, ++left, --right);
}

int exercise_4_13(void)
{
    _S8 source[] = "This a incridable string!";

    printf("string: %s\n", source);
    my_reverse(source, 0, strlen(source) - 1);
    printf("reverse string : %s\n", source);

    return 0;
}


