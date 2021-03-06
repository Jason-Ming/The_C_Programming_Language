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
#include "exercise.2.1.h"
#include "exercise.2.2.h"
#include "exercise.2.3.h"
#include "exercise.2.4.h"
#include "exercise.2.5.h"
#include "exercise.2.6.h"
#include "exercise.2.7.h"
#include "exercise.2.8.h"
#include "exercise.2.9.h"


#define SUBCMD_EXERCISE "exercise"
#define SUBCMD_EXERCISE_OPTION_N "-n"
#define SUBCMD_EXERCISE_OPTION_L "-l"

STRU_MAIN_PROC exercise_proc_array[] =
{
    {"2.1", exercise_2_1, "print type size and extremum "},
    {"2.2", exercise_2_2, "get line form input, Write a loop equivalent to the for loop above without using && or || ."},
    {"2.3", exercise_2_3, "s_hstrtou64: converts a string of hexadecimal digits (including an optional 0x or 0X) into its\
equivalent integer value."},
    {"2.4", exercise_2_4, "s_squeeze: deletes each character in the\
string s1 that matches any character in the string s2 ."},
    {"2.5", exercise_2_5, "any: returns the first location in the string s1\
where any character from the string s2 occurs, or -1 if s1 contains no characters\
from s2 ."},
    {"2.6", exercise_2_6, "setbits(x,p,n,y): returns x with the n bits that begin at\
position p set to the rightmost n bits of y, leaving the other bits unchanged"},
    {"2.7", exercise_2_7, "invert(x,p,n): returns x with the n bits that begin at position p\
inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged."},
    {"2.8", exercise_2_8, "rightrot(x,n): returns the value of the integer x rotated to the\
right by n bit positions."},
    {"2.9", exercise_2_9, "bits_count(x):  counts the number of 1-bits in its integer argument."},

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



