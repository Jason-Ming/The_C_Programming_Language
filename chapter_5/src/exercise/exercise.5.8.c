
#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_time.h"

#include "exercise.5.8.h"

int exercise_5_8(void)

{
	int 			year, month, day, yearday, yearday_temp;

	for (year = 1970; year <= 2000; ++year)
	{
		for (yearday = 1; yearday < 366; ++yearday)
		{
			if (month_day(year, yearday, &month, &day) == -1)
			{
				printf("month_day failed: %d %d\n", 
					year, yearday);
			}
			else if (day_of_year(year, month, day, &yearday_temp) != -1 && yearday_temp != yearday)
			{
				printf("bad result: %d %d\n", year, 
					yearday);
				printf("month = %d, day = %d\n", month, 
					day);
			}
		}
	}


	return 0;

}



