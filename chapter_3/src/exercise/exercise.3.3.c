#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"

#include "exercise.3.3.h"


int exercise_3_3(void)
{
    _S8 *s[] = { "a-z-", "z-a-", "-1-6-",    "a-ee-a", "a-R-L", "1-9-1",    "5-5", NULL };
    _S8 result[100];
    int i = 0;
    while ( s[i] ) {
        /* Expand and print the next string in our array s[] */
        s_expand(s[i], result, 100);
        printf("Unexpanded: %s\n", s[i]);
        printf("Expanded : %s\n", result);
        ++i;
    }

    return 0;
}

