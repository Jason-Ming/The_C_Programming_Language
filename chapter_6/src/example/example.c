#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "s_mem.h"

#include "main_proc.h"
#include "example.h"



#define SUBCMD_EXAMPLE "example"
#define SUBCMD_EXAMPLE_OPTION_N "-n"
#define SUBCMD_EXAMPLE_OPTION_L "-l"

STRU_MAIN_PROC main_proc_array[] =
{

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

ENUM_RETURN subcmd_example_option_n_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    FUNC_MAIN_PROC handler = get_example_handler_by_name(value);
    if(handler == NULL)
    {
        generate_system_error(ERROR_CODE_INVALID_ARGS, value);
        return RETURN_FAILURE;
    }

    return handler();;
}

ENUM_RETURN subcmd_example_option_l_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    printf("Here is the example list:\n");
    
    STRU_TABLE_TEXT_FORMAT format[2] = {{1, 0, 21, BOOLEAN_TRUE}, {4, 0, 70, BOOLEAN_TRUE}};
    const _S8 *text[2];
    for(int i = 0; i < SIZE_OF_ARRAY(main_proc_array); i++)
    {
        text[0] = main_proc_array[i].n_value;
        text[1] = main_proc_array[i].introduction;
        R_ASSERT(s_print_text_table(text, 1, 2, format) == RETURN_SUCCESS, RETURN_FAILURE);
        
        //printf(" %-20s    %s\n", main_proc_array[i].n_value, main_proc_array[i].introduction);
    }
    
    return RETURN_SUCCESS;
}

ENUM_RETURN example_init(void)
{

    ENUM_RETURN ret_val = RETURN_SUCCESS;

    ret_val = register_subcmd(SUBCMD_EXAMPLE, 
        default_subcmd_proc_handler, 
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
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_DATA, 
        subcmd_example_option_n_proc, 
        BOOLEAN_TRUE,
        "excute example by name");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}


