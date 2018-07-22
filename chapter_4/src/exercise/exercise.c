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
#include "exercise.4.1.h"
#include "exercise.4.2.h"
#include "exercise.4.3.h"
#include "exercise.4.13.h"
#include "exercise.4.14.h"
#include "exercise.4.6.h"


#define SUBCMD_EXERCISE "exercise"
#define SUBCMD_EXERCISE_OPTION_N "-n"
#define SUBCMD_EXERCISE_OPTION_L "-l"

STRU_MAIN_PROC exercise_proc_array[] =
{
    {"4.1", exercise_4_1, "Write the function strrindex(s,t) , which returns the position of the rightmost\
occurrence of t in s , or -1 if there is none."},
    {"4.2", exercise_4_2, "Extend atof to handle scientific notation of the form 123.45e-6 where a\
floating-point number may be followed by e or E and an optionally signed exponent."},
    {"4.3", exercise_4_3, "Given the basic framework, it's straightforward to extend the calculator. Add the\
modulus ( % ) operator and provisions for negative numbers"},
    {"4.13", exercise_4_13, "Write a recursive version of the function reverse(s) , which reverses the string s in\
place."},
    {"4.14", exercise_4_14, "Define a macro swap(t,x,y) that interchanges two arguments of type t . (Block\
structure will help.)"},
    {"4.6", exercise_4_6, "Write a version of itoa that accepts three arguments instead of two. The third\
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



