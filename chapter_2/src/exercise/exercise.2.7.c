
#include <stdio.h>
#include <limits.h>
#include "s_mem.h"
#include "s_text.h"
#include "s_type.h"

#include "exercise.2.7.h"

#define lim 20

int exercise_2_7(void)
{
    int i, c;
    char s[lim];
    unsigned long long x, y;
    int p, n;
    
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

    printf("input p and n:\n");
    scanf("%d%d", &p, &n);

    y = INVERT_BITS(x, p, n);
    
    printf("after INVERT_BITS(%llu, %d, %d), result is %llu\n", x, p, n, y);
    DISPLAY_VAR_MEM_ONE_LINE(y);

    return 0;
}







