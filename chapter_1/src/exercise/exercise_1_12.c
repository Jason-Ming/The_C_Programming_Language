#include <stdio.h>
#include <assert.h>
#include "s_text.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/sizeof((a)[0]))
#endif

int main(void)
{
    char* files[] = {"./test_files/test0.txt", "./test_files/test1.txt", "./test_files/test2.txt", "./test_files/test3.txt", "./test_files/test4.txt", "./test_files/test5.txt", "./test_files/test6.txt"};
    
    for(int i = 0; i < ARRAY_SIZE(files); i++)
    {
        printf("file: %s, words: %d\n", files[i], format_words(files[i], "\n"));
    }

    return 0;
}


