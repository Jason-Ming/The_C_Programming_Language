
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
#include "dcl.h"

#define SUBCMD_DCL			"dcl"
#define SUBCMD_DCL_OPTION_O	"-o" /* specify the output file */

#define SUBCMD_DCL_OPTION_N	"-n" /* compare lines numerically */
#define SUBCMD_DCL_OPTION_R	"-r" /* sorting in reverse(decreasing) order. */
#define SUBCMD_DCL_OPTION_F	"-f" /* ignore upper and lower case */
#define SUBCMD_DCL_OPTION_D	"-d" /* compare lines only on letters, numbers and blanks. */


PRIVATE const char * output_file = NULL;

PRIVATE _VOID data_init(_VOID)
{
}

PRIVATE _VOID data_clear(_VOID)
{
}

#define MAX_TOKEN_LEN 256
#define MAX_STATEMENT_LEN 1000

PRIVATE ENUM_RETURN write_token(FILE * pfw, ENUM_DCL_TOKEN t, _S8 *token)
{
    R_ASSERT(token != NULL, RETURN_FAILURE);
    DEBUG_PRINT("%d, %s\n", t, token);
    
    if(pfw == NULL)
    {
        printf("%d, %s, %s\n", t, get_dcl_token_str(t), token);
    }
    else
    {
        fprintf(pfw, "%d, %s, %s\n", t, get_dcl_token_str(t), token);
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_dcl_proc_do(FILE * pfr, FILE * pfw)
{
	R_ASSERT(pfr != NULL, RETURN_FAILURE);
    PRIVATE _S8 statement_buffer[MAX_STATEMENT_LEN];

	ENUM_RETURN ret_val = RETURN_SUCCESS;

    size_t statement_len = 0;
    while(RETURN_SUCCESS == s_cget_statement(pfr, statement_buffer, MAX_STATEMENT_LEN, &statement_len) && statement_len >0)
    {
        _S8 *p_statement = statement_buffer;
        printf("-------->%s\n", p_statement);
        
        ret_val = s_cdcl(p_statement);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    }

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_dcl_proc(_VOID)
{
	ENUM_RETURN ret_val = RETURN_SUCCESS;

	const char * file_name = get_input_file_of_current_running_subcmd();

	FALSE_GEN_SYSTEM_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_DCL,
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
			FCLOSE(pfr);

			ret_val = generate_system_error(ERROR_CODE_FILE_CAN_NOT_BE_CREATED, output_file);
			R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

			return RETURN_FAILURE;
		}
	}

	data_init();

	ret_val = subcmd_dcl_proc_do(pfr, pfw);

	data_clear();
	FCLOSE(pfr);
	FCLOSE(pfw);
	return ret_val;
}

PRIVATE ENUM_RETURN subcmd_dcl_option_o_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	/* 检查文件名是否合法 */
	output_file = value;

	return RETURN_SUCCESS;
}

ENUM_RETURN dcl_init(_VOID)
{
	ENUM_RETURN ret_val;

	ret_val = register_subcmd(SUBCMD_DCL, 
		subcmd_dcl_proc, 
		"parse a declarator");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	ret_val = register_option(SUBCMD_DCL, 
		SUBCMD_DCL_OPTION_O, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_DATA, 
		subcmd_dcl_option_o_proc, 
		BOOLEAN_FALSE, 
		"specify output file name as <arg>, if it is ignored, the lines will be print to the standard output");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	return RETURN_SUCCESS;
}




