#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "s_stack.h"

#include "checkpair.h"

//this is a test comment
//test snippet begin
#define STRING "checkpair//  /**/\t  'this is a string' \" good! \"\n"//a line comment

#define CALCULATE(x, y, z) (x/y/*this is a comment"a common string" 'a' // x/y/z*//z)
#define STRING1 'this is a single quote// /* lalala */ \" "hehe" \'sssss\''//a line comment
//a line comment

//test snippet end

#define SUBCMD_CHECKPAIR "checkpair"
#define SUBCMD_CHECKPAIR_OPTION "-o"

PRIVATE const char *output_file = NULL;

typedef enum TAG_ENUM_CHECKPAIR_STM
{
    CHECKPAIR_STM_NORMAL = 0,
    CHECKPAIR_STM_STRING_DOUBLE_QUOTE,
    CHECKPAIR_STM_STRING_SINGLE_QUOTE,
    CHECKPAIR_STM_ONELINE_COMMENT,
    CHECKPAIR_STM_PAIR_COMMENT,
    CHECKPAIR_STM_INTERMEDIATE,
    CHECKPAIR_STM_MAX,
}ENUM_CHECKPAIR_STM;

PRIVATE ENUM_CHECKPAIR_STM checkpair_stm_state = CHECKPAIR_STM_NORMAL;

typedef ENUM_RETURN (*CHECKPAIR_STM_PROC)(FILE *pfr, int c);
typedef struct TAG_STRU_CHECKPAIR_STM_PROC
{
    ENUM_CHECKPAIR_STM state;
    CHECKPAIR_STM_PROC handler;
    const char *info;
}STRU_CHECKPAIR_STM_PROC;

PRIVATE ENUM_RETURN checkpair_stm_proc_normal(FILE *pfr, int c);
PRIVATE ENUM_RETURN checkpair_stm_proc_string_double_quote(FILE *pfr, int c);
PRIVATE ENUM_RETURN checkpair_stm_proc_string_single_quote(FILE *pfr, int c);
PRIVATE ENUM_RETURN checkpair_stm_proc_oneline_comment(FILE *pfr, int c);
PRIVATE ENUM_RETURN checkpair_stm_proc_pair_comment(FILE *pfr, int c);
PRIVATE ENUM_RETURN checkpair_stm_proc_intermediate(FILE *pfr, int c);


PRIVATE STRU_CHECKPAIR_STM_PROC checkpair_stm_proc[CHECKPAIR_STM_MAX] = 
{
    {CHECKPAIR_STM_NORMAL, checkpair_stm_proc_normal, "normal"},
    {CHECKPAIR_STM_STRING_DOUBLE_QUOTE, checkpair_stm_proc_string_double_quote, "string double quote"},
    {CHECKPAIR_STM_STRING_SINGLE_QUOTE, checkpair_stm_proc_string_single_quote, "string single quote"},
    {CHECKPAIR_STM_ONELINE_COMMENT, checkpair_stm_proc_oneline_comment, "oneline comment"},
    {CHECKPAIR_STM_PAIR_COMMENT, checkpair_stm_proc_pair_comment, "pair comment"},
    {CHECKPAIR_STM_INTERMEDIATE, checkpair_stm_proc_intermediate, "intermediate"},
};

PRIVATE STACK stack;
PRIVATE int line = 1;
PRIVATE int column = 0;
PRIVATE ENUM_BOOLEAN is_error_exist = BOOLEAN_FALSE;

PRIVATE void display_check_error_info(const int c)
{
    printf("Error: missing %c before line: %d, column :%d\n", c, line, column);
}

PRIVATE void display_check_correct_info(void)
{
    printf("Check correct!\n");
}

PRIVATE ENUM_RETURN push(const int c)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;

    ret_val = stack_push(&stack, (void *)&c, sizeof(c));
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN pop_and_check(const int c, ENUM_RETURN *result)
{
    R_ASSERT(result != NULL, RETURN_FAILURE);
    
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    int c_temp = 0;
    unsigned int len = 0;
    ret_val = stack_pop(&stack, (void *)&c_temp, &len, sizeof(c_temp));
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
        is_error_exist = BOOLEAN_TRUE;
        display_check_error_info(c_temp);
    }
    
    return RETURN_SUCCESS;
}

PRIVATE ENUM_BOOLEAN is_checkpair_stm_state_valid(int arg)
{
    R_FALSE_RET(arg >= CHECKPAIR_STM_NORMAL && arg < CHECKPAIR_STM_MAX, BOOLEAN_FALSE);

    return BOOLEAN_TRUE;
}

PRIVATE ENUM_RETURN checkpair_stm_init(void)
{
    for(int i = 0; i < CHECKPAIR_STM_MAX; i++)
    {
        R_ASSERT_LOG(checkpair_stm_proc[i].state == i, 
            RETURN_FAILURE, 
            "i = %d, state = %d", 
            i, checkpair_stm_proc[i].state);
    }

    return RETURN_SUCCESS;
}

const char* get_checkpair_stm_string(ENUM_CHECKPAIR_STM state)
{
    R_ASSERT(is_checkpair_stm_state_valid(state) == BOOLEAN_TRUE, NULL);

    return checkpair_stm_proc[(state)].info;
}

CHECKPAIR_STM_PROC get_checkpair_stm_proc(ENUM_CHECKPAIR_STM state)
{
    R_ASSERT(is_checkpair_stm_state_valid(state) == BOOLEAN_TRUE, NULL);

    return checkpair_stm_proc[(state)].handler;
}

