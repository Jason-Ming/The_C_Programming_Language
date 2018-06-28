#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"
#include "s_limits.h"

#include "exercise.4.5.h"


ENUM_RETURN exercise_4_5(_VOID)
{
    _S8 buffer[10];
    _S32 i;
    for ( i = 2; i <= 36; ++i ) {
    s_s32tostrb(255, i, buffer, 10);
    printf("Decimal 255 in base %-2d : %s\n", i, buffer);
    }

    return 0;
}



