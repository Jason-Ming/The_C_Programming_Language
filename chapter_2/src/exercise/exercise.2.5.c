
#include <stdio.h>
#include <limits.h>
#include "s_mem.h"
#include "s_text.h"
#include "s_type.h"

#include "exercise.2.5.h"

#define lim 20

int exercise_2_5(void)
{
    int i, c;
    char s[2][lim];
    
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
    }

    const char *p = NULL;
    s_any(s[0], s[1], &p);
    DISPLAY_VAR_MEM_MULTI_LINES(s[0]);
    printf("after s_any, p is %s \n", p);

    return 0;
}

