
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "s_mem.h"
#include "s_log.h"

#include "s_text.h"
#include "exercise.1.11.h"

#define CHECK_WORD_NUM(expected,actual)\
    do\
    {\
        if(!(expected == actual))\
        {\
            printf("CHECK_WORD_NUM failed! expected = %zd, actual = %zd\n", expected, actual);\
        }\
        else\
        {\
            printf("CHECK_WORD_NUM success!\n");\
        }\
    }while(0)

PRIVATE int exercise_1_11_generate_input_files(void)
{
    FILE *			f;
	unsigned long	i;
	static char *	ws	= " \f\t\v";
	static char *	al	= "abcdefghijklmnopqrstuvwxyz";
	static char *	i5	=   "a b c d e f g h i j k l m "
                            "n o p q r s t u v w x y z "
                            "a b c d e f g h i j k l m "
                        	"n o p q r s t u v w x y z "
                        	"a b c d e f g h i j k l m "
                        	"n\n";

    system("mkdir test_files");
    
	/* Generate the following: */
	/* 0. input file contains zero words */
	f = fopen("./test_files/test0.txt", "w");
	assert(f != NULL);
	fclose(f);

	/* 1. input file contains 1 enormous word without any newlines */
	f = fopen("./test_files/test1.txt", "w");
	assert(f != NULL);
	for (i = 0; i < ((66000ul / 26) + 1); i++)
	{
		fputs(al, f);
	}
	fclose(f);

	/* 2. input file contains all white space without newlines */
	f = fopen("./test_files/test2.txt", "w");
	assert(f != NULL);
	for (i = 0; i < ((66000ul / 4) + 1); i++)
	{
		fputs(ws, f);
	}
	fclose(f);

	/* 3. input file contains 66000 newlines */
	f = fopen("./test_files/test3.txt", "w");
	assert(f != NULL);
	for (i = 0; i < 66000; i++)
	{
		fputc('\n', f);
	}
	fclose(f);

	/* 4. input file contains word/
	* {huge sequence of whitespace of different kinds}
	* /word
	*/
	f = fopen("./test_files/test4.txt", "w");
	assert(f != NULL);
	fputs("word", f);
	for (i = 0; i < ((66000ul / 26) + 1); i++)
	{
		fputs(ws, f);
	}
	fputs("word", f);
	fclose(f);

	/* 5. input file contains 66000 single letter words,
	* 66 to the line
	*/
	f = fopen("./test_files/test5.txt", "w");
	assert(f != NULL);
	for (i = 0; i < 1000; i++)
	{
		fputs(i5, f);
	}
	fclose(f);

	/* 6. input file contains 66000 words without any newlines */
	f = fopen("./test_files/test6.txt", "w");
	assert(f != NULL);
	for (i = 0; i < 66000; i++)
	{
		fputs("word ", f);
	}
	fclose(f);
	return 0;
}
#define MAX_LINE_LEN			1000*1024

PRIVATE ENUM_RETURN my_count_word(FILE *pfr, size_t *word_num)
{

    R_ASSERT(word_num != NULL, RETURN_FAILURE);
    R_ASSERT(pfr != NULL, RETURN_FAILURE);

    PRIVATE _S8 line_buffer [MAX_LINE_LEN];
    size_t line_length = 0;
    size_t word_num_line = 0;
    ENUM_RETURN ret_val;
    *word_num = 0;
    s_set_separators(NULL);
    while(RETURN_SUCCESS == s_getline_f(pfr, line_buffer, MAX_LINE_LEN, &line_length) && line_length > 0)
    {
        //printf("line_length = %zd\n", line_length);
        
        ret_val = s_count_word_s(line_buffer, &word_num_line);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
        
        //printf("word_num_line = %zd\n", word_num_line);
        
        *word_num += word_num_line;
    }
    
    return RETURN_SUCCESS;
}
PRIVATE void exercise_1_11_check_do(_S8 *file_name, size_t word_number)
{
    _S32 retval;
    size_t word_num1 = 0;
    size_t word_num2 = 0;
    assert(file_name != NULL);
    FILE *pfr = fopen(file_name, "r");
	assert(pfr != NULL);

    s_set_separators(NULL);

    retval = s_count_word_f(pfr, &word_num1);
    V_ASSERT(retval == RETURN_SUCCESS);

    retval = fseek(pfr, 0, SEEK_SET);
    V_ASSERT(retval == RETURN_SUCCESS);
    
    retval = my_count_word(pfr, &word_num2);
    V_ASSERT(retval == RETURN_SUCCESS);

    CHECK_WORD_NUM(word_number,word_num1);
    CHECK_WORD_NUM(word_number,word_num2);

    FCLOSE(pfr);
}

PRIVATE void exercise_1_11_check(_VOID)
{
    exercise_1_11_check_do("./test_files/test0.txt", 0);
    exercise_1_11_check_do("./test_files/test1.txt", 1);
    exercise_1_11_check_do("./test_files/test2.txt", 0);
    exercise_1_11_check_do("./test_files/test3.txt", 0);
    exercise_1_11_check_do("./test_files/test4.txt", 2);
    exercise_1_11_check_do("./test_files/test5.txt", 66000);
    exercise_1_11_check_do("./test_files/test6.txt", 66000);
}

PRIVATE void print_prompt_info(void)
{
    printf("type charactor to execute different operations:\n");
    printf("    h:    display help information\n");
    printf("    g:    generate test files\n");
    printf("    t:    test test files\n");
    printf("    q:    quit\n\n");
}

int exercise_1_11(void)
{
    print_prompt_info();

    int c;
    while((c = getchar()) != EOF)
    {
        switch(c)
        {
            case '\n':
            {
                break;
            }
            
            case 'g':
            {
                exercise_1_11_generate_input_files();
                break;
            }

            case 't':
            {
                exercise_1_11_check();

                break;
            }

            case 'h':
            {
                print_prompt_info();
                break;
            }

            case 'q':
            {
                return RETURN_SUCCESS;
            }

            default:
            {
                printf("unkown operation option\n");
                break;
            }
        }
    }

    return RETURN_SUCCESS;
}


