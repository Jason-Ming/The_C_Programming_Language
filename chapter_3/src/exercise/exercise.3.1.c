
#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"

#include "exercise.3.1.h"

#define MAX_ELEMENT 200000
int exercise_3_1(void)
{
    _S32 test_data[MAX_ELEMENT];
    _S32 index;
    _S32 n = -1;
    clock_t time_taken;

    for(_S32 i = 0; i < MAX_ELEMENT; i++)
    {
        test_data[i] = i;
    }

    time_taken = clock();
    
    for(_S32 i = 0; i < 200000; i++)
    {
        index = binsearch(n, test_data, MAX_ELEMENT);
    }
    
    time_taken = clock() - time_taken;
    
    if(index < 0)
    {
        printf("Element %d not found.\n", n);
    }
    else
    {
        printf("Element %d found at index %d.\n", n, index);
    }

    printf("binsearch() took %lu clocks (%lu seconds)\n", (_UL)time_taken, (_UL)time_taken/CLOCKS_PER_SEC);

    time_taken = clock();
    for(_S32 i = 0; i < 200000; i++)
    {
        index = binsearch2(n, test_data, MAX_ELEMENT);
    }
    
    time_taken = clock() - time_taken;
    
    if(index < 0)
    {
        printf("Element %d not found.\n", n);
    }
    else
    {
        printf("Element %d found at index %d.\n", n, index);
    }

    printf("binsearch2() took %lu clocks (%lu seconds)\n", (_UL)time_taken, (_UL)time_taken/CLOCKS_PER_SEC);
	return 0;
}


