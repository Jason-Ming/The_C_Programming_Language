#include <stdio.h>
#include <assert.h>
#include "1_5_4.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#endif

int main(void)
{
    char* files[] = {"test0", "test1", "test2", "test3", "test4", "test5", "test6"};

    enable_output();
    
    for(int i = 0; i < ARRAY_SIZE(files); i++)
    {
        printf("file: %s, words: %d\n", files[i], calculate_words(files[i]));
    }

    return 0;
}


