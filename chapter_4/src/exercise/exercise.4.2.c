
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

        //%g�������ʵ������������ֵ�Ĵ�С���Զ�ѡf��ʽ��e��ʽ��ѡ�����ʱռ��Ƚ�С��һ�֣����Ҳ�����������0
        printf("s_strtosd(%s) = %g\n", strings[i], temp);
    }


    return 0;
}



