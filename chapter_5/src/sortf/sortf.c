
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

#include "sortf.h"

#define SUBCMD_SORTF			"sortf"
#define SUBCMD_SORTF_OPTION_N	"-n" /* compare lines numerically */
#define SUBCMD_SORTF_OPTION_R	"-r" /* sorting in reverse(decreasing) order. */
#define SUBCMD_SORTF_OPTION_F	"-f" /* ignore upper and lower case */
#define SUBCMD_SORTF_OPTION_D	"-d" /* compare lines only on letters, numbers and blanks. */
#define SUBCMD_SORTF_OPTION_O	"-o" /* specify the output file */

#define MAX_LINE				5000

PRIVATE const char * output_file = NULL;
PRIVATE ENUM_BOOLEAN numeric = BOOLEAN_FALSE;
PRIVATE _S32 *p_positoin = NULL;

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
		FREE(line_ptr[i]);
	}
}


PRIVATE ENUM_RETURN write_lines(FILE * pfw, _S8 *line_ptr[], size_t line_num)
{
	R_ASSERT(line_ptr != NULL, RETURN_FAILURE);

	for (size_t i = 0; i < line_num; i++)
	{
		if (pfw == NULL)
		{
			printf("%s", line_ptr[i]);
		}
		else 
		{
			fputs(line_ptr[i], pfw);
		}
	}

	return RETURN_SUCCESS;
}


/* numcmp: compare s1 and s2 numerically */
PRIVATE int numcmp(char * s1, char * s2)
{
	double	v1, v2;

	v1		= atof(s1);
	v2		= atof(s2);

	if (v1 < v2)
	{
		return - 1;

	}
	else if (v1 > v2)
	{
		return 1;

	}
	else 
	{
		return 0;
	}
}


PRIVATE ENUM_RETURN subcmd_sortf_proc_do(FILE * pfr, FILE * pfw)
{
	R_ASSERT(pfr != NULL, RETURN_FAILURE);

	ENUM_RETURN ret_val;
	size_t	line_num = 0;

	ret_val = s_getlines(pfr, line_ptr, SIZE_OF_ARRAY(line_ptr), &line_num);
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	s_qsort_ptr((_VOID * *) line_ptr, 0, line_num - 1, (numeric ? (COMPARE_FUNC) numcmp: (COMPARE_FUNC) strcmp));

	//s_qsort_ptr((_VOID**)line_ptr, 0, line_num - 1, (COMPARE_FUNC)strcmp);
	write_lines(pfw, line_ptr, line_num);

	return RETURN_SUCCESS;
}


PRIVATE ENUM_RETURN subcmd_sortf_proc(STRU_OPTION_RUN_BLOCK * value)
{
	ENUM_RETURN ret_val = RETURN_SUCCESS;

	const char * file_name = get_input_file_of_subcmd(SUBCMD_SORTF);

	R_ASSERT(file_name != NULL, RETURN_FAILURE);

	FILE *	pfr = fopen(file_name, "r");

	FALSE_ADD_ERROR_DO(pfr != NULL, 
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

			ret_val = add_current_user_error(ERROR_CODE_FILE_CAN_NOT_BE_CREATED, output_file);
			R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

			return RETURN_FAILURE;
		}
	}

	data_init();
	ret_val = subcmd_sortf_proc_do(pfr, pfw);
	R_ASSERT_DO(ret_val == RETURN_SUCCESS, RETURN_FAILURE, FCLOSE(pfr); FCLOSE(pfw); FREE(p_positoin););

	data_clear();

	FCLOSE(pfr);
	FCLOSE(pfw);
	FREE(p_positoin);
	return RETURN_SUCCESS;
}


PRIVATE ENUM_RETURN subcmd_sortf_option_n_proc(STRU_ARG * arg)
{
	R_ASSERT(arg != NULL, RETURN_FAILURE);
	R_ASSERT(arg->value != NULL, RETURN_FAILURE);

	numeric = BOOLEAN_TRUE;

	return RETURN_SUCCESS;
}


PRIVATE ENUM_RETURN subcmd_sortf_option_o_proc(STRU_ARG * arg)
{
	R_ASSERT(arg != NULL, RETURN_FAILURE);
	R_ASSERT(arg->value != NULL, RETURN_FAILURE);

	/* 检查文件名是否合法 */
	output_file = arg->value;

	return RETURN_SUCCESS;
}


ENUM_RETURN sortf_init(_VOID)
{
	ENUM_RETURN ret_val;

	ret_val = register_subcmd(SUBCMD_SORTF, 
		BOOLEAN_TRUE, 
		subcmd_sortf_proc, 
		"sort lines of input file and output to target file.");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	ret_val = register_option(SUBCMD_SORTF, 
		SUBCMD_SORTF_OPTION_N, 
		BOOLEAN_TRUE, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_SWITCH, 
		subcmd_sortf_option_n_proc, 
		BOOLEAN_FALSE, 
		"compare lines numerically");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	ret_val = register_option(SUBCMD_SORTF, 
		SUBCMD_SORTF_OPTION_O, 
		BOOLEAN_TRUE, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_DATA, 
		subcmd_sortf_option_o_proc, 
		BOOLEAN_FALSE, 
		"specify output file name as <arg>, if it is ignored, the lines will be print to the standard io");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	return RETURN_SUCCESS;
}



