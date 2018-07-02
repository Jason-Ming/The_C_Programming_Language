#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"
#include "s_limits.h"

#include "exercise.4.14.h"

#define my_swap1(t, x, y) do{t x##y = x; x = y; y = x##y; }while(0)
#define my_swap2(t, x, y)\
    do\
    {\
        _U8 * x##temp_p = (_U8 *)&x;\
        _U8 * y##temp_p = (_U8 *)&y;\
        size_t size##x##y = sizeof(x);\
        _U8 x##y##temp;\
        while(size##x##y--)\
        {\
            x##y##temp = *x##temp_p;\
            *x##temp_p = *y##temp_p;\
            *y##temp_p = x##y##temp;\
            x##temp_p++;\
            y##temp_p++;\
        }\
    }while(0)


ENUM_RETURN exercise_4_14(_VOID)
{
    _S8 bufferx[10] = "abcdefg";
    _S8 buffery[10] = "1234567";
    const _S8 *px = "qwerty";
    const _S8 *py = "sweet!";
    _S32 x = 10, y = 20;
    _SD xd = 1.234e-3;
    _SD yd = 3.146;

    printf("bufferx[10]: %s, buffery[10]: %s\n", bufferx, buffery);
    my_swap2(_S8, bufferx, buffery);
    printf("after swap:\n");
    printf("bufferx[10]: %s, buffery[10]: %s\n\n", bufferx, buffery);

    printf("px: %s, py: %s\n", px, py);
    my_swap2(_S8*, px, py);
    printf("after swap:\n");
    printf("px: %s, py: %s\n\n", px, py);

    printf("x: %d, y: %d\n", x, y);
    my_swap2(_S32, x, y);
    printf("after swap:\n");
    printf("x: %d, y: %d\n\n", x, y);

    printf("xd: %g, yd: %g\n", xd, yd);
    my_swap2(_SD, xd, yd);
    printf("after swap:\n");
    printf("xd: %g, yd: %g\n\n", xd, yd);
    
    return 0;
}



