#include <stdio.h>
#include <stdlib.h>

#include "s_text.h"
#include "s_log.h"
#include "s_mem.h"
#include "exercise.1.12.h"

PRIVATE FILE* fpr = NULL;
PRIVATE FILE *fpw = NULL;
PRIVATE _S8 *filename_ouput = NULL;

#define TEST_DIR "./test_files/"
#define OUTPUT_SUFFIX ".output"

ENUM_RETURN format_words_prepare(const _S8* filename)
{
    R_ASSERT(filename != NULL, RETURN_FAILURE);

    fpr = fopen(filename, "r");
    R_ASSERT(fpr != NULL, RETURN_FAILURE);



    filename_ouput = malloc(strlen(filename) + strlen(OUTPUT_SUFFIX) + 1);
    R_ASSERT(filename_ouput != NULL, RETURN_FAILURE);
    
    filename_ouput[0] = '\0';
    sprintf(filename_ouput, "%s%s", filename, OUTPUT_SUFFIX);

    fpw = fopen(filename_ouput, "w");
    R_ASSERT(fpr != NULL, RETURN_FAILURE);

    return RETURN_SUCCESS;
}

#define MAX_LINE_LEN			1000*1024
#define MAX_LEN_OF_WORD MAX_LINE_LEN

ENUM_RETURN format_words_do(const _S8 * separator)
{
    R_ASSERT(separator != NULL, RETURN_FAILURE);
    R_ASSERT(fpr != NULL, RETURN_FAILURE);
    R_ASSERT(fpw != NULL, RETURN_FAILURE);

    PRIVATE _S8 word_buffer [MAX_LEN_OF_WORD];
    size_t word_length = 0;
    ENUM_BOOLEAN first_word = BOOLEAN_TRUE;
    s_set_separators(NULL);
    
    while(RETURN_SUCCESS == s_get_word_f(fpr, word_buffer, MAX_LEN_OF_WORD, &word_length) && word_length > 0)
    {
        fprintf(fpw, "%s%s", first_word?"":separator, word_buffer);
        first_word = BOOLEAN_FALSE;
    }

    return RETURN_SUCCESS;
}

_VOID format_words_clear(_VOID)
{
    FREE(filename_ouput);
    FCLOSE(fpr);
    FCLOSE(fpw);
}

ENUM_RETURN format_words(const _S8 * filename, const _S8 * separator)
{
    ENUM_RETURN ret_val;
    ret_val = format_words_prepare(filename);
    R_FALSE_LOG(ret_val == RETURN_SUCCESS, "format_words_prepare failed! ret_val = %d", ret_val);

    ret_val = format_words_do(separator);
    R_FALSE_LOG(ret_val == RETURN_SUCCESS, "format_words_do failed! ret_val = %d", ret_val);

    format_words_clear();
    return ret_val;
}

int exercise_1_12(void)
{
    char* files[] = {
        "./test_files/test0.txt", 
        "./test_files/test1.txt",
        "./test_files/test2.txt", 
        "./test_files/test3.txt", 
        "./test_files/test4.txt", 
        "./test_files/test5.txt", 
        "./test_files/test6.txt"};
    
    for(int i = 0; i < SIZE_OF_ARRAY(files); i++)
    {
        printf("file: %s, processed result: %d\n", files[i], format_words(files[i], "\n"));
    }

    return 0;
}


