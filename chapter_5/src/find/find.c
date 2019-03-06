#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "s_defines.h"
#include "s_log.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_mem.h"

#include "find.h"

#define SUBCMD_FIND "find"
#define SUBCMD_FIND_OPTION_S "-s"
#define SUBCMD_FIND_OPTION_N "-n"
#define SUBCMD_FIND_OPTION_X "-x"
#define SUBCMD_FIND_OPTION_O "-o"

#define MAX_LINE				5000

#define MASK_OPTION_NULL (0)

#define MASK_OPTION_N (_U32)(1)
#define MASK_OPTION_X (MASK_OPTION_N<<1)

PRIVATE ENUM_BOOLEAN option_n = BOOLEAN_FALSE;
PRIVATE ENUM_BOOLEAN option_x = BOOLEAN_FALSE;
PRIVATE const char *compare_str = NULL;
PRIVATE const char *output_file = NULL;
PRIVATE _S8 *line_ptr[MAX_LINE];

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
        if (strstr(line_ptr[i], compare_str) != NULL)
        {
            if(option_x == BOOLEAN_TRUE)
            {
                continue;
            }
        }
        else
        {
            if (option_x == BOOLEAN_FALSE)
            {
                continue;
            }
        }

        if (option_n == BOOLEAN_TRUE)
        {
            if (pfw == NULL)
    		{
    			printf("%ld: %s", i+1, line_ptr[i]);
    		}
    		else 
    		{
    			fprintf(pfw, "%ld: %s", i+1, line_ptr[i]);
    		}
        }
        else
        {
            if (pfw == NULL)
    		{
    			printf("%s", line_ptr[i]);
    		}
    		else 
    		{
    			fprintf(pfw, "%s", line_ptr[i]);
    		}
        }
        

	}

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_find_proc_do(FILE * pfr, FILE * pfw)
{
	R_ASSERT(pfr != NULL, RETURN_FAILURE);

	ENUM_RETURN ret_val;
	size_t	line_num = 0;

	ret_val = s_getlines_f(pfr, line_ptr, SIZE_OF_ARRAY(line_ptr), &line_num);
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	write_lines(pfw, line_ptr, line_num);

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_find_proc(_VOID)
{
	ENUM_RETURN ret_val = RETURN_SUCCESS;

	const char * file_name = get_input_file_of_current_running_subcmd();

	FALSE_GEN_SYSTEM_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_FIND,
        return RETURN_FAILURE;);

	FILE *	pfr = fopen(file_name, "r");

	FALSE_GEN_SYSTEM_ERROR_DO(pfr != NULL, 
		ERROR_CODE_FILE_NOT_EXIST, 
		file_name, 
		return RETURN_FAILURE;);

	FILE *	pfw = NULL;

	if (output_file != NULL)
	{
		pfw 	= fopen(output_file, "w");

		if (pfw == NULL)
		{
			S_FCLOSE(pfr);

			ret_val = generate_system_error(ERROR_CODE_FILE_CAN_NOT_BE_CREATED, output_file);
			R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

			return RETURN_FAILURE;
		}
	}

	data_init();

	ret_val = subcmd_find_proc_do(pfr, pfw);

	data_clear();
	S_FCLOSE(pfr);
	S_FCLOSE(pfw);
	return ret_val;
}

PRIVATE ENUM_RETURN subcmd_find_option_s_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	compare_str = value;

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_find_option_n_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	option_n = BOOLEAN_TRUE;

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_find_option_x_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	option_x = BOOLEAN_TRUE;

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_find_option_o_proc(const char *value)
{
    R_ASSERT(value != NULL, RETURN_FAILURE);

    /* 检查文件名是否合法 */
    output_file = value;

    return RETURN_SUCCESS;
}

ENUM_RETURN find_init(_VOID)
{
    ENUM_RETURN ret_val;

    ret_val = register_subcmd(
        SUBCMD_FIND, 
        subcmd_find_proc, 
        "prints lines that contain the specific string of its input.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(
        SUBCMD_FIND, 
        SUBCMD_FIND_OPTION_S, 
        OPTION_TYPE_MANDATORY, 
        ARG_TYPE_DATA, 
        subcmd_find_option_s_proc, 
        BOOLEAN_FALSE,
        "specify the string");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_FIND, 
		SUBCMD_FIND_OPTION_N, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_SWITCH, 
		subcmd_find_option_n_proc, 
		BOOLEAN_FALSE, 
		"prints lines with line number");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_FIND, 
		SUBCMD_FIND_OPTION_X, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_SWITCH, 
		subcmd_find_option_x_proc, 
		BOOLEAN_FALSE, 
		"prints lines which don't cotain the string");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(
        SUBCMD_FIND, 
        SUBCMD_FIND_OPTION_O, 
        OPTION_TYPE_OPTIONAL, 
        ARG_TYPE_DATA, 
        subcmd_find_option_o_proc, 
        BOOLEAN_FALSE,
        "specify output file name as <arg>, if it is ignored, the lines will be print to the standard io");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}



