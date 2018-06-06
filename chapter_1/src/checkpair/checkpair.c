#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "s_stack.h"
#include "s_stm.h"

#include "checkpair.h"

//this is a test comment
//test snippet begin========================================================================================
#define STRING "checkpair//  /**/\t  'this is a string' \" good! \"\n"//a line comment

#define CALCULATE(x, y, z) (x/y/*this is a comment"a common string" 'a' // x/y/z*//z)
#define STRING1 'this is a single quote// /* lalala */ \" "hehe" \'sssss\''//a line comment
//a line comment

//test snippet end==========================================================================================

#define SUBCMD_CHECKPAIR "checkpair"
#define SUBCMD_CHECKPAIR_OPTION "-o"

typedef enum TAG_ENUM_CHECKPAIR_STM
{
    CHECKPAIR_STM_NORMAL = 0,
    CHECKPAIR_STM_STRING_DOUBLE_QUOTE,
    CHECKPAIR_STM_STRING_SINGLE_QUOTE,
    CHECKPAIR_STM_ONELINE_COMMENT,
    CHECKPAIR_STM_PAIR_COMMENT,
    CHECKPAIR_STM_INTERMEDIATE,
    CHECKPAIR_STM_END,
    CHECKPAIR_STM_MAX,
}ENUM_CHECKPAIR_STM;

typedef struct TAG_STRU_CHECKPAIR_STM_PROC
{
    STM_STATE state;
    STM_PROC handler;
    const char *info;
}STRU_CHECKPAIR_STM_PROC;

typedef struct TAG_STRU_CHECKPAIR_STM_RUN_DATA
{
    STACK stack;
    int line;
    int column;
    FILE *pfr;
    int c;
    ENUM_BOOLEAN is_error_exist;
}STRU_CHECKPAIR_STM_RUN_DATA;


PRIVATE STM stm = NULL;
PRIVATE STRU_CHECKPAIR_STM_RUN_DATA run_data;

PRIVATE void display_check_error_info(const int expected, const int actual)
{
    printf("Error: expected %c, actual %c, at line: %d, column :%d\n", 
        expected, actual, run_data.line, run_data.column);
}

PRIVATE void display_check_correct_info(void)
{
    printf("Check correct!\n");
}

