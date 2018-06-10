#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "main_proc.h"

#include "exercise.h"
#include "exercise.2.1.h"
#include "exercise.2.2.h"
#include "exercise.2.3.h"
#include "exercise.2.4.h"
#include "exercise.2.5.h"
#include "exercise.2.6.h"
#include "exercise.2.7.h"


#define SUBCMD_EXERCISE "exercise"
#define SUBCMD_EXERCISE_OPTION_N "-n"
#define SUBCMD_EXERCISE_OPTION_L "-l"

STRU_MAIN_PROC exercise_proc_array[] =
{
    {"2.1", exercise_2_1, "print type size and extremum "},
    {"2.2", exercise_2_2, "get line form input "},
    {"2.3", exercise_2_3, "htou: converts a string of hexadecimal digits (including\
an optional 0x or 0X) into its equivalent integer value."},
    {"2.4", exercise_2_4, "squeeze: deletes each character in the\
string s1 that matches any character in the string s2 ."},
    {"2.5", exercise_2_5, "any: returns the first location in the string s1\
where any character from the string s2 occurs, or -1 if s1 contains no characters\
from s2 ."},
    {"2.6", exercise_2_6, "setbits(x,p,n,y): returns x with the n bits that begin at\
position p set to the rightmost n bits of y, leaving the other bits unchanged"},
    {"2.7", exercise_2_7, "invert(x,p,n): returns x with the n bits that begin at position p\
inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged."},

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
        subcmd_exercise_proc, 
        "execute exercises.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_EXERCISE, 
        SUBCMD_EXERCISE_OPTION_L, 
        BOOLEAN_FALSE, 
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_SWITCH, 
        subcmd_exercise_option_l_proc, 
        BOOLEAN_TRUE,
        "list exercise by name");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_EXERCISE, 
        SUBCMD_EXERCISE_OPTION_N, 
        BOOLEAN_FALSE, 
        OPTION_TYPE_MANDATORY, 
        ARG_TYPE_DATA, 
        subcmd_exercise_option_n_proc, 
        BOOLEAN_TRUE,
        "excute exercise by name");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}



