
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
#include "scc.h"

#define SUBCMD_SCC			"scc"
#define SUBCMD_SCC_OPTION_O	"-o" /* specify the output file */

#define SUBCMD_SCC_OPTION_E	"-e" /* preprocess only */
#define SUBCMD_SCC_OPTION_D	"-d" /* process decaration */


PRIVATE const char * output_file = NULL;

PRIVATE ENUM_BOOLEAN whether_subcmd_scc_option_e_is_enabled = BOOLEAN_FALSE;
PRIVATE ENUM_BOOLEAN whether_subcmd_scc_option_d_is_enabled = BOOLEAN_FALSE;

PRIVATE ENUM_RETURN subcmd_scc_proc_do(const _S8 * file_name, FILE * pfw)
{
	R_ASSERT(file_name != NULL, RETURN_FAILURE);

	ENUM_RETURN ret_val = RETURN_SUCCESS;
    
    return s_cc(file_name, pfw);
    //R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	//return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_scc_proc(_VOID)
{
	ENUM_RETURN ret_val = RETURN_SUCCESS;

	const _S8 * file_name = get_input_file_of_current_running_subcmd();

	FALSE_GEN_SYSTEM_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_SCC,
        return RETURN_FAILURE;);

	FILE *	pfr = fopen(file_name, "r");

	FALSE_GEN_SYSTEM_ERROR_DO(pfr != NULL, 
		ERROR_CODE_FILE_NOT_EXIST, 
		file_name, 
		return RETURN_FAILURE;);
    S_FCLOSE(pfr);


	FILE *pfw = NULL;

	if (output_file != NULL)
	{
		pfw = fopen(output_file, "w");

		if (pfw == NULL)
		{
			ret_val = generate_system_error(ERROR_CODE_FILE_CAN_NOT_BE_CREATED, output_file);
			R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

			return RETURN_FAILURE;
		}
	}

	ret_val = subcmd_scc_proc_do(file_name, pfw);

	S_FCLOSE(pfw);
	return ret_val;
}

PRIVATE ENUM_RETURN subcmd_scc_option_e_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	whether_subcmd_scc_option_e_is_enabled = BOOLEAN_TRUE;

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_scc_option_d_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	whether_subcmd_scc_option_d_is_enabled = BOOLEAN_TRUE;

	return RETURN_SUCCESS;
}


PRIVATE ENUM_RETURN subcmd_scc_option_o_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	/* 检查文件名是否合法 */
	output_file = value;

	return RETURN_SUCCESS;
}

ENUM_RETURN scc_init(_VOID)
{
	ENUM_RETURN ret_val;

	ret_val = register_subcmd(SUBCMD_SCC, 
		subcmd_scc_proc, 
		"process c source file");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	ret_val = register_option(SUBCMD_SCC, 
		SUBCMD_SCC_OPTION_E, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_SWITCH, 
		subcmd_scc_option_e_proc, 
		BOOLEAN_FALSE, 
		"preprocess only");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_SCC, 
		SUBCMD_SCC_OPTION_D, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_SWITCH, 
		subcmd_scc_option_d_proc, 
		BOOLEAN_FALSE, 
		"process declaration");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	ret_val = register_option(SUBCMD_SCC, 
		SUBCMD_SCC_OPTION_O, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_DATA, 
		subcmd_scc_option_o_proc, 
		BOOLEAN_FALSE, 
		"specify output file name as <arg>, if it is ignored, the lines will be print to the standard output");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	return RETURN_SUCCESS;
}




