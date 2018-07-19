
#include <stdio.h>
#include <limits.h>
#include "s_mem.h"
#include "s_text.h"
#include "s_type.h"

#include "exercise.2.2.h"

#define lim 10

int exercise_2_2(void)
{
    int i, c;
    char s[lim];

    /* Exercise 2-2 discusses a for loop from the text. Here it is: */
    /*
    for(i=; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
    s[i] = c;
    */
    
    for(i = 0; i < lim - 1 ? (c = getchar()) != '\n' ? c != EOF:0:0; i++)
    {
        s[i] = c;
    }

    //this version will ignore the '\n'
    
	s[i] ^= s[i];
    DISPLAY_VAR_MEM_MULTI_LINES(s);
    
    printf("%s", s);

    return s[i];
}



