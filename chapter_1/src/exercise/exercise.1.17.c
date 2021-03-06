#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "s_defines.h"
#include "s_mem.h"
#include "s_text.h"

#include "exercise.1.17.h"

#define MAX_LINE_BUFFER 100 //maximum input line length

//print the longest input line
int find_spec_line_and_length(const char *filename)
{
    size_t len; //current line length
    int lines = 0; //maximum length seen so far
    char line[MAX_LINE_BUFFER]; //current input line
    FILE *fp = fopen(filename, "r");
    assert(fp != NULL);
    
    while((RETURN_SUCCESS == s_getline_f(fp, line, MAX_LINE_BUFFER, &len))&& len > 0)
    {
        if(len > 80)
        {
            printf("length > 80: %s\n", line);
            lines++;
        }
    }

    fclose(fp);
    return lines;
}

typedef struct TAG_STRU_TEST_INFO
{
    char *filename;
    char *input_lines;
    int expect_line_number;
}STRU_TEST_INFO;

#define TEST_FILE_NAME(index) "./test_files/test_exercise_1_17_"#index".txt"
STRU_TEST_INFO exercise_1_17_test_info[] =
{
    {/* 0. input file contains zero words */
        TEST_FILE_NAME(0), 
        "",
        0
    },
    {/* 1. input file contains 1 newlines without anyother charactors */
        TEST_FILE_NAME(1), 
        "\n",
        0
    },
    {/* 2. input file contains 78 chars without newlines */
        TEST_FILE_NAME(2), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678",
        0
    },
    {/* 3. input file contains 78 char with newlines */
        TEST_FILE_NAME(3), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678\n",
        0
    },
    {/* 4. input file contains 79 char without newlines */
        TEST_FILE_NAME(4), 
        "1234567890123456789012345678901234567890123456789012345678901234567890123456789",
        0
    },
    {/* 5. input file contains 79 char with newlines */
        TEST_FILE_NAME(5), 
        "1234567890123456789012345678901234567890123456789012345678901234567890123456789\n",
        0
    },
    {/* 6. input file contains 80 char without newlines */
        TEST_FILE_NAME(6), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890",
        0
    },
    {/* 7. input file contains 80 char with newlines */
        TEST_FILE_NAME(7), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890\n",
        1
    },
    {/* 8. input file contains 81 char without newlines */
        TEST_FILE_NAME(8), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901",
        1
    },
    {/* 9. input file contains 81 char with newlines */
        TEST_FILE_NAME(9), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901\n",
        1
    },
    {/* 10. input file contains 2lines (81 chars with newlines and 80 chars without newline */
        TEST_FILE_NAME(10), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901\n"
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890",
        1
    },
    {/* 11. input file contains 2lines (80 chars with newlines and 101 chars without newline */
        TEST_FILE_NAME(11), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890\n"
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901",
        2
    },
};

int exercise_1_17_generate_input_files(void)
{
    FILE *f = NULL;

    system("mkdir test_files");

    for(int i = 0; i < SIZE_OF_ARRAY(exercise_1_17_test_info); i++)
    {
        f = fopen(exercise_1_17_test_info[i].filename, "w");
    	assert(f != NULL);
        fputs(exercise_1_17_test_info[i].input_lines, f);
    	fclose(f);
    }

	return 0;
}

int exercise_1_17_test_input_files(void)
{
    int  lines = 0;

    printf("*************test result:*********************\n");
    
    for(int i = 0; i < SIZE_OF_ARRAY(exercise_1_17_test_info); i++)
    {
        int result = 0;
        
        printf(" %2d:    %s\n", i, exercise_1_17_test_info[i].filename);
        lines = find_spec_line_and_length(exercise_1_17_test_info[i].filename);
        if(lines != exercise_1_17_test_info[i].expect_line_number)
        {
            result = 1;
            printf("      lines: %d, expect: %d\n", lines, exercise_1_17_test_info[i].expect_line_number);
        }

        if(result == 0)
        {
            printf("        result: success!\n");
        }
    }

    return 0;
}
void print_prompt_info_exercise_1_17(void)
{
    printf("type charactor to execute different operations:\n");
    printf("    h:    display help information\n");
    printf("    g:    generate test files\n");
    printf("    t:    test test files\n");
    printf("    q:    quit\n\n");
}

int exercise_1_17(void)
{
    print_prompt_info_exercise_1_17();

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
                exercise_1_17_generate_input_files();
                break;
            }

            case 't':
            {
                exercise_1_17_test_input_files();
                break;
            }

            case 'h':
            {
                print_prompt_info_exercise_1_17();
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

/*
this line's length is 107:
123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345*/

