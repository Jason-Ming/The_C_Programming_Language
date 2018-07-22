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
#include "exercise.1.11.h"
#include "exercise.1.12.h"
#include "exercise.1.13.h"
#include "exercise.1.14.h"
#include "exercise.1.15.h"
#include "exercise.1.16.h"
#include "exercise.1.17.h"
#include "exercise.1.18.h"


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
    {"1.11", exercise_1_11, "test the program of 'count words'"},
    {"1.12", exercise_1_12, "prints its input one word per line"},
    {"1.13", exercise_1_13, "draw the word histogram of input file"},
    {"1.14", exercise_1_14, "draw the charactor histogram of input file"},
    {"1.15", exercise_1_15, "print Celsius-Fahrenheit table use function"},
    {"1.16", exercise_1_16, "test the program of 'print the longest(any length) input line'"},
    {"1.17", exercise_1_17, "test the program of 'print the specified length(>80) input line'"},
    {"1.18", exercise_1_18, "test the program of 'o remove all trailing blanks and tabs from each line of input, and to delete entirely blank lines.'"},

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
    _S8 *text[2];
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



