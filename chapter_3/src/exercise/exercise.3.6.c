#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"
#include "s_limits.h"

#include "exercise.3.6.h"


ENUM_RETURN exercise_3_6(_VOID)
{
    _S8 buffer[20];
    s_s32tostrbw(S32_MIN, 10, 7, buffer, 20);
    printf("Buffer:%s\n", buffer);


    return 0;
}




