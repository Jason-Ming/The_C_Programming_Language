#include <stdio.h>
#include "1.5.1.h"

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

int main_1_5_1(void)
{
    printf("type some charactors, CTRL+D to exit\n");
    copy_input_to_output1();

    return 0;
}

