
#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"

#include "exercise.5.4.h"

int exercise_5_4(void)
{
	
	char *			s1 = "some really long string.";
	char *			s2 = "ng.";
	char *			s3 = "ng";

    ENUM_RETURN ret_val;
    ENUM_BOOLEAN whether_any_charactor_occured;
	if ((ret_val = s_strend(s1, s2, &whether_any_charactor_occured)) == RETURN_SUCCESS && whether_any_charactor_occured == BOOLEAN_TRUE)
	{
		printf("The string (%s) has (%s) at the end.\n", s1, s2);
	}
	
	
	else 
	{
		printf("The string (%s) doesn't have (%s) at the end.\n", s1, s2);
	}
	
	
	if ((ret_val = s_strend(s1, s3, &whether_any_charactor_occured)) == RETURN_SUCCESS && whether_any_charactor_occured == BOOLEAN_TRUE)
	{
		printf("The string (%s) has (%s) at the end.\n", s1, s3);
	}
	
	
	else 
	{
		printf("The string (%s) doesn't have (%s) at the end.\n", s1, s3);
	}
	
	

	return 0;

}


