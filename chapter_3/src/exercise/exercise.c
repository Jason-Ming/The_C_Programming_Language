#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "s_mem.h"

#include "main_proc.h"

#include "exercise.h"
#include "exercise.3.1.h"
#include "exercise.3.2.h"
#include "exercise.3.3.h"
#include "exercise.3.4.h"
#include "exercise.3.5.h"
#include "exercise.3.6.h"


#define SUBCMD_EXERCISE "exercise"
#define SUBCMD_EXERCISE_OPTION_N "-n"
#define SUBCMD_EXERCISE_OPTION_L "-l"

STRU_MAIN_PROC exercise_proc_array[] =
{
    {"3.1", exercise_3_1, "Our binary search makes two tests inside the loop, when one would suffice (at the\
price of more tests outside). Write a version with only one test inside the loop and\
measure the difference in run-time."},
    {"3.2", exercise_3_2, "Write a function escape(s,t) that converts characters like newline and tab into\
visible escape sequences like \n and \t as it copies the string t to s . Use a switch .\
Write a function for the other direction as well, converting escape sequences into the\
real characters"},
    {"3.3", exercise_3_3, "expand(s1,s2) that expands shorthand notations like a-z in the\
string s1 into the equivalent complete list abc...xyz in s2 . Allow for letters of either\
case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z .\
Arrange that a leading or trailing - is taken literally."},
    {"3.4", exercise_3_4, "n a two's complement number representation, our version of itoa does not handle\
the largest negative number, that is, the value of n equal to -(2 to the power\
(wordsize - 1)) . Explain why not. Modify it to print that value correctly regardless\
of the machine on which it runs."},
    {"3.5", exercise_3_5, "Write the function itob(n,s,b) that converts the integer n into a base b character\
representation in the string s . In particular, itob(n,s,16) formats n as a\
hexadecimal integer in s ."},
    {"3.6", exercise_3_6, "Write a version of itoa that accepts three arguments instead of two. The third\
argument is a minimum field width; the converted number must be padded with\
blanks on the left if necessary to make it wide enough"},

};

FUNC_MAIN_PROC get_exercise_handler_by_name(const char *name)
{
    R_ASSERT(name != NULL, NULL);

    for(int i = 0; i < SIZE_OF_ARRAY(exercise_proc_array); i++)
    {
        if(strcmp(exercise_proc_array[i].n_value, name) == 0)
        {
            return exercise_proc_array[i].handler;
        }
    }

    return NULL;
}

ENUM_RETURN subcmd_exercise_option_n_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    FUNC_MAIN_PROC handler = get_exercise_handler_by_name(value);
    if(handler == NULL)
    {
        generate_system_error(ERROR_CODE_INVALID_ARGS, value);
        return RETURN_FAILURE;
    }

    return handler();
}

ENUM_RETURN subcmd_exercise_option_l_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    printf("Here is the exercise list:\n");
    
    STRU_TABLE_TEXT_FORMAT format[2] = {{1, 0, 21, BOOLEAN_TRUE}, {4, 0, 70, BOOLEAN_TRUE}};
    const _S8 *text[2];
    for(int i = 0; i < SIZE_OF_ARRAY(exercise_proc_array); i++)
    {
        text[0] = exercise_proc_array[i].n_value;
        text[1] = exercise_proc_array[i].introduction;
        R_ASSERT(s_print_text_table(text, 1, 2, format) == RETURN_SUCCESS, RETURN_FAILURE);
    }
    
    return RETURN_SUCCESS;
}

int exercise_init(void)
{

    ENUM_RETURN ret_val = RETURN_SUCCESS;

    ret_val = register_subcmd(SUBCMD_EXERCISE, 
        default_subcmd_proc_handler,
        "execute exercises.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_EXERCISE, 
        SUBCMD_EXERCISE_OPTION_L, 
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_SWITCH, 
        subcmd_exercise_option_l_proc, 
        BOOLEAN_TRUE,
        "list exercise by name");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_EXERCISE, 
        SUBCMD_EXERCISE_OPTION_N, 
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_DATA, 
        subcmd_exercise_option_n_proc, 
        BOOLEAN_TRUE,
        "excute exercise by name");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}



