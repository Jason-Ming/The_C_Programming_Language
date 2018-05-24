#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "main.h"


#define SUBCMD_EXAMPLE "example"
#define SUBCMD_EXAMPLE_OPTION_N "-n"
#define SUBCMD_EXAMPLE_OPTION_L "-l"
typedef ENUM_RETURN (*FUNC_MAIN_PROC)(void);

typedef struct TAG_STRU_EXAMPLE_PROC
{
    const char * n_value;
    FUNC_MAIN_PROC handler;
}STRU_EXAMPLE_PROC;

STRU_EXAMPLE_PROC main_proc_array[] =
{
    {"1.1", main_1_1},
    {"1.2", main_1_2},
    {"1.3", main_1_3},
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

    printf("Here is the example list:");
    
    for(int i = 0; i < SIZE_OF_ARRAY(main_proc_array); i++)
    {
        printf(" %s", main_proc_array[i].n_value);

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


    
    return process(argc, argv);
}

