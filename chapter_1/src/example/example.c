#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "main_proc.h"
#include "example.h"

#include "1.1.h"
#include "1.2.h"
#include "1.3.h"
#include "1.4.h"
#include "1.5.1.h"
#include "1.5.2.h"
#include "1.5.3.h"
#include "1.5.4.h"
#include "1.6.h"
#include "1.7.h"
#include "1.8.h"
#include "1.9.h"


#define SUBCMD_EXAMPLE "example"
#define SUBCMD_EXAMPLE_OPTION_N "-n"
#define SUBCMD_EXAMPLE_OPTION_L "-l"

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

ENUM_RETURN example_init(void)
{

    ENUM_RETURN ret_val = RETURN_SUCCESS;

    ret_val = register_subcmd(SUBCMD_EXAMPLE, 
        BOOLEAN_FALSE, 
        subcmd_example_proc, 
        "execute examples.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_EXAMPLE, 
        SUBCMD_EXAMPLE_OPTION_L, 
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_SWITCH, 
        subcmd_example_option_l_proc, 
        BOOLEAN_TRUE,
        "list example by name");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_EXAMPLE, 
        SUBCMD_EXAMPLE_OPTION_N, 
        OPTION_TYPE_MANDATORY, 
        ARG_TYPE_DATA, 
        subcmd_example_option_n_proc, 
        BOOLEAN_TRUE,
        "excute example by name");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}


