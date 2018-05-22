#include <stdio.h>//include information about standard library
#include "1.1.h"

ENUM_RETURN main_1_1(void)//define a function called main that received no argument values
{//statements of main are enclosed in braces

    //main calls library function printf to print this sequence of characters
    //\n represents the newline character
    printf("hello, world, \c\n");

    return RETURN_SUCCESS;
}

