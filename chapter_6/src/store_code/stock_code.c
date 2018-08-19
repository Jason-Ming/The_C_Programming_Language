
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "s_defines.h"
#include "s_log.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_mem.h"
#include "s_alg.h"
#include "s_cproc.h"
#include "usr_error.h"
#include "stock_code.h"

#define SUBCMD_SC			"sc"
#define SUBCMD_SC_OPTION_O	"-o" /* specify the output file */
#define MAX_LINE_LEN_OF_SC_FILE			1000


PRIVATE const char * output_file = NULL;

PRIVATE ENUM_RETURN subcmd_sc_proc_do(FILE * pfr, FILE * pfw)
{
	R_ASSERT(pfr != NULL, RETURN_FAILURE);
	_S8 line_buffer[MAX_LINE_LEN_OF_SC_FILE];
	size_t line_len = 0;
	
	while(s_getline_f(pfr, line_buffer, MAX_LINE_LEN_OF_SC_FILE, &line_len) == RETURN_SUCCESS && line_len > 0)
	{
		if(line_buffer[0] == '6')
		{
			fputc('1', pfw);
		}
		else
		{
			fputc('0', pfw);
		}
		fputs(line_buffer, pfw);
	};
	
	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_sc_proc(_VOID)
{
	ENUM_RETURN ret_val = RETURN_SUCCESS;

	const char * file_name = get_input_file_of_current_running_subcmd();

	FALSE_GEN_SYSTEM_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_SC,
        return RETURN_FAILURE;);

	FILE *	pfr = fopen(file_name, "r");

	FALSE_GEN_SYSTEM_ERROR_DO(pfr != NULL, 
		ERROR_CODE_FILE_NOT_EXIST, 
		file_name, 
		return RETURN_FAILURE;);

	FILE *	pfw = NULL;

	if (output_file != NULL)
	{
		pfw = fopen(output_file, "w");

		if (pfw == NULL)
		{
			FCLOSE(pfr);

			ret_val = generate_system_error(ERROR_CODE_FILE_CAN_NOT_BE_CREATED, output_file);
			R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

			return RETURN_FAILURE;
		}
	}

	ret_val = subcmd_sc_proc_do(pfr, pfw);

	FCLOSE(pfr);
	FCLOSE(pfw);
	return ret_val;
}

PRIVATE ENUM_RETURN subcmd_sc_option_o_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	/* 检查文件名是否合法 */
	output_file = value;

	return RETURN_SUCCESS;
}

ENUM_RETURN stock_code_init(_VOID)
{
	ENUM_RETURN ret_val;

	ret_val = register_subcmd(SUBCMD_SC, 
		subcmd_sc_proc, 
		"process stock code file");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	ret_val = register_option(SUBCMD_SC, 
		SUBCMD_SC_OPTION_O, 
		OPTION_TYPE_MANDATORY, 
		ARG_TYPE_DATA, 
		subcmd_sc_option_o_proc, 
		BOOLEAN_FALSE, 
		"specify output file name as <arg>, if it is ignored, the lines will be print to the standard output");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	return RETURN_SUCCESS;
}





