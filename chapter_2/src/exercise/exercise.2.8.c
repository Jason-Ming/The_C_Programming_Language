
#include <stdio.h>
#include <limits.h>
#include "s_mem.h"
#include "s_text.h"
#include "s_type.h"
#include "s_bits.h"
#include "s_log.h"

#include "exercise.2.8.h"

#define lim 20

ENUM_RETURN exercise_2_8(_VOID)
{
    _S32 i, c;
    _S8 s[lim];
    _U64 x, y;
    _S32 n;
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
    
    retval = s_hstrtou64(s, &x);
    R_ASSERT(retval == RETURN_SUCCESS, RETURN_FAILURE);
    printf("the unsigned integer is %llu\n", x);
    DISPLAY_VAR_MEM_ONE_LINE(x);

    printf("input n:\n");
    scanf("%d", &n);

    y = RIGHT_ROT(x, n);
    
    printf("after RIGHT_ROT(%llu, %d), result is %llu\n", x, n, y);
    DISPLAY_VAR_MEM_ONE_LINE(y);

    return RETURN_SUCCESS;
}








