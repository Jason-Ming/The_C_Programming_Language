
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "s_type.h"
#include "s_log.h"
#include "s_text.h"
#include "s_mem.h"
#include "s_cmd.h"
#include "s_bintree.h"
#include "s_list.h"
#include "word_count.h"

typedef struct TAG_STRU_WORD_LINE
{
    size_t line;
    struct list_head list;
}STRU_WORD_LINE;

typedef struct TAG_STRU_WORD_INFO
{
    PSTR p_string;
    size_t length;
    STRU_WORD_LINE line_list;
}STRU_WORD_INFO;

typedef struct TAG_STRU_WORD_INFO_PARA
{
    PSTR p_string;
    size_t length;
    size_t line;
}STRU_WORD_INFO_PARA;

#define SUBCMD_WORD_COUNT			"wordcount"
#define SUBCMD_WORD_COUNT_OPTION_O	"-o" /* specify the output file */
#define MAX_LINE_LEN            1000
#define MAX_WORD_LENGTH  256


PRIVATE const char * output_file = NULL;
PRIVATE BINTREE g_words;
PRIVATE FILE * g_pfw = NULL;

PRIVATE ENUM_RETURN save_word(PSTR p_string, size_t length, size_t line)
{
    STRU_WORD_INFO_PARA word_info_para;
    word_info_para.p_string = p_string;
    word_info_para.length = length;
    word_info_para.line = line;

    return bintree_insert_data(&g_words, &word_info_para);
}

PRIVATE ENUM_RETURN output_word(_VOID)
{
    return bintree_print(&g_words);
}

