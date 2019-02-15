#include <stdio.h>
#include "1.5.3.h"

int main_1_5_3(void)
{
    long nc, c_n, c_r;
    int c;
    nc = 0;
    c_n = 0;
    c_r = 0;

    printf("type some charactors, CTRL+D to exit and diplay the count of charactors and lines\n");
    
    while((c = getchar()) != EOF)
    {
        if(c == '\n')
        {
            ++c_n;
        }

        if(c == '\r')
        {
            ++c_r;
        }
        
        ++nc;
    }

    printf("%ld, %ld, %ld\n", nc, c_n, c_r);

    return 0;
}


