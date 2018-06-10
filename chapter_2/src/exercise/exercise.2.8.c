
#include <stdio.h>
#include <limits.h>
#include "s_mem.h"
#include "s_text.h"
#include "s_type.h"

#include "exercise.2.8.h"

#define lim 20

int exercise_2_8(void)
{
    int i, c;
    char s[lim];
    unsigned long long x, y;
    int n;
    
    printf("input string:\n");
    
    for(i = 0; i < lim - 1 ? (c = getchar()) != '\n' ? c != EOF:0:0; i++)
    {
        s[i] = c;
    }

    //this version will ignore the '\n'
    
	s[i] ^= s[i];
    DISPLAY_VAR_MEM_MULTI_LINES(s);
    
    printf("the string is %s\n", s);
    
    x = htou(s);
    printf("the unsigned integer is %llu\n", x);
    DISPLAY_VAR_MEM_ONE_LINE(x);

    printf("input n:\n");
    scanf("%d", &n);

    y = RIGHT_ROT(x, n);
    
    printf("after RIGHT_ROT(%llu, %d), result is %llu\n", x, n, y);
    DISPLAY_VAR_MEM_ONE_LINE(y);

    return 0;
}








