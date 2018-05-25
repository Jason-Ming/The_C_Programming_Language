#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "main.h"
#include "exercise.h"
#include "example.h"

#define SUBCMD_EXAMPLE "example"
#define SUBCMD_EXAMPLE_OPTION_N "-n"
#define SUBCMD_EXAMPLE_OPTION_L "-l"

#define SUBCMD_EXERCISE "exercise"
#define SUBCMD_EXERCISE_OPTION_N "-n"
#define SUBCMD_EXERCISE_OPTION_L "-l"

typedef ENUM_RETURN (*FUNC_MAIN_PROC)(void);

typedef struct TAG_STRU_MAIN_PROC
{
    const char * n_value;
    FUNC_MAIN_PROC handler;
    const char * introduction;
}STRU_MAIN_PROC;

STRU_MAIN_PROC main_proc_array[] =
{
    {"1.1", main_1_1, "print 'hello, world' "},
    {"1.2", main_1_2, "print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300. use 'while'"},
    {"1.3", main_1_3, "print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300. use 'for'"},
    {"1.4", main_1_4, "print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300. use macro"},
    {"1.5.1", main_1_5_1, "copy input to output"},
    {"1.5.2", main_1_5_2, "count characters in input"},
    {"1.5.3", main_1_5_3, "count lines in input"},
    {"1.5.4", main_1_5_4, "count lines, words, and characters in input"},
    {"1.6", main_1_6, "count digits, white space, others"},
    {"1.7", main_1_7, "test power function"},
    {"1.8", main_1_8, "test power function use parameter as a temporary variable"},
    {"1.9", main_1_9, "print the longest input line"},
};

STRU_MAIN_PROC exercise_proc_array[] =
{
    {"1.1", exercise_1_1, "print 'hello, world' "},
    {"1.2", exercise_1_2, "using a non-specified escape sequence"},
    {"1.3", main_1_3, "print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300. use 'for'"},
    {"1.4", main_1_4, "print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300. use macro"},
    {"1.5.1", main_1_5_1, "copy input to output"},
    {"1.5.2", main_1_5_2, "count characters in input"},
    {"1.5.3", main_1_5_3, "count lines in input"},
    {"1.5.4", main_1_5_4, "count lines, words, and characters in input"},
    {"1.6", main_1_6, "count digits, white space, others"},
    {"1.7", main_1_7, "test power function"},
    {"1.8", main_1_8, "test power function use parameter as a temporary variable"},
    {"1.9", main_1_9, "print the longest input line"},
};

FUNC_MAIN_PROC get_example_handler_by_name(const char *name)
{
    R_ASSERT(name != NULL, NULL);

    for(int i = 0; i < SIZE_OF_ARRAY(main_proc_array); i++)
    {
        if(strcmp(main_proc_array[i].n_value, name) == 0)
        {
            return main_proc_array[i].handler;
        }
    }

    return NULL;
}

ENUM_RETURN subcmd_example_proc(STRU_OPTION_RUN_BLOCK *value)
{
    return RETURN_SUCCESS;
}

ENUM_RETURN subcmd_example_option_n_proc(struct TAG_STRU_ARG *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);
    R_ASSERT(value->value != NULL, RETURN_FAILURE);

    FUNC_MAIN_PROC handler = get_example_handler_by_name(value->value);
    if(handler == NULL)
    {
        add_current_user_error(ERROR_CODE_INVALID_ARGS, value->value);
        return RETURN_FAILURE;
    }

    return handler();;
}

ENUM_RETURN subcmd_example_option_l_proc(struct TAG_STRU_ARG *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);
    R_ASSERT(value->value != NULL, RETURN_FAILURE);

    printf("Here is the example list:\n");
    
    for(int i = 0; i < SIZE_OF_ARRAY(main_proc_array); i++)
    {
        printf(" %-20s    %s\n", main_proc_array[i].n_value, main_proc_array[i].introduction);

    }

    printf("\n");
    
    return RETURN_SUCCESS;
}

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

int main(int argc, char **argv)
{

    ENUM_RETURN ret_val = RETURN_SUCCESS;
    ret_val = register_introduction("this program execute examples and exerceses in chapter 1.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    ret_val = register_usage("<sub-command> [<input files>] [<options> [<args>]]");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = example_init();
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    
    return process(argc, argv);
}

