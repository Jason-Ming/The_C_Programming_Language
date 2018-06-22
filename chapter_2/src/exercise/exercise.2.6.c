
#include <stdio.h>
#include <limits.h>
#include "s_mem.h"
#include "s_text.h"
#include "s_type.h"
#include "s_bits.h"
#include "s_log.h"

#include "exercise.2.6.h"

#define lim 20

ENUM_RETURN exercise_2_6(_VOID)
{
    _S32 i, c;
    _S8 s[2][lim];
    _U64 x[2], y;
    ENUM_RETURN retval = RETURN_SUCCESS;
    
    for(_S32 j = 0; j < 2; j++)
    {
        printf("input string%d:\n", j);
        
        for(i = 0; i < lim - 1 ? (c = getchar()) != '\n' ? c != EOF:0:0; i++)
        {
            s[j][i] = c;
        }

        //this version will ignore the '\n'
        
    	s[j][i] ^= s[j][i];
        DISPLAY_VAR_MEM_MULTI_LINES(s[j]);
        
        printf("the string%d is %s\n", j, s[j]);

        retval = s_htou(s[j], &(x[j]));
        R_ASSERT(retval == RETURN_SUCCESS, RETURN_FAILURE);
        
        printf("the unsigned integer is %llu\n", x[j]);
    }

    y = SET_BITS(x[0], 2, 2, x[1]);
    DISPLAY_VAR_MEM_ONE_LINE(y);
    printf("after SET_BITS, result is %llu\n", y);

    return RETURN_SUCCESS;
}






