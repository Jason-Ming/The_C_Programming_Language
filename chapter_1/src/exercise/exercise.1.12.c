#include <stdio.h>
#include <assert.h>
#include "s_text.h"
#include "exercise.1.12.h"

int exercise_1_12(void)
{
    char* files[] = {
        "./test_files/test0.txt", 
        "./test_files/test1.txt",
        "./test_files/test2.txt", 
        "./test_files/test3.txt", 
        "./test_files/test4.txt", 
        "./test_files/test5.txt", 
        "./test_files/test6.txt"};
    
    for(int i = 0; i < SIZE_OF_ARRAY(files); i++)
    {
        printf("file: %s, words: %d\n", files[i], format_words(files[i], "\n"));
    }

    return 0;
}


