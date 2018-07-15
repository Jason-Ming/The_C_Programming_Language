
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
typedef enum TAG_ENUM_SORTF_ERROR_CODE
{
    ERROR_SORTF_CODE_OPTION_ERROR = 0,

    ERROR_SORTF_CODE_MAX = USER_DEFINE_ERROR_CODE_MAX,
}ENUM_SORTF_ERROR_CODE;

#define SUBCMD_SORTF			"sortf"
#define SUBCMD_SORTF_OPTION_N	"-n" /* compare lines numerically */
#define SUBCMD_SORTF_OPTION_R	"-r" /* sorting in reverse(decreasing) order. */
#define SUBCMD_SORTF_OPTION_F	"-f" /* ignore upper and lower case */
#define SUBCMD_SORTF_OPTION_D	"-d" /* compare lines only on letters, numbers and blanks. */
#define SUBCMD_SORTF_OPTION_O	"-o" /* specify the output file */

#define MAX_LINE				5000

#define MASK_OPTION_NULL (0)

#define MASK_OPTION_N (_U32)(1)
#define MASK_OPTION_R (MASK_OPTION_N<<1)
#define MASK_OPTION_F (MASK_OPTION_R<<1)
#define MASK_OPTION_D (MASK_OPTION_F<<1)


PRIVATE const char * output_file = NULL;
PRIVATE _U32 mask_option_n = 0;
PRIVATE _U32 mask_option_r = 0;
PRIVATE _U32 mask_option_f = 0;
PRIVATE _U32 mask_option_d = 0;

PRIVATE COMPARE_FUNC compare_handler = NULL;

PRIVATE _S8 *line_ptr[MAX_LINE];

#define DIR_CHAR(c) ((IS_ALPHABET(c) || IS_DEC(c) || c == ' ')?1:0)

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

COMPARE_FUNC get_compare_func(_VOID)
{
    _U32 mask_option = mask_option_n | mask_option_r | mask_option_f | mask_option_d;

    switch (mask_option)
    {
        case MASK_OPTION_NULL:
        {
            return (COMPARE_FUNC)strcmp;
        }
        case MASK_OPTION_F:
        {
            return (COMPARE_FUNC)strcasecmp;
        }
        case MASK_OPTION_R:
        {
            return (COMPARE_FUNC)strcmp_r;
        }
        case MASK_OPTION_R | MASK_OPTION_F:
        {
            return (COMPARE_FUNC)strcasecmp_r;
        }
        case MASK_OPTION_D:
        {
            return (COMPARE_FUNC)dircmp;
        }
        case MASK_OPTION_D | MASK_OPTION_F:
        {
            return (COMPARE_FUNC)dircasecmp;
        }
        case MASK_OPTION_D | MASK_OPTION_R:
        {
            return (COMPARE_FUNC)dircmp_r;
        }
        case MASK_OPTION_D | MASK_OPTION_R | MASK_OPTION_F:
        {
            return (COMPARE_FUNC)dircasecmp_r;
        }
        case MASK_OPTION_N:
        {
            return (COMPARE_FUNC)numcmp;
        }
        case MASK_OPTION_N | MASK_OPTION_R:
        {
            return (COMPARE_FUNC)numcmp_r;
        }
        default:
        {
            return (COMPARE_FUNC)NULL;
        }
    }
    
}

PRIVATE ENUM_RETURN subcmd_sortf_proc_do(FILE * pfr, FILE * pfw)
{
	R_ASSERT(pfr != NULL, RETURN_FAILURE);

	ENUM_RETURN ret_val;
	size_t	line_num = 0;

	ret_val = s_getlines(pfr, line_ptr, SIZE_OF_ARRAY(line_ptr), &line_num);
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    R_ASSERT(compare_handler != NULL, RETURN_FAILURE);
	s_qsort_ptr((_VOID * *) line_ptr, 0, line_num - 1, compare_handler);

	//s_qsort_ptr((_VOID**)line_ptr, 0, line_num - 1, (COMPARE_FUNC)strcmp);
	write_lines(pfw, line_ptr, line_num);

	return RETURN_SUCCESS;
}


PRIVATE ENUM_RETURN subcmd_sortf_proc(_VOID)
{
	ENUM_RETURN ret_val = RETURN_SUCCESS;

    compare_handler = get_compare_func();

    FALSE_GEN_USER_ERROR_DO(
        compare_handler != NULL,
        ERROR_SORTF_CODE_OPTION_ERROR,
        NULL,
        return RETURN_FAILURE;);

	const char * file_name = get_input_file_of_current_running_subcmd();

	FALSE_GEN_SYSTEM_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_SORTF,
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

	ret_val = subcmd_sortf_proc_do(pfr, pfw);

	data_clear();
	FCLOSE(pfr);
	FCLOSE(pfw);
	return ret_val;
}


PRIVATE ENUM_RETURN subcmd_sortf_option_n_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	mask_option_n = MASK_OPTION_N;

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_sortf_option_r_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	mask_option_r = MASK_OPTION_R;

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_sortf_option_f_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	mask_option_f = MASK_OPTION_F;

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_sortf_option_d_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	mask_option_d = MASK_OPTION_D;

	return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_sortf_option_o_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	/* 检查文件名是否合法 */
	output_file = value;

	return RETURN_SUCCESS;
}


ENUM_RETURN sortf_init(_VOID)
{
	ENUM_RETURN ret_val;

	ret_val = register_subcmd(SUBCMD_SORTF, 
		subcmd_sortf_proc, 
		"sort lines of input file and output to target file.");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	ret_val = register_option(SUBCMD_SORTF, 
		SUBCMD_SORTF_OPTION_N, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_SWITCH, 
		subcmd_sortf_option_n_proc, 
		BOOLEAN_FALSE, 
		"compare lines numerically");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_SORTF, 
		SUBCMD_SORTF_OPTION_F, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_SWITCH, 
		subcmd_sortf_option_f_proc, 
		BOOLEAN_FALSE, 
		"ignore upper and lower case");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option(SUBCMD_SORTF, 
		SUBCMD_SORTF_OPTION_D, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_SWITCH, 
		subcmd_sortf_option_d_proc, 
		BOOLEAN_FALSE, 
		"compare lines only on letters, numbers and blanks");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
	ret_val = register_option(SUBCMD_SORTF, 
		SUBCMD_SORTF_OPTION_R, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_SWITCH, 
		subcmd_sortf_option_r_proc, 
		BOOLEAN_FALSE, 
		"sorting in reverse(decreasing) order");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	ret_val = register_option(SUBCMD_SORTF, 
		SUBCMD_SORTF_OPTION_O, 
		OPTION_TYPE_OPTIONAL, 
		ARG_TYPE_DATA, 
		subcmd_sortf_option_o_proc, 
		BOOLEAN_FALSE, 
		"specify output file name as <arg>, if it is ignored, the lines will be print to the standard output");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_user_error_info(ERROR_SORTF_CODE_OPTION_ERROR, 
        "option '-n' cann't be uesed with '-d' or '-f'", BOOLEAN_FALSE);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
	return RETURN_SUCCESS;
}



