
#include <stdio.h>
#include <limits.h>
#include "s_mem.h"
#include "s_text.h"
#include "s_type.h"
#include "s_bits.h"

#include "exercise.2.6.h"

#define lim 20

int exercise_2_6(void)
{
    int i, c;
    char s[2][lim];
    unsigned long long x[2], y;
    
    for(int j = 0; j < 2; j++)
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
        x[j] = htou(s[j]);
        printf("the unsigned integer is %llu\n", x[j]);
    }

    y = SET_BITS(x[0], 2, 2, x[1]);
    DISPLAY_VAR_MEM_ONE_LINE(y);
    printf("after SET_BITS, result is %llu\n", y);

    return 0;
}






