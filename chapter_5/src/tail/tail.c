#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "s_defines.h"
#include "s_log.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_mem.h"

#include "tail.h"

#define SUBCMD_TAIL "tail"
#define SUBCMD_TAIL_OPTION_N "-n"
#define SUBCMD_TAIL_OPTION_O "-o"

PRIVATE const char *output_file = NULL;
PRIVATE _S32 line_num = 10;
PRIVATE _S32 *p_positoin = NULL;

PRIVATE ENUM_RETURN subcmd_tail_proc_do(FILE *pfr, FILE *pfw)
{
    R_ASSERT(pfr != NULL, RETURN_FAILURE);

    _S8 line[1000] = {0};
    _S32 len = 0;
    ENUM_RETURN ret_val;
    _S32 i = 0;

    p_positoin = (_S32 *)malloc(line_num * sizeof(_S32));
    R_ASSERT(p_positoin != NULL, RETURN_FAILURE);

    for(i = 0; i < line_num; i++)
    {
        p_positoin[i] = 0;
    }
    
    ret_val = fseek(pfr, 0, SEEK_END);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    _S8 c;
    _SL offset = 0;

    i = 0;
    while(fseek(pfr, -1, SEEK_CUR) == 0)
    {
        offset -= 1;
        
        if((c = fgetc(pfr)) == '\n')
        {
            if(offset + 1 != 0)
            {
                 p_positoin[i++] = offset + 1;
            }
        }
        else
        {
            p_positoin[i] = offset;
        }

        DEBUG_PRINT("offset: %ld, c: %c", offset, c);
        
        if(i == line_num)
        {
            break;
        }
        
        R_ASSERT(fseek(pfr, -1, SEEK_CUR) == 0, RETURN_FAILURE);
    }

    for(i = line_num - 1; i >= 0; i--)
    {
        DEBUG_PRINT("p_positoin[%d]: %d", i, p_positoin[i]);
        
        if(p_positoin[i] == 0)
        {
            continue;
        }

        ret_val = fseek(pfr, p_positoin[i], SEEK_END);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

        ret_val = s_getline(pfr, line, 1000, &len);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
        R_ASSERT(len > 0, RETURN_FAILURE);

        if(pfw == NULL)
        {
            printf("%s", line);
        }
        else
        {
            fputs(line, pfw);
        }
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_tail_proc(_VOID)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    
    const char* file_name = get_input_file_of_current_running_subcmd();
    FALSE_GEN_SYSTEM_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_TAIL,
        return RETURN_FAILURE;);

    FILE *pfr = fopen(file_name, "r");
    FALSE_GEN_SYSTEM_ERROR_DO(
        pfr != NULL, 
        ERROR_CODE_FILE_NOT_EXIST, 
        file_name,
        return RETURN_FAILURE;);

    FILE *pfw = NULL;
    if(output_file != NULL)
    {
        pfw = fopen(output_file, "w");
        if(pfw == NULL)
        {
            FCLOSE(pfr);
            
            ret_val = generate_system_error(
                ERROR_CODE_FILE_CAN_NOT_BE_CREATED, output_file);
            R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

            return RETURN_FAILURE;
        }
    }

    ret_val = subcmd_tail_proc_do(pfr, pfw);
    R_ASSERT_DO(ret_val == RETURN_SUCCESS, RETURN_FAILURE,FCLOSE(pfr);FCLOSE(pfw);FREE(p_positoin););

    FCLOSE(pfr);
    FCLOSE(pfw);
    FREE(p_positoin);
    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_tail_option_n_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    ENUM_RETURN ret_val = s_strtos32(value, &line_num);
    if(ret_val == RETURN_FAILURE || (ret_val == RETURN_SUCCESS && line_num <= 0))
    {
        ret_val = generate_system_error(ERROR_CODE_INVALID_ARGS, value);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
        return RETURN_FAILURE;
    }
    
    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_tail_option_o_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    /* 检查文件名是否合法 */
    output_file = value;

    return RETURN_SUCCESS;
}

ENUM_RETURN tail_init(_VOID)
{
    ENUM_RETURN ret_val;

    ret_val = register_subcmd(
        SUBCMD_TAIL, 
        subcmd_tail_proc, 
        "prints the last n lines of its input.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(
        SUBCMD_TAIL, 
        SUBCMD_TAIL_OPTION_N, 
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_DATA, 
        subcmd_tail_option_n_proc, 
        BOOLEAN_FALSE,
        "specify the number of lines, default value is 10");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(
        SUBCMD_TAIL, 
        SUBCMD_TAIL_OPTION_O, 
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_DATA, 
        subcmd_tail_option_o_proc, 
        BOOLEAN_FALSE,
        "specify output file name as <arg>, if it is ignored, the lines will be print to the io");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}


