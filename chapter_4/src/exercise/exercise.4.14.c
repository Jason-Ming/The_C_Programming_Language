#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"
#include "s_limits.h"
#include "s_mem.h"

#include "exercise.4.14.h"

#define my_swap1(t, x, y) do{t x##y = x; x = y; y = x##y; }while(0)

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
    SWAP(bufferx, buffery);
    printf("after swap:\n");
    printf("bufferx[10]: %s, buffery[10]: %s\n\n", bufferx, buffery);

    printf("px: %s, py: %s\n", px, py);
    SWAP(px, py);
    printf("after swap:\n");
    printf("px: %s, py: %s\n\n", px, py);

    printf("x: %d, y: %d\n", x, y);
    SWAP(x, y);
    printf("after swap:\n");
    printf("x: %d, y: %d\n\n", x, y);

    printf("xd: %g, yd: %g\n", xd, yd);
    SWAP(xd, yd);
    printf("after swap:\n");
    printf("xd: %g, yd: %g\n\n", xd, yd);
    
    return 0;
}



