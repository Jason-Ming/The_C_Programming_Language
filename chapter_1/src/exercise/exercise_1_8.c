#include <stdio.h>

/* count charactors in input; 2nd version */
#define COUNT_CHAR(v, c, l) if(v == c){++l;}

int exercise_1_8()
{
    int c, last_c;
    double number_charactor, number_tab = 0, number_blank = 0, number_newline = 0;
    number_charactor = 0;
    for(number_charactor = 0; (c = getchar()) != EOF; ++number_charactor)
    {
        COUNT_CHAR(c, '\t', number_tab);
        COUNT_CHAR(c, ' ', number_blank);
        COUNT_CHAR(c, '\n', number_newline);
        last_c = c;
    }
    
    /* this is a bit of a semantic stretch, but it copes
    * with implementations where a text file might not
    * end with a newline. Thanks to Jim Stad for pointing
    * this out.
    */
    if(last_c != '\n')
    {
        ++number_newline;
    }

    printf("Charactors: %.0f\nTabs: %0.f\nBlanks: %0.f\nNewlines: %0.f\n", number_charactor, number_tab, number_blank, number_newline);

    return 0;
}

