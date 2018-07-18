#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s_text.h"
#include "s_draw.h"
#include "s_defines.h"
#include "s_mem.h"

#define MAX_WORD_BUFFER_LENGTH 1000*1024
#define MAX_WORD_LENGTH 20//最大长度为20
#define ARRAY_LENGTH_OF_NUM_OF_WORD_LENGTH (MAX_WORD_LENGTH+1)

//存储单词长度为1~20，及20以上的数组个数的
STRU_CHART_DATA num_of_word_length[ARRAY_LENGTH_OF_NUM_OF_WORD_LENGTH];

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

#define OUTPUTFILE_SUFFIX "_output.txt"

PRIVATE void init_chart_data_array(void)
{
    for(int i = 0; i < ARRAY_LENGTH_OF_NUM_OF_WORD_LENGTH - 1; i++)
    {
        num_of_word_length[i].val = 0;
        sprintf(num_of_word_length[i].info, "%d", i + 1);
    }
    
    num_of_word_length[ARRAY_LENGTH_OF_NUM_OF_WORD_LENGTH - 1].val = 0;
    sprintf(num_of_word_length[ARRAY_LENGTH_OF_NUM_OF_WORD_LENGTH - 1].info, ">%d", ARRAY_LENGTH_OF_NUM_OF_WORD_LENGTH - 1);
}

PRIVATE void save_word_length(size_t length)
{
    assert(length >=1);

    if(length > MAX_WORD_LENGTH)
    {
        num_of_word_length[MAX_WORD_LENGTH].val++;
    }
    else
    {
        num_of_word_length[length - 1].val++;
    }
}

PRIVATE ENUM_RETURN calculate_word_length(const char* filename)
{
    FILE* fpr = NULL;
    fpr = fopen(filename, "r");
	assert(fpr != NULL);

    init_chart_data_array();
    _S8 word_buf[MAX_WORD_BUFFER_LENGTH];
    size_t a_word_length = 0;
    s_set_separators(NULL);
    
    while(RETURN_SUCCESS == s_get_word_f(fpr, word_buf, MAX_WORD_BUFFER_LENGTH, &a_word_length) && a_word_length > 0)
    {
        //记录上一个单词的长度到数组中
        save_word_length(a_word_length);
    }
    
	fclose(fpr);

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN get_output_filename(const char* original_filename, char**output_filename)
{
    assert(output_filename != NULL);
    *output_filename = malloc(strlen(original_filename) + strlen(OUTPUTFILE_SUFFIX) + 1);
    assert(*output_filename != NULL);
    (*output_filename)[0] = '\0';
    strcat(*output_filename, original_filename);
    strcat(*output_filename, OUTPUTFILE_SUFFIX);

    return RETURN_SUCCESS;
}

PRIVATE ENUM_RETURN output_word_length(const char* filename_input)
{
    int retval;
    FILE *fpw = NULL;
    char *filename_ouput = NULL;
    retval = get_output_filename(filename_input, &filename_ouput);
    assert(retval == RETURN_SUCCESS);

    fpw = fopen(filename_ouput, "w");
    assert(fpw != NULL);

    draw_histogram(fpw, num_of_word_length, SIZE_OF_ARRAY(num_of_word_length));

    fclose(fpw);

    free(filename_ouput);

    return RETURN_SUCCESS;
}

void print_prompt_info_1_13(void)
{
    printf("type the input file name, the program will draw the word histogram to the output file named _output.txt\n");
}
int exercise_1_13(void)
{

    print_prompt_info_1_13();

    char buff[256] = {'\0'};
    scanf("%s", buff);
    int retval = calculate_word_length(buff);
    retval = output_word_length(buff);

    return retval;
}

