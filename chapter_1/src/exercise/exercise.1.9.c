#include <stdio.h>
#include "exercise.1.9.h"

int exercise_1_9_implementation_v1(void)
{
    int c;
    int inspace = 0;

    while((c = getchar()) != EOF)
    {
        if(c == ' ')
        {
            if(inspace ==0)
            {
                putchar(c);
                inspace = 1;
            }
        }

        /* We haven't met 'else' yet, so we have to be a little clumsy */
        if(c != ' ')
        {
            inspace = 0;
            putchar(c);
        }
    }

    return 0;
}

int exercise_1_9_implementation_v2(void)
{
    int c, pc;/* c = charactor, pc = previous charactor */

    /* set pc to a value that wouldn't match any charactor, in case this program is ever modified 
    to get rid of multiples of other charactors */
    pc = EOF;

    while((c = getchar()) != EOF)
    {
        if(c == ' ')
        {
            if(pc != ' ')
            {
                putchar(c);
            }
        }

        /* We haven't met else yet, so we have to be a little clumsy */
        if(c != ' ')
        {
            putchar(c);
        }

        pc = c;
    }

    return 0;
}

int exercise_1_9(void)
{
    int c, last_c = '\0';
    while((c = getchar()) != EOF)
    {
        if(last_c != ' ' || c != ' ')
        {
            putchar(c);
        }
        last_c = c;    
    }

    return 0;
}


