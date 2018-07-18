#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "s_defines.h"
#include "s_log.h"
#include "s_text.h"
#include "s_cmd.h"

#include "tab.h"

#define SUBCMD_TAB "tab"
#define SUBCMD_TAB_OPTION_D "-d"
#define SUBCMD_TAB_OPTION_C "-c"
#define SUBCMD_TAB_OPTION_O "-o"

PRIVATE const char *output_file = NULL;
PRIVATE _S32 tab_stop = 8;
PRIVATE ENUM_BOOLEAN whether_option_d_is_enable = BOOLEAN_FALSE;

PRIVATE ENUM_RETURN subcmd_tab_proc_do(FILE *pfr, FILE *pfw)
{
    R_ASSERT(pfr != NULL, RETURN_FAILURE);
    R_ASSERT(pfw != NULL, RETURN_FAILURE);

    _S8 line[1000] = {0};
    _S8 line_new[1000] = {0};
    size_t len = 0;
    ENUM_RETURN ret_val;
    
    while(s_getline_f(pfr, line, 1000, &len) == RETURN_SUCCESS && len > 0)
    {
        line_new[0] = '\0';

        if(whether_option_d_is_enable == BOOLEAN_TRUE)
        {
            ret_val = s_detab(line, line_new, 1000, tab_stop);
        }
        else
        {
            ret_val = s_entab(line, line_new, 1000, tab_stop);
        }
        
        if(ret_val != RETURN_SUCCESS)
        {
            DEBUG_PRINT("detab error!\n    line: %s\nline_new: %s", line, line_new);
            break;
        }

        DEBUG_PRINT("    line: %s\nline_new: %s", line, line_new);
        fputs(line_new, pfw);
    };

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_tab_proc(_VOID)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    
    const char* file_name = get_input_file_of_current_running_subcmd();
    FALSE_GEN_SYSTEM_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_TAB,
        return RETURN_FAILURE;);

    FILE *pfr = fopen(file_name, "r");
    FALSE_GEN_SYSTEM_ERROR_DO(
        pfr != NULL, 
        ERROR_CODE_FILE_NOT_EXIST, 
        file_name,
        return RETURN_FAILURE;);
    
    FILE *pfw = fopen(output_file, "w");
    if(pfw == NULL)
    {
        fclose(pfr);
        
        ret_val = generate_system_error(
            ERROR_CODE_FILE_CAN_NOT_BE_CREATED, output_file);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

        return RETURN_FAILURE;
    }

    ret_val = subcmd_tab_proc_do(pfr, pfw);
    R_ASSERT_DO(ret_val == RETURN_SUCCESS, RETURN_FAILURE,fclose(pfr);fclose(pfw););

    fclose(pfr);
    fclose(pfw);
    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_tab_option_d_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    whether_option_d_is_enable = BOOLEAN_TRUE;
    
    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_tab_option_c_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    ENUM_RETURN ret_val = s_strtos32(value, &tab_stop);
    if(ret_val == RETURN_FAILURE)
    {
        ret_val = generate_system_error(ERROR_CODE_INVALID_ARGS, value);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    }
    
    return ret_val;
}

PRIVATE ENUM_RETURN subcmd_tab_option_o_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    /* 检查文件名是否合法 */
    output_file = value;

    return RETURN_SUCCESS;
}

ENUM_RETURN tab_init(_VOID)
{
    ENUM_RETURN ret_val;

    ret_val = register_subcmd(
        SUBCMD_TAB, 
        subcmd_tab_proc, 
        "replaces strings of blanks with the minimum number of tabs and blanks to achieve the same spacing. ");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(
        SUBCMD_TAB, 
        SUBCMD_TAB_OPTION_D, 
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_SWITCH, 
        subcmd_tab_option_d_proc, 
        BOOLEAN_FALSE,
        "replaces tabs in the input with the proper number of blanks to space to the next tab stop. ");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    ret_val = register_option(
        SUBCMD_TAB, 
        SUBCMD_TAB_OPTION_C, 
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_DATA, 
        subcmd_tab_option_c_proc, 
        BOOLEAN_FALSE,
        "specify tab stops as columns <arg>, default value is 8");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(
        SUBCMD_TAB, 
        SUBCMD_TAB_OPTION_O, 
        OPTION_TYPE_MANDATORY, 
        ARG_TYPE_DATA, 
        subcmd_tab_option_o_proc, 
        BOOLEAN_FALSE,
        "specify output file name as <arg>");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}

