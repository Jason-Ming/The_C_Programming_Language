
#include <stdio.h>
#include <limits.h>
#include "s_mem.h"
#include "s_text.h"
#include "s_type.h"
#include "s_bits.h"
#include "s_log.h"

#include "exercise.2.9.h"

#define lim 20

ENUM_RETURN exercise_2_9(_VOID)
{
    _S32 i, c;
    _S8 s[lim];
    _U64 x, y;
    ENUM_RETURN retval;
    
    printf("input string:\n");
    
    for(i = 0; i < lim - 1 ? (c = getchar()) != '\n' ? c != EOF:0:0; i++)
    {
        s[i] = c;
    }

    //this version will ignore the '\n'
    
	s[i] ^= s[i];
    DISPLAY_VAR_MEM_MULTI_LINES(s);
    
    printf("the string is %s\n", s);

    
    retval = s_htou(s, &x);
    R_ASSERT(retval == RETURN_SUCCESS, RETURN_FAILURE);

    printf("the unsigned integer is %llu\n", x);
    DISPLAY_VAR_MEM_ONE_LINE(x);

    y = bits_count(x);
    
    printf("after bits_count(%llu), result is %llu\n", x, y);
    DISPLAY_VAR_MEM_ONE_LINE(y);

    return 0;
}









