#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "s_defines.h"
#include "s_log.h"
#include "s_mem.h"
#include "s_text.h"

#include "exercise.1.18.h"
#define MAX_LINE_BUFFER 100 //maximum input line length

int cutoff_space_and_tabs(char *pstr_buf)
{
    assert(pstr_buf != NULL);
    int pos = strlen(pstr_buf);
    while(pos > 1)
    {
        if(pstr_buf[pos - 1] == '\n')
        {
            if(pstr_buf[pos - 2] == '\t' || pstr_buf[pos - 2] == ' ')
            {
                pstr_buf[pos - 2] = '\n';
                pstr_buf[pos - 1] = '\0';
                pos--;
            }
            else
            {
                break;
            }
        }
        else
        {
            if(pstr_buf[pos - 1] == '\t' || pstr_buf[pos - 1] == ' ')
            {
                pstr_buf[pos - 1] = '\0';
                pos--;
            }
            else
            {
                break;
            }
        }
    }

    if(strlen(pstr_buf) == 1)
    {
        if(pstr_buf[0] == '\n' || pstr_buf[0] == '\t' || pstr_buf[0] == ' ')
        {
            pstr_buf[0] = '\0';
        }
    }
    
    return 0;
}

ENUM_RETURN exercise_1_18_process_lines_and_output(const char *filename, const char *filename_output, int *lines)
{
    size_t len; //current line length
    
    char line[MAX_LINE_BUFFER]; //current input line
    
    FILE *fp = fopen(filename, "r");
    R_ASSERT(fp != NULL, RETURN_FAILURE);
    FILE *fpw = fopen(filename_output, "w");
    R_ASSERT(fpw != NULL, RETURN_FAILURE);
    R_ASSERT(lines != NULL, RETURN_FAILURE);

    *lines = 0; //maximum length seen so far
    
    while((RETURN_SUCCESS == s_getline_f(fp, line, MAX_LINE_BUFFER, &len))&& len > 0)
    {
        s_trim_nl(line);
        
        if(strlen(line) != 0)
        {
            fputs(line, fpw);
            (*lines)++;
        }
    }

    fclose(fp);
    fclose(fpw);
    return RETURN_SUCCESS;
}

typedef struct TAG_STRU_TEST_INFO
{
    char *filename;
    char *filename_output;
    char *input_lines;
    int expect_line_number;
}STRU_TEST_INFO;

#define TEST_FILE_NAME(index) "./test_files/test_exercise_1_18_"#index".txt","./test_files/test_exercise_1_18_"#index"_output.txt"

STRU_TEST_INFO exercise_1_18_test_info[] =
{
    {/* 0. input file contains zero words */
        TEST_FILE_NAME(0), 
        "",
        0
    },
    {/* 1. input file contains space tab newlines without anyother charactors */
        TEST_FILE_NAME(1), 
        "\n  \t  \n  ",
        0
    },
    {/* 2. input file contains 78 chars without newlines */
        TEST_FILE_NAME(2), 
        "123456789 123456789\t123456789  23456789\t\t2345678901234567890123456789012345678",
        1
    },
    {/* 3. input file contains 78 char with newlines */
        TEST_FILE_NAME(3), 
        "123456789 123456789\t123456789  23456789\t\t2345678901234567890123456789012345678\n",
        1
    },
    {/* 4. input file contains 79 char with 2 newlines */
        TEST_FILE_NAME(4), 
        "1234567890123456789012345678901234567890123456789012345678901234567890123456789\n\n",
        1
    },
    {/* 5. input file contains 79 char with space */
        TEST_FILE_NAME(5), 
        "1234567890123456789012345678901234567890123456789012345678901234567890123456789 ",
        1
    },
    {/* 6. input file contains 80 char with 2spaces */
        TEST_FILE_NAME(6), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890  ",
        1
    },
    {/* 7. input file contains 80 char with tab */
        TEST_FILE_NAME(7), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890\t",
        1
    },
    {/* 8. input file contains 81 char with 2tabs */
        TEST_FILE_NAME(8), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901\t\t",
        1
    },
    {/* 9. input file contains 81 char with newlines */
        TEST_FILE_NAME(9), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901 \t",
        1
    },
    {/* 10. input file contains 81 char with newlines */
        TEST_FILE_NAME(10), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901\t ",
        1
    },
    {/* 11. input file contains 2lines (81 chars with newlines and 80 chars without newline */
        TEST_FILE_NAME(11), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901\n"
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890",
        2
    },
    {/* 12. input file contains 2lines (80 chars with newlines and 101 chars without newline */
        TEST_FILE_NAME(12), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890\n"
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901",
        2
    },
};

int exercise_1_18_generate_input_files(void)
{
    FILE *f = NULL;

    system("mkdir test_files");

    for(int i = 0; i < SIZE_OF_ARRAY(exercise_1_18_test_info); i++)
    {
        f = fopen(exercise_1_18_test_info[i].filename, "w");
    	assert(f != NULL);
        fputs(exercise_1_18_test_info[i].input_lines, f);
    	fclose(f);
    }

	return 0;
}

int exercise_1_18_test_input_files_and_output(void)
{
    int  lines = 0;
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    
    printf("*************test result:*********************\n");
    
    for(int i = 0; i < SIZE_OF_ARRAY(exercise_1_18_test_info); i++)
    {
        int result = 0;
        
        printf(" %2d:    %s\n", i, exercise_1_18_test_info[i].filename);
        ret_val = exercise_1_18_process_lines_and_output(exercise_1_18_test_info[i].filename, exercise_1_18_test_info[i].filename_output, &lines);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
        if(lines != exercise_1_18_test_info[i].expect_line_number)
        {
            result = 1;
            printf("      lines: %d, expect: %d\n", lines, exercise_1_18_test_info[i].expect_line_number);
        }

        if(result == 0)
        {
            printf("        result: success!\n");
        }
    }

    return 0;
}

void print_prompt_info_exercise_1_18(void)
{
    printf("type charactor to execute different operations:\n");
    printf("    h:    display help information\n");
    printf("    g:    generate test files\n");
    printf("    t:    test test files\n");
    printf("    q:    quit\n\n");
}

int exercise_1_18(void)
{
    print_prompt_info_exercise_1_18();

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
                exercise_1_18_generate_input_files();
                break;
            }

            case 't':
            {
                exercise_1_18_test_input_files_and_output();
                break;
            }

            case 'h':
            {
                print_prompt_info_exercise_1_18();
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