ENUM_CHECKPAIR_STM get_current_checkpair_stm_state(void)
{
    return checkpair_stm_state;
}

void set_current_checkpair_stm_state(ENUM_CHECKPAIR_STM arg)
{
    V_ASSERT(arg >= CHECKPAIR_STM_NORMAL && arg < CHECKPAIR_STM_MAX);
    V_ASSERT(checkpair_stm_state != arg);
    
    R_LOG("state change from %s to %s at line: %d, column: %d", 
        get_checkpair_stm_string(checkpair_stm_state),
        get_checkpair_stm_string(arg),
        line,
        column);
    
    checkpair_stm_state = arg;
}

PRIVATE ENUM_RETURN checkpair_stm_proc_normal(FILE *pfr, int c)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    
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
            set_current_checkpair_stm_state(CHECKPAIR_STM_STRING_DOUBLE_QUOTE);
            break;
        }
        case '/':
        {
            set_current_checkpair_stm_state(CHECKPAIR_STM_INTERMEDIATE);
            break;
        }
        case '\'':
        {
            set_current_checkpair_stm_state(CHECKPAIR_STM_STRING_SINGLE_QUOTE);
            break;
        }
        case '\n':
        {
            line++;
            column = 1;
        }
        default:
        {
            break;
        }
    }
    
    return RETURN_SUCCESS;
}
//this is a test comment
PRIVATE ENUM_RETURN checkpair_stm_proc_string_double_quote(FILE *pfr, int c)
{
    static ENUM_BOOLEAN backslash = BOOLEAN_FALSE;
    
    switch (c)
    {
        case '"'://a line comment
        {
            if(backslash == BOOLEAN_FALSE)
            {
                set_current_checkpair_stm_state(CHECKPAIR_STM_NORMAL);
            }

            backslash = BOOLEAN_FALSE;
            break;
        }
        case '\\':
        {
            backslash = BOOLEAN_TRUE;
            break;
        }
        case '\n':
        {
            line++;
            column = 1;
        }
        default:
        {
            backslash = BOOLEAN_FALSE;
            break;
        }
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_proc_string_single_quote(FILE *pfr, int c)
{
    static ENUM_BOOLEAN backslash = BOOLEAN_FALSE;
    
    switch (c)
    {
        case '\''://a line comment
        {
            if(backslash == BOOLEAN_FALSE)
            {
                set_current_checkpair_stm_state(CHECKPAIR_STM_NORMAL);
            }

            backslash = BOOLEAN_FALSE;
            break;
        }
        case '\\':
        {
            backslash = BOOLEAN_TRUE;
            break;
        }
        case '\n':
        {
            line++;
            column = 1;
        }
        default:
        {
            backslash = BOOLEAN_FALSE;
            break;
        }
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_proc_oneline_comment(FILE *pfr, int c)
{
    switch (c)
    {
        case '\n':
        {
            line++;
            column = 1;
            set_current_checkpair_stm_state(CHECKPAIR_STM_NORMAL);
            break;
        }
        default:
        {
            break;
        }
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_proc_pair_comment(FILE *pfr, int c)
{
    static ENUM_BOOLEAN star = BOOLEAN_FALSE;
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
                set_current_checkpair_stm_state(CHECKPAIR_STM_NORMAL);
            }
            star = BOOLEAN_FALSE;
            break;
        }
        case '\n':
        {
            line++;
            column = 1;
        }
        default:
        {
            star = BOOLEAN_FALSE;
            break;
        }
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN checkpair_stm_proc_intermediate(FILE *pfr, int c)
{
    switch (c)
    {
        case '*':
        {
            set_current_checkpair_stm_state(CHECKPAIR_STM_PAIR_COMMENT);
            break;
        }
        case '/':
        {
            set_current_checkpair_stm_state(CHECKPAIR_STM_ONELINE_COMMENT);
            break;
        }
        case '\n':
        {   
            line++;
            column = 1;
        }
        default:
        {
            set_current_checkpair_stm_state(CHECKPAIR_STM_NORMAL);
            break;
        }
    }

    return RETURN_SUCCESS;
}

ENUM_RETURN subcmd_checkpair_option_o_proc(STRU_ARG *arg)
{
    R_ASSERT(arg != NULL, RETURN_FAILURE);
    R_ASSERT(arg->value != NULL, RETURN_FAILURE);

    /* 检查文件名是否合法 */
    output_file = arg->value;

    return RETURN_SUCCESS;
}

ENUM_RETURN subcmd_checkpair_proc_do(FILE *pfr)
{
    R_ASSERT(pfr != NULL, RETURN_FAILURE);

    ENUM_RETURN ret_val = RETURN_SUCCESS;
    int c;
    ret_val = stack_create(&stack);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    while((c = fgetc(pfr)) != EOF)
    {
        R_FALSE_DO_LOG(is_error_exist == BOOLEAN_FALSE, 
            break, "check error!");
        column++;
        ENUM_CHECKPAIR_STM state = get_current_checkpair_stm_state();
        CHECKPAIR_STM_PROC handler = get_checkpair_stm_proc(state);
        R_ASSERT(handler != NULL, RETURN_FAILURE);
        
        ret_val = handler(pfr, c);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    }

    ret_val = stack_delete(&stack);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    if(is_error_exist == BOOLEAN_FALSE)
    {
        display_check_correct_info();
    }
    
    return RETURN_SUCCESS;
}

ENUM_RETURN subcmd_checkpair_proc(STRU_OPTION_RUN_BLOCK *value)
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


