#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"
#include "s_limits.h"

#include "exercise.3.4.h"


int exercise_3_4(void)
{
    _S32 value[] = { 0, -37246, 453898, S32_MAX, S32_MIN};
    _S8 result[100];
    _S32 i = 0;
    for(i = 0; i < SIZE_OF_ARRAY(value); i++)
    {
        /* Expand and print the next string in our array s[] */
        s_s32tostr(value[i], result, 100);
        printf("value: %d\n", value[i]);
        printf("string : %s\n", result);
    }

    return 0;
}


