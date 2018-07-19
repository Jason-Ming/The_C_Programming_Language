#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "s_stack.h"
#include "s_stm.h"
#include "s_mem.h"
#include "s_cproc.h"

#include "checkpair.h"

//this is a test comment
//test snippet begin========================================================================================
#define STRING "checkpair//  /**/\t  'this is a string' \" good! \"\n"//a line comment

#define CALCULATE(x, y, z) (x/y/*this is a comment"a common string" 'a' // x/y/z*//z)
#define STRING1 'this is a single quote// /* lalala */ \" "hehe" \'sssss\''//a line comment
//a line comment

//test snippet end==========================================================================================
#define SUBCMD_CHECKPAIR "checkpair"
PRIVATE ENUM_RETURN subcmd_checkpair_proc(_VOID)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    ENUM_RETURN check_result = RETURN_SUCCESS;
    const char* file_name = get_input_file_of_current_running_subcmd();
    FALSE_GEN_SYSTEM_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_CHECKPAIR,
        return RETURN_FAILURE;);

    FILE *pfr = fopen(file_name, "r");
    FALSE_GEN_SYSTEM_ERROR_DO(
        pfr != NULL, 
        ERROR_CODE_FILE_NOT_EXIST, 
        file_name,
        return RETURN_FAILURE;);
    
    ret_val = s_cchk_pair(pfr, &check_result);
    R_ASSERT_DO(ret_val == RETURN_SUCCESS, RETURN_FAILURE,fclose(pfr););

    fclose(pfr);
    return check_result;
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

    return RETURN_SUCCESS;
}