PRIVATE ENUM_RETURN push(const int c)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;

    ret_val = stack_push(&(run_data.stack), (void *)&c, sizeof(c));
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN pop_and_check(const int c, ENUM_RETURN *result)
{
    R_ASSERT(result != NULL, RETURN_FAILURE);
    
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    int c_temp = 0;
    unsigned int len = 0;
    ret_val = stack_pop(&(run_data.stack), (void *)&c_temp, &len, sizeof(c_temp));
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    switch (c_temp)
    {
        case '(':
        {
            c_temp = ')';
            break;
        }
        case '[':
        {
            c_temp = ']';
            break;
        }
        case '{':
        {
            c_temp = '}';
            break;
        }
        default:
        {
            ret_val = RETURN_FAILURE;
            break;
        }
    }

    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    *result = RETURN_SUCCESS;
    if(c_temp != c)
    {
        *result = RETURN_FAILURE;
        R_LOG("c_temp = %c, c = %c", c_temp, c);
        run_data.is_error_exist = BOOLEAN_TRUE;
        display_check_error_info(c_temp, c);
    }
    
    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_prepare_proc()
{
    ENUM_RETURN ret_val = stack_create(&(run_data.stack));
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    run_data.line = 1;
    run_data.column = 0;
    run_data.is_error_exist = BOOLEAN_FALSE;

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_clear_proc()
{
    ENUM_RETURN ret_val = stack_delete(&(run_data.stack));
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    if(run_data.is_error_exist == BOOLEAN_FALSE)
    {
        display_check_correct_info();
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_preproc()
{
    ENUM_RETURN ret_val;
    
    run_data.c = fgetc(run_data.pfr);
    if(run_data.is_error_exist == BOOLEAN_TRUE)
    {
        R_LOG("check error!");
        ret_val = set_current_stm_state(stm, CHECKPAIR_STM_END);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
        
        return RETURN_SUCCESS;
    }

    if(run_data.c == EOF)
    {
        ret_val = set_current_stm_state(stm, CHECKPAIR_STM_END);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
        
        return RETURN_SUCCESS;
    }

    if(run_data.c == '\n')
    {
        run_data.column = 0;
        run_data.line++;
    }
    
    run_data.column++;

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_postproc()
{
    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_state_notifier()
{
    return RETURN_SUCCESS;
}


PRIVATE ENUM_RETURN checkpair_stm_proc_normal()
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    int c = run_data.c;
    switch (c)
    {
        case '(':
        case '[':
        case '{':
        {
            ret_val = push(c);
            R_ASSERT_LOG(ret_val == RETURN_SUCCESS, RETURN_FAILURE, 
                "c = %c", c);
            break;
        }
        case ')':
        case ']':
        case '}':
        {
            ENUM_RETURN result = RETURN_SUCCESS;
            ret_val = pop_and_check(c, &result);
            R_ASSERT_LOG(ret_val == RETURN_SUCCESS, RETURN_FAILURE, 
                "c = %c", c);
            R_FALSE_RET(result == RETURN_SUCCESS, RETURN_SUCCESS);
            break;
        }
        case '"'://this is a test comment
        {/* this is a test comment */
            set_current_stm_state(stm, CHECKPAIR_STM_STRING_DOUBLE_QUOTE);
            break;
        }
        case '/':
        {
            set_current_stm_state(stm, CHECKPAIR_STM_INTERMEDIATE);
            break;
        }
        case '\'':
        {
            set_current_stm_state(stm, CHECKPAIR_STM_STRING_SINGLE_QUOTE);
            break;
        }
        default:
        {
            break;
        }
    }
    
    return RETURN_SUCCESS;
}
//this is a test comment
PRIVATE ENUM_RETURN checkpair_stm_proc_string_double_quote()
{
    static ENUM_BOOLEAN backslash = BOOLEAN_FALSE;
    int c = run_data.c;
    switch (c)
    {
        case '"'://a line comment
        {
            if(backslash == BOOLEAN_FALSE)
            {
                set_current_stm_state(stm, CHECKPAIR_STM_NORMAL);
            }

            backslash = BOOLEAN_FALSE;
            break;
        }
        case '\\':
        {
            backslash = BOOLEAN_TRUE;
            break;
        }
        default:
        {
            backslash = BOOLEAN_FALSE;
            break;
        }
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_proc_string_single_quote()
{
    static ENUM_BOOLEAN backslash = BOOLEAN_FALSE;
    int c = run_data.c;
    switch (c)
    {
        case '\''://a line comment
        {
            if(backslash == BOOLEAN_FALSE)
            {
                set_current_stm_state(stm, CHECKPAIR_STM_NORMAL);
            }

            backslash = BOOLEAN_FALSE;
            break;
        }
        case '\\':
        {
            backslash = BOOLEAN_TRUE;
            break;
        }
        default:
        {
            backslash = BOOLEAN_FALSE;
            break;
        }
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_proc_oneline_comment()
{
    int c = run_data.c;
    switch (c)
    {
        case '\n':
        {
            set_current_stm_state(stm, CHECKPAIR_STM_NORMAL);
            break;
        }
        default:
        {
            break;
        }
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_proc_pair_comment()
{
    static ENUM_BOOLEAN star = BOOLEAN_FALSE;
    int c = run_data.c;
    switch (c)
    {
        case '*':
        {
            star = BOOLEAN_TRUE;
            break;
        }
        case '/':
        {
            if(star == BOOLEAN_TRUE)
            {
                set_current_stm_state(stm, CHECKPAIR_STM_NORMAL);
            }
            star = BOOLEAN_FALSE;
            break;
        }
        default:
        {
            star = BOOLEAN_FALSE;
            break;
        }
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_proc_intermediate()
{
    int c = run_data.c;
    switch (c)
    {
        case '*':
        {
            set_current_stm_state(stm, CHECKPAIR_STM_PAIR_COMMENT);
            break;
        }
        case '/':
        {
            set_current_stm_state(stm, CHECKPAIR_STM_ONELINE_COMMENT);
            break;
        }
        default:
        {
            set_current_stm_state(stm, CHECKPAIR_STM_NORMAL);
            break;
        }
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_proc_end()
{
    return RETURN_SUCCESS;
}

PRIVATE STRU_CHECKPAIR_STM_PROC checkpair_stm_proc[CHECKPAIR_STM_MAX] = 
{
    {CHECKPAIR_STM_NORMAL, checkpair_stm_proc_normal, "normal"},
    {CHECKPAIR_STM_STRING_DOUBLE_QUOTE, checkpair_stm_proc_string_double_quote, "string double quote"},
    {CHECKPAIR_STM_STRING_SINGLE_QUOTE, checkpair_stm_proc_string_single_quote, "string single quote"},
    {CHECKPAIR_STM_ONELINE_COMMENT, checkpair_stm_proc_oneline_comment, "oneline comment"},
    {CHECKPAIR_STM_PAIR_COMMENT, checkpair_stm_proc_pair_comment, "pair comment"},
    {CHECKPAIR_STM_INTERMEDIATE, checkpair_stm_proc_intermediate, "intermediate"},
    {CHECKPAIR_STM_END, checkpair_stm_proc_end, "end"},
};

PRIVATE ENUM_RETURN checkpair_stm_init(void)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    ret_val = stm_create(&stm, CHECKPAIR_STM_MAX);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = set_stm_start_state(stm, CHECKPAIR_STM_NORMAL);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = set_stm_end_state(stm, CHECKPAIR_STM_END);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = add_stm_prepare_handler(stm, checkpair_stm_prepare_proc);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = add_stm_clear_handler(stm, checkpair_stm_clear_proc);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = add_stm_preproc_handler(stm, checkpair_stm_preproc);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = add_stm_postproc_handler(stm, checkpair_stm_postproc);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = add_stm_state_notifier(stm, checkpair_stm_state_notifier);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    for(int i = 0; i < SIZE_OF_ARRAY(checkpair_stm_proc); i++)
    {
        ret_val = add_stm_state_handler(
            stm, 
            checkpair_stm_proc[i].state, 
            checkpair_stm_proc[i].handler, 
            checkpair_stm_proc[i].info);
        
        R_ASSERT_LOG(
            ret_val == RETURN_SUCCESS, 
            RETURN_FAILURE, 
            "i = %d, state = %d",
            i, 
            checkpair_stm_proc[i].state);
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_checkpair_proc_do(FILE *pfr)
{
    R_ASSERT(pfr != NULL, RETURN_FAILURE);

    run_data.pfr = pfr;
    ENUM_RETURN ret_val = stm_run(stm);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_checkpair_proc(STRU_OPTION_RUN_BLOCK *value)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    
    const char* file_name = get_input_file_of_subcmd(SUBCMD_CHECKPAIR);
    R_ASSERT(file_name != NULL, RETURN_FAILURE);

    FILE *pfr = fopen(file_name, "r");
    FALSE_ADD_ERROR_DO(
        pfr != NULL, 
        ERROR_CODE_FILE_NOT_EXIST, 
        file_name,
        return RETURN_FAILURE;);
    
    ret_val = subcmd_checkpair_proc_do(pfr);
    R_ASSERT_DO(ret_val == RETURN_SUCCESS, RETURN_FAILURE,fclose(pfr););

    fclose(pfr);
    return RETURN_SUCCESS;
}

int checkpair_init(void)
{
    ENUM_RETURN ret_val;

    ret_val = register_subcmd(
        SUBCMD_CHECKPAIR, 
        subcmd_checkpair_proc, 
        "check a C program for rudimentary syntax errors like unbalanced "
        "parentheses, brackets and braces.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

#if 0
    ret_val = register_option(
        SUBCMD_CHECKPAIR, 
        SUBCMD_CHECKPAIR_OPTION, 
        BOOLEAN_TRUE, 
        OPTION_TYPE_MANDATORY, 
        ARG_TYPE_DATA, 
        subcmd_checkpair_option_o_proc, 
        BOOLEAN_TRUE,
        "specify output file name as <arg>");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
#endif

    ret_val = checkpair_stm_init();
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}

