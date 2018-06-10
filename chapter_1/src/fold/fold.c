#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"
#include "fold.h"

#define DEFAULT_FOLD_NUM 80
#define SUBCMD_FOLD "fold"
PRIVATE int fold_num = DEFAULT_FOLD_NUM;
#define MAX_LINE_BUFFER 1000 //maximum input line length

ENUM_RETURN subcmd_fold_option_n_proc(struct TAG_STRU_ARG *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);
    R_ASSERT(value->value != NULL, RETURN_FAILURE);

    fold_num = atoi(value->value);
    
    return RETURN_SUCCESS;
}

PRIVATE const char *output_file = NULL;
ENUM_RETURN subcmd_fold_option_o_proc(STRU_ARG *arg)
{
    R_ASSERT(arg != NULL, RETURN_FAILURE);
    R_ASSERT(arg->value != NULL, RETURN_FAILURE);

    /* 检查文件名是否合法 */
    output_file = arg->value;

    return RETURN_SUCCESS;
}

ENUM_RETURN subcmd_fold_proc(STRU_OPTION_RUN_BLOCK *value)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    char line[MAX_LINE_BUFFER]; //current input line
    
    const char* file_name = get_input_file_of_subcmd(SUBCMD_FOLD);
    FALSE_ADD_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_FOLD,
        return RETURN_FAILURE;);

    FILE *fpr = fopen(file_name, "r");
    FALSE_ADD_ERROR_DO(
        fpr != NULL, 
        ERROR_CODE_FILE_NOT_EXIST, 
        file_name,
        return RETURN_FAILURE;);
    
    FILE *fpw = fopen(output_file, "w");
    if(fpw == NULL)
    {
        fclose(fpr);
        
        ret_val = add_current_user_error(
            ERROR_CODE_FILE_NOT_EXIST, output_file);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

        return RETURN_FAILURE;
    }

    char temp[MAX_LINE_BUFFER * 2] = {'\0'};

    int len = 0;
    while((len = get_line(fpr, line, MAX_LINE_BUFFER)) > 0)
    {
        ret_val = fold(line, temp, MAX_LINE_BUFFER * 2, fold_num);
        R_ASSERT_DO(ret_val == RETURN_SUCCESS, RETURN_FAILURE, fclose(fpr);fclose(fpw););
        if(strlen(temp) != 0)
        {
            fputs(temp, fpw);
        }
    }

    fclose(fpr);
    fclose(fpw);
    return RETURN_SUCCESS;
}

int fold_init(void)
{
    ENUM_RETURN ret_val;

    ret_val = register_subcmd(
        SUBCMD_FOLD, 
        subcmd_fold_proc, 
        "fold each line in input files");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(
        SUBCMD_FOLD, 
        "-n", 
        BOOLEAN_TRUE, 
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_DATA, 
        subcmd_fold_option_n_proc, 
        BOOLEAN_FALSE,
        "set the fold number");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(
        SUBCMD_FOLD, 
        "-o", 
        BOOLEAN_TRUE, 
        OPTION_TYPE_MANDATORY, 
        ARG_TYPE_DATA, 
        subcmd_fold_option_o_proc, 
        BOOLEAN_TRUE,
        "specify output file name as <arg>");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}
