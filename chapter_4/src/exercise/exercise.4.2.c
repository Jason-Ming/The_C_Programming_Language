
#include <stdio.h>
#include <time.h>

#include "s_alg.h"
#include "s_mem.h"

#include "s_type.h"
#include "s_text.h"

#include "exercise.4.2.h"

char *strings[] = {
"1.0e43",
"999.999",
"123.456e-9",
"-1.2e-3",
"1.2e-3",
"-1.2E3",
"-1.2e03",
"cat",
"",0};

int exercise_4_2(void)
{
    int i = 0;
    _SD temp;
    ENUM_RETURN ret_val;

    for(; i < SIZE_OF_ARRAY(strings); i++)
    {
        ret_val = s_strtosd(strings[i], &temp);
        if(ret_val == RETURN_FAILURE)
        {
            printf("s_strtosd(%s) is failed!\n", strings[i]);
            continue;
        }

        //%g用来输出实数，它根据数值的大小，自动选f格式或e格式（选择输出时占宽度较小的一种），且不输出无意义的0
        printf("s_strtosd(%s) = %g\n", strings[i], temp);
    }


    return 0;
}



