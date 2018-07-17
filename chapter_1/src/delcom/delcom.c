#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "s_cproc.h"
#include "delcom.h"

//this is a test comment
//test snippet begin
#define STRING "delcom//  /**/\t  'this is a string' \" good! \"\n"//a line comment

#define CALCULATE(x, y, z) (x/y/*this is a comment"a common string" 'a' // x/y/z*//z)
#define STRING1 'this is a single quote// /* lalala */ \" "hehe" \'sssss\''//a line comment
//a line comment

//test snippet end

#define SUBCMD_DELCOM "delcom"
#define SUBCMD_DELCOM_OPTION_O "-o"

PRIVATE const char *output_file = NULL;

PRIVATE ENUM_RETURN subcmd_delcom_option_o_proc(const _S8 *arg)
{
    R_ASSERT(arg != NULL, RETURN_FAILURE);
    /* 检查文件名是否合法 */
    output_file = arg;

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_delcom_proc(_VOID)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    
    const char* file_name = get_input_file_of_current_running_subcmd();
    FALSE_GEN_SYSTEM_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_DELCOM,
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

    ret_val = s_cdel_cmnt(pfr, pfw);
    R_ASSERT_DO(ret_val == RETURN_SUCCESS, RETURN_FAILURE,fclose(pfr);fclose(pfw););

    fclose(pfr);
    fclose(pfw);
    return RETURN_SUCCESS;
}

int delcom_init(void)
{
    ENUM_RETURN ret_val;

    ret_val = register_subcmd(
        SUBCMD_DELCOM, 
        subcmd_delcom_proc, 
        "remove all comments from a C program");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(
        SUBCMD_DELCOM, 
        SUBCMD_DELCOM_OPTION_O, 
        OPTION_TYPE_MANDATORY, 
        ARG_TYPE_DATA, 
        subcmd_delcom_option_o_proc, 
        BOOLEAN_FALSE,
        "specify output file name as <arg>");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}

