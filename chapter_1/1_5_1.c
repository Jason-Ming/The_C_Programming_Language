#include <stdio.h>

void copy_input_to_output1()
{
    /* copy input to output */
    int c;
    c = getchar();
    while(c != EOF)
    {
        putchar(c);
        c = getchar();
    };
}

void copy_input_to_output2()
{
    /* copy input to output */
    int c;
    while((c = getchar()) != EOF)
    {
        putchar(c);
    };
}

void main()
{
    copy_input_to_output1();
    
}

