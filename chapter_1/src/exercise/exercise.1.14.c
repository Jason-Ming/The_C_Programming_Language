#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s_draw.h"
#include "s_defines.h"
#include "exercise.1.14.h"

#define MAX_ChARACTOR 256 //ASCII字符个数，如果有中文，那么字符的值可能超过127
#define ARRAY_LENGTH_OF_NUM_OF_CHARACTORS (MAX_ChARACTOR)

//存储单词长度为1~20，及20以上的数组个数的
STRU_CHART_DATA num_of_charactors[ARRAY_LENGTH_OF_NUM_OF_CHARACTORS];

#define OUTPUTFILE_SUFFIX "_output.txt"

PRIVATE void init_chart_data_array(void)
{
    for(int i = 0; i < ARRAY_LENGTH_OF_NUM_OF_CHARACTORS; i++)
    {
        num_of_charactors[i].val = 0;
        sprintf(num_of_charactors[i].info, "%d", i);
        printf("%s", num_of_charactors[i].info);
    }
}

PRIVATE void increase_charactor_num(int ch)
{
    assert(ch >=0 && ch < MAX_ChARACTOR);

    num_of_charactors[ch].val++;
}

PRIVATE ENUM_RETURN calculate_charactors(const char* filename)
{
    FILE* fpr = NULL;
    fpr = fopen(filename, "r");
	assert(fpr != NULL);

    int c;
    init_chart_data_array();
    
    while((c = fgetc(fpr)) != EOF)
    {
        increase_charactor_num(c);
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

PRIVATE ENUM_RETURN output_charactors_number(const char* filename_input)
{
    int retval;
    FILE *fpw = NULL;
    char *filename_ouput = NULL;
    retval = get_output_filename(filename_input, &filename_ouput);
    assert(retval == RETURN_SUCCESS);

    fpw = fopen(filename_ouput, "w");
    assert(fpw != NULL);

    draw_histogram(fpw, num_of_charactors, SIZE_OF_ARRAY(num_of_charactors));

    fclose(fpw);

    free(filename_ouput);

    return RETURN_SUCCESS;
}

void print_prompt_info_1_14(void)
{
    printf("type the input file name, the program will draw the charactor histogram to the output file named _output.txt\n");
}

int exercise_1_14(void)
{
    int retval;
    print_prompt_info_1_14();

    char buff[256] = {'\0'};
    scanf("%s", buff);

    retval = calculate_charactors(buff);
    retval = output_charactors_number(buff);

    return retval;
}