PRIVATE ENUM_RETURN word_line_list_init(STRU_WORD_LINE *p_word_line_head)
{
    S_R_ASSERT(p_word_line_head != NULL, RETURN_FAILURE);

    INIT_LIST_HEAD(&p_word_line_head->list);
    p_word_line_head->line = 0;//a invalid value

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN word_line_list_add(STRU_WORD_LINE *p_word_line_head, STRU_WORD_LINE *p_word_line_new)
{
    S_R_ASSERT(p_word_line_head != NULL, RETURN_FAILURE);
    S_R_ASSERT(p_word_line_new != NULL, RETURN_FAILURE);

    list_add_tail(&p_word_line_new->list, &p_word_line_head->list);

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN word_line_list_release(STRU_WORD_LINE *p_word_line_head)
{
    S_R_ASSERT(p_word_line_head != NULL, RETURN_FAILURE);
    STRU_WORD_LINE *p_word_line_temp;

    LIST_FOR_EACH_ALL_SAFE(p_word_line_head)
    {
        p_word_line_temp = LIST_GET_ITERATOR(STRU_WORD_LINE);
        LIST_RMV_NODE(p_word_line_temp);
        S_FREE(p_word_line_temp);
    }

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN word_bintree_data_alloc_proc(void** pp_data_container, void *p_data_new)
{
    S_R_ASSERT(pp_data_container != NULL, RETURN_FAILURE);
    S_R_ASSERT(*pp_data_container == NULL, RETURN_FAILURE);
    S_R_ASSERT(p_data_new != NULL, RETURN_FAILURE);

    ENUM_RETURN ret_val = RETURN_FAILURE;
    STRU_WORD_INFO_PARA *p_word_info_para = (STRU_WORD_INFO_PARA *)p_data_new;

    STRU_WORD_INFO *p_word_info = (STRU_WORD_INFO *)malloc(sizeof(STRU_WORD_INFO));
    S_R_ASSERT(p_word_info != NULL, RETURN_FAILURE);
    
    p_word_info->p_string = NULL;
    p_word_info->p_string = (PSTR)malloc(p_word_info_para->length + 1);
    S_R_ASSERT_DO(p_word_info->p_string != NULL, RETURN_FAILURE, S_FREE(p_word_info));
    strcpy(p_word_info->p_string, p_word_info_para->p_string);

    p_word_info->length = p_word_info_para->length;
    
    ret_val = word_line_list_init(&p_word_info->line_list);
    S_R_ASSERT_DO(ret_val == RETURN_SUCCESS, RETURN_FAILURE, S_FREE(p_word_info->p_string);S_FREE(p_word_info));
    
    STRU_WORD_LINE *p_word_line = (STRU_WORD_LINE*)malloc(sizeof(STRU_WORD_LINE));
    S_R_ASSERT_DO(p_word_line != NULL, RETURN_FAILURE, S_FREE(p_word_info->p_string);S_FREE(p_word_info));

    p_word_line->line = p_word_info_para->line;
    
    ret_val = word_line_list_add(&(p_word_info->line_list), p_word_line);
    S_R_ASSERT_DO(ret_val == RETURN_SUCCESS, RETURN_FAILURE, S_FREE(p_word_line);S_FREE(p_word_info->p_string);S_FREE(p_word_info));

    DEBUG_PRINT("alloc new word: %s, %zu\n", p_word_info->p_string, p_word_info->line_list.line);
    
    *pp_data_container = p_word_info;
    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN word_bintree_data_free_proc(void** pp_data_container)
{
    S_R_ASSERT(pp_data_container != NULL, RETURN_FAILURE);
    S_R_ASSERT(*pp_data_container != NULL, RETURN_FAILURE);

    STRU_WORD_INFO *p_word_info = (STRU_WORD_INFO *)(*pp_data_container);
    DEBUG_PRINT("free word: %s, %zu\n", p_word_info->p_string, p_word_info->line_list.line);

    return word_line_list_release(&p_word_info->line_list);
}

PRIVATE ENUM_BINTREE_DATA_COMPARE_RESULT word_bintree_data_compare_proc(void *p_data_container, void *p_data_new)
{
    S_R_ASSERT(p_data_container != NULL, RETURN_FAILURE);
    S_R_ASSERT(p_data_new != NULL, RETURN_FAILURE);

    STRU_WORD_INFO *p_word_info = (STRU_WORD_INFO *)p_data_container;
    STRU_WORD_INFO_PARA *p_word_info_para = (STRU_WORD_INFO_PARA *)p_data_new;

    _S32 result = strcmp(p_word_info->p_string, p_word_info_para->p_string);

    DEBUG_PRINT("compare words: %s, %s\n", p_word_info->p_string, p_word_info_para->p_string);
    
    if(result == 0)
    {
        return ENUM_BINTREE_DATA_COMPARE_EQUAL;
    }
    else if(result > 0)
    {
        return ENUM_BINTREE_DATA_COMPARE_BIG;
    }
    else
    {
        return ENUM_BINTREE_DATA_COMPARE_SMALL;
    }
}

PRIVATE ENUM_RETURN word_bintree_data_update_proc(void *p_data_container, void *p_data_new)
{
    S_R_ASSERT(p_data_container != NULL, RETURN_FAILURE);
    S_R_ASSERT(p_data_new != NULL, RETURN_FAILURE);

    STRU_WORD_INFO *p_word_info = (STRU_WORD_INFO *)p_data_container;
    STRU_WORD_INFO_PARA *p_word_info_para = (STRU_WORD_INFO_PARA *)p_data_new;
    
    STRU_WORD_LINE *p_word_line_new = (STRU_WORD_LINE*)malloc(sizeof(STRU_WORD_LINE));
    S_R_ASSERT(p_word_line_new != NULL, RETURN_FAILURE);
    p_word_line_new->line = p_word_info_para->line;

    DEBUG_PRINT("update word: %s, %zu\n", p_word_info->p_string, p_word_info_para->line);
    
    return word_line_list_add(&p_word_info->line_list, p_word_line_new);
}

PRIVATE ENUM_RETURN word_bintree_data_print_proc(void *p_data_container)
{
    S_R_ASSERT(p_data_container != NULL, RETURN_FAILURE);
    S_R_ASSERT(g_pfw != NULL, RETURN_FAILURE);
    
    STRU_WORD_INFO *p_word_info = (STRU_WORD_INFO *)p_data_container;
    STRU_WORD_LINE *p_word_line_temp;

    fprintf(g_pfw, "word: %s, lines: ", p_word_info->p_string);
    
    LIST_FOR_EACH_ALL(&p_word_info->line_list)
    {
        p_word_line_temp = LIST_GET_ITERATOR(STRU_WORD_LINE);
        fprintf(g_pfw, "%zu ", p_word_line_temp->line);
    }

    fprintf(g_pfw, "\n");
    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN subcmd_word_count_proc_do(FILE * pfr)
{
	S_R_ASSERT(pfr != NULL, RETURN_FAILURE);

    PRIVATE _S8 line_buffer [MAX_LINE_LEN];
    const _S8 *p_line_buffer = &line_buffer[0];
    size_t line_length = 0;

    PRIVATE _S8 word_buf[MAX_WORD_LENGTH];
    size_t a_word_length = 0;
    size_t line = 0;
    
    s_set_separators(NULL);
    ENUM_RETURN ret_val = RETURN_FAILURE;

    ret_val = bintree_create(&g_words, 
        word_bintree_data_alloc_proc, 
        word_bintree_data_free_proc, 
        word_bintree_data_compare_proc,
        word_bintree_data_update_proc, 
        word_bintree_data_print_proc);
    S_R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    while(RETURN_SUCCESS == s_getline_f(pfr, line_buffer, MAX_LINE_LEN, &line_length) && line_length > 0)
    {
        line++;
        DEBUG_PRINT("read a new line %zu: %s\n", line, line_buffer);
        p_line_buffer = &line_buffer[0];
        while(RETURN_SUCCESS == s_get_word_s(&p_line_buffer, word_buf, MAX_WORD_LENGTH, &a_word_length) && a_word_length > 0)
        {
            DEBUG_PRINT("read a new word: %s, now line buffer is: %s\n", word_buf, p_line_buffer);
            
            ret_val = save_word(word_buf, a_word_length, line);
            S_ASSERT_DO(ret_val == RETURN_SUCCESS, break);
        }
    }
    
    ret_val = output_word();
    S_ASSERT(ret_val == RETURN_SUCCESS);

    return bintree_delete(&g_words);
}


PRIVATE ENUM_RETURN subcmd_word_count_proc(_VOID)
{
	ENUM_RETURN ret_val = RETURN_SUCCESS;

	const char * file_name = get_input_file_of_current_running_subcmd();

	FALSE_GEN_SYSTEM_ERROR_DO(
        file_name != NULL, 
        ERROR_CODE_NO_INPUT_FILES, 
        SUBCMD_WORD_COUNT,
        return RETURN_FAILURE;);

	FILE *	pfr = fopen(file_name, "r");

	FALSE_GEN_SYSTEM_ERROR_DO(pfr != NULL, 
		ERROR_CODE_FILE_NOT_EXIST, 
		file_name, 
		return RETURN_FAILURE;);

	if (output_file != NULL)
	{
		g_pfw = fopen(output_file, "w");

		if (g_pfw == NULL)
		{
			S_FCLOSE(pfr);

			ret_val = generate_system_error(ERROR_CODE_FILE_CAN_NOT_BE_CREATED, output_file);
			R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

			return RETURN_FAILURE;
		}
	}

	ret_val = subcmd_word_count_proc_do(pfr);

	S_FCLOSE(pfr);
	S_FCLOSE(g_pfw);
	return ret_val;
}

PRIVATE ENUM_RETURN subcmd_word_count_option_o_proc(const char *value)
{
	R_ASSERT(value != NULL, RETURN_FAILURE);

	/* 检查文件名是否合法 */
	output_file = value;

	return RETURN_SUCCESS;
}

ENUM_RETURN word_count_init(_VOID)
{
	ENUM_RETURN ret_val;

	ret_val = register_subcmd(SUBCMD_WORD_COUNT, 
		subcmd_word_count_proc, 
		"count words of the input file");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	ret_val = register_option(SUBCMD_WORD_COUNT, 
		SUBCMD_WORD_COUNT_OPTION_O, 
		OPTION_TYPE_MANDATORY, 
		ARG_TYPE_DATA, 
		subcmd_word_count_option_o_proc, 
		BOOLEAN_FALSE, 
		"specify output file name as <arg>");
	R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

	return RETURN_SUCCESS;
}





