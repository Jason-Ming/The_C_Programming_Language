#include <stdio.h>

int main_1_5_3(void)
{
    long nc, c_n, c_r;
    int c;
    nc = 0;
    c_n = 0;
    c_r = 0;
    
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


