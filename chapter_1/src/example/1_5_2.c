#include <stdio.h>
/* count charactors in input; 1st version */
void count_charactors_in_input_v1()
{
    long nc;
    nc = 0;
    while(getchar() != EOF)
    {
        ++nc;
    }

    printf("%ld\n", nc);
}

/* count charactors in input; 2nd version */
void count_charactors_in_input_v2()
{
    double nc;
    nc = 0;
    for(nc = 0; getchar() != EOF; ++nc)
    {
    }

    printf("%.0f\n", nc);
}

int main_1_5_2(void)
{
    count_charactors_in_input_v2();
    return 0;
}

