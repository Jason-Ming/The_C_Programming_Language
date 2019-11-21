#include <stdio.h>
#include <time.h>
#include <limits.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"
#include "s_limits.h"

#include "exercise.4.6.h"


ENUM_RETURN exercise_4_6(_VOID)
{
    _S8 buffer[20];
    s_s32tostrbw(S32_MIN, 10, 17, buffer, 20);
    printf("int value: %d\nwidth: %d\nstring: %s\n", S32_MIN, 17, buffer);


    return 0;
}




