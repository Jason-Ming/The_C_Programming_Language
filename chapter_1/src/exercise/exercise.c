#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "main_proc.h"

#include "exercise.h"
#include "exercise.1.1.h"
#include "exercise.1.2.h"
#include "exercise.1.3.h"
#include "exercise.1.4.h"
#include "exercise.1.5.h"
#include "exercise.1.6.h"
#include "exercise.1.7.h"
#include "exercise.1.8.h"
#include "exercise.1.9.h"
#include "exercise.1.10.h"

#define SUBCMD_EXERCISE "exercise"
#define SUBCMD_EXERCISE_OPTION_N "-n"
#define SUBCMD_EXERCISE_OPTION_L "-l"

STRU_MAIN_PROC exercise_proc_array[] =
{
    {"1.1", exercise_1_1, "print 'hello, world' "},
    {"1.2", exercise_1_2, "using a non-specified escape sequence"},
    {"1.3", exercise_1_3, "print Fahrenheit-Celsius table with a heading"},
    {"1.4", exercise_1_4, "print Celsius-Fahrenheit table"},
    {"1.5", exercise_1_5, "print Fahrenhiet-Celcius Table in reverse order"},
    {"1.6", exercise_1_6, "verify that the expression getchar() != EOF is 0 or 1"},
    {"1.7", exercise_1_7, "print the value of EOF"},
    {"1.8", exercise_1_8, "count blanks, tabs, and newlines in input"},
    {"1.9", exercise_1_9, "replacing each string of one or more blanks by a single blank"},
    {"1.10", exercise_1_10, "replace tabs, backslash and backspaces by \\t, \\ and \b"},

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

ENUM_RETURN subcmd_exercise_proc(STRU_OPTION_RUN_BLOCK *value)
{
    return RETURN_SUCCESS;
}

ENUM_RETURN subcmd_exercise_option_n_proc(struct TAG_STRU_ARG *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);
    R_ASSERT(value->value != NULL, RETURN_FAILURE);

    FUNC_MAIN_PROC handler = get_exercise_handler_by_name(value->value);
    if(handler == NULL)
    {
        add_current_user_error(ERROR_CODE_INVALID_ARGS, value->value);
        return RETURN_FAILURE;
    }

    return handler();;
}

ENUM_RETURN subcmd_exercise_option_l_proc(struct TAG_STRU_ARG *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);
    R_ASSERT(value->value != NULL, RETURN_FAILURE);

    printf("Here is the exercise list:\n");
    
    for(int i = 0; i < SIZE_OF_ARRAY(exercise_proc_array); i++)
    {
        printf(" %-20s    %s\n", exercise_proc_array[i].n_value, exercise_proc_array[i].introduction);

    }

    printf("\n");
    
    return RETURN_SUCCESS;
}

int exercise_init(void)
{

    ENUM_RETURN ret_val = RETURN_SUCCESS;

    ret_val = register_subcmd(SUBCMD_EXERCISE, 
        BOOLEAN_FALSE, 
        subcmd_exercise_proc, 
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
        OPTION_TYPE_MANDATORY, 
        ARG_TYPE_DATA, 
        subcmd_exercise_option_n_proc, 
        BOOLEAN_TRUE,
        "excute exercise by name");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}



