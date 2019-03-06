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

#define MAX_LINE				5000

PRIVATE _S8 *line_ptr[MAX_LINE];

PRIVATE const char *output_file = NULL;
PRIVATE _S32 line_num = 10;

PRIVATE _VOID data_init(_VOID)
{
	for (_S32 i = 0; i < SIZE_OF_ARRAY(line_ptr); i++)
	{
		line_ptr[i] = NULL;
	}
}


PRIVATE _VOID data_clear(_VOID)
{
	for (_S32 i = 0; i < SIZE_OF_ARRAY(line_ptr); i++)
	{
		S_FREE(line_ptr[i]);
	}
}


PRIVATE ENUM_RETURN write_lines(FILE * pfw, _S8 *line_ptr[], size_t line_num)
{
	R_ASSERT(line_ptr != NULL, RETURN_FAILURE);

	for (size_t i = 0; i < line_num; i++)
	{
        if (pfw == NULL)
		{
			printf("%s", line_ptr[line_num - i - 1]);
		}
		else 
		{
			fprintf(pfw, "%s", line_ptr[line_num -i - 1]);
		}
	}

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_tail_proc_do(FILE *pfr, FILE *pfw)
{
    R_ASSERT(pfr != NULL, RETURN_FAILURE);

    	R_ASSERT(pfr != NULL, RETURN_FAILURE);

	ENUM_RETURN ret_val;
	size_t	line_numbers = 0;

	ret_val = s_getlines_f_r(pfr, line_ptr, line_num, &line_numbers);
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	write_lines(pfw, line_ptr, line_numbers);

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
            S_FCLOSE(pfr);
            
            ret_val = generate_system_error(
                ERROR_CODE_FILE_CAN_NOT_BE_CREATED, output_file);
            R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

            return RETURN_FAILURE;
        }
    }
    
	data_init();

    ret_val = subcmd_tail_proc_do(pfr, pfw);

	data_clear();
	S_FCLOSE(pfr);
	S_FCLOSE(pfw);
	return ret_val;
}

PRIVATE ENUM_RETURN subcmd_tail_option_n_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    ENUM_RETURN ret_val = s_strtos32(value, &line_num);
    if(ret_val == RETURN_FAILURE || (ret_val == RETURN_SUCCESS && (line_num <= 0 || line_num > MAX_LINE)))
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
        "specify the number of lines, default value is 10, range: 1~5000");
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


