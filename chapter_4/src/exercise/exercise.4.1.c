
#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"

#include "exercise.4.1.h"
typedef struct TEST
{
const char *			data;
const char*		testchar;
int 			expected;
} TEST;


int exercise_4_1(void)
{

	TEST			test[] =
	{
		{
			"Hello world", "o", 7
		},
		{
			"This string is littered with iiiis", "i", 32
		},
		{
			"No 'see' letters in here", "c", -1
		}
	};


	size_t			numtests = sizeof test / sizeof test[0];
	size_t			i;
	int 			pos;

    ENUM_RETURN ret_val;
    
	for (i = 0; i < numtests; i++)
	{
		ret_val 				= s_strrindex(test[i].data, test[i].testchar, &pos);
        if(ret_val == RETURN_FAILURE)
        {
            printf("s_strrindex failed!\n");
            continue;
        }
        
		printf("Searching %s for last occurrence of %s.\n", 
			test[i].data, 
			test[i].testchar);
		printf("Expected result: %d\n", test[i].expected);
		printf("%sorrect (%d).\n", pos == test[i].expected ? "C": "Inc", pos);

		if (pos != -1)
		{
			printf("Character found was %c\n", test[i].data[pos]);
		}
	}

	return 0;

}


