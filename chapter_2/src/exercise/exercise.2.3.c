
#include <stdio.h>
#include <limits.h>
#include "s_mem.h"
#include "s_text.h"
#include "s_type.h"
#include "s_log.h"

#include "exercise.2.3.h"

#define lim 20

ENUM_RETURN exercise_2_3(_VOID)
{
    _S32 i, c;
    _S8 s[lim];

    printf("input a string:\n");
    
    for(i = 0; i < lim - 1 ? (c = getchar()) != '\n' ? c != EOF:0:0; i++)
    {
        s[i] = c;
    }

    //this version will ignore the '\n'
    
	s[i] ^= s[i];
    DISPLAY_VAR_MEM_MULTI_LINES(s);
    
    printf("the string is %s\n", s);

    _U64 value = 0;
    _S64 value1 = 0;
    
    ENUM_RETURN retval = s_htou(s, &value);
    R_ASSERT(retval == RETURN_SUCCESS, RETURN_FAILURE);
    
    printf("the unsigned integer is %llu\n", value);

    retval = s_htoi(s, &value1);
    R_ASSERT(retval == RETURN_SUCCESS, RETURN_FAILURE);
    printf("the integer is %lld\n", value1);
    
    return RETURN_SUCCESS;
}




