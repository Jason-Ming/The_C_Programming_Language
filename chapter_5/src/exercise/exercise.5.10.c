#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"

#include "exercise.5.10.h"


int exercise_5_10(void)
{
    _S8 *s[] = { "1 2 - 4 5 + *", "1  0 /", "1  0 %",    "-1.0e-2 100 * ", "1 + 1", NULL };
    _SD result = 0.0;
    int i = 0;
    ENUM_RETURN ret_val;
    
    while ( s[i] ) {
        /* Expand and print the next string in our array s[] */
        ret_val = s_calc_rp(s[i], &result);
        printf("expression: %s\n", s[i]);
        if(ret_val == RETURN_SUCCESS)
        {
            printf("result : %g\n", result);
        }
        else
        {
            printf("error!!\n");
        }
        ++i;
    }

    return 0;
}

