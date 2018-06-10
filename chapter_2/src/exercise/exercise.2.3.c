
#include <stdio.h>
#include <limits.h>
#include "s_mem.h"
#include "s_text.h"
#include "s_type.h"

#include "exercise.2.3.h"

#define lim 20

int exercise_2_3(void)
{
    int i, c;
    char s[lim];

    printf("input a string:\n");
    
    for(i = 0; i < lim - 1 ? (c = getchar()) != '\n' ? c != EOF:0:0; i++)
    {
        s[i] = c;
    }

    //this version will ignore the '\n'
    
	s[i] ^= s[i];
    DISPLAY_VAR_MEM_MULTI_LINES(s);
    
    printf("the string is %s\n", s);

    printf("the unsigned integer is %llu\n", htou(s));
    printf("the integer is %lld\n", htoi(s));
    return 0;
}




