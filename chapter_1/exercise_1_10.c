#include <stdio.h>

int implementation_v1(void)
{
    int c, d;

    while((c = getchar())!= EOF)
    {
        d = 0;

        if(c == '\\')
        {
            putchar('\\');
            putchar('\\');
            d = 1;
        }

        if(c == '\b')
        {
            putchar('\\');
            putchar('b');
            d = 1;
        }
        
        if(c == '\t')
        {
            putchar('\\');
            putchar('t');
            d = 1;
        }

        if(d == 0)
        {
            putchar(c);
        }
    }
}

int implementation_v2(void)
{
    int c, d;

    while((c = getchar())!= EOF)
    {
        switch(c)
        {
            case '\\':
            {
                putchar('\\');
                putchar('\\');
                break;
            }
            case '\b':/* The OS on which I tested this (NT) intercepts \b characters. */
            {
                putchar('\\');
                putchar('b');
                break;
            }

            case '\t':
            {
                putchar('\\');
                putchar('t');
                break;
            }
            default:
            {
                putchar(c);
                break;
            }
        }
    }
}


#define REPLACE_CHAR(old, c, new) if(old == c){ putchar('\\'); putchar(new); is_special_char = 1;}
int main(void)
{
    int c;
    int is_special_char = 0;
    while((c = getchar()) != EOF)
    {
        is_special_char == 0;
        
        REPLACE_CHAR(c, '\t', 't');
        REPLACE_CHAR(c, '\b', 'b');
        REPLACE_CHAR(c, '\\', '\\');

        if(is_special_char == 0)
        {
            putchar(c);
        }
    }

    return 0;
}

