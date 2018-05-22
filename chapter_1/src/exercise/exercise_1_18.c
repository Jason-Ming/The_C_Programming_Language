#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "s_defines.h"
#include "s_log.h"

#define MAX_LINE_BUFFER 100 //maximum input line length

/* read a line into line, return length */
PRIVATE int getline(FILE *fp, char line[], int maxline)
{
    int c;
    int i = 0;

    while((c = fgetc(fp)) != EOF && c != '\n')
    {
        if(i < maxline-1)
        {
            line[i] = c;
        }
        ++i;
    }

    if(c == '\n')
    {
        if(i < (maxline-1))
        {
            line[i] = c;
        }
        ++i;
    }

    line[(maxline - 1) > i ? i : (maxline - 1)] = '\0';

    return i;
}

int cutoff_space_and_tabs(char *pstr_buf)
{
    assert(pstr_buf != NULL);
    int pos = strlen(pstr_buf);
    while(pos != 0)
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

    return 0;
}

ENUM_RETURN exercise_1_18_process_lines_and_output(const char *filename, const char *filename_output, int *lines)
{
    int len; //current line length
    
    char line[MAX_LINE_BUFFER]; //current input line
    
    FILE *fp = fopen(filename, "r");
    R_ASSERT(fp != NULL, RETURN_FAILURE);
    FILE *fpw = fopen(filename_output, "w");
    R_ASSERT(fpw != NULL, RETURN_FAILURE);
    R_ASSERT(lines != NULL, RETURN_FAILURE);

    *lines = 0; //maximum length seen so far
    
    while((len = getline(fp, line, MAX_LINE_BUFFER)) > 0)
    {
        cutoff_space_and_tabs(line);
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
            R_LOG("      lines: %d, expect: %d\n", lines, exercise_1_18_test_info[i].expect_line_number);
        }

        if(result == 0)
        {
            R_LOG("        result: success!\n");
        }
    }

    return 0;
}
int exercise_1_18(int argc, char **argv)
{

    R_ASSERT(argc == 2, RETURN_FAILURE);
    R_ASSERT(argv[1] != NULL, RETURN_FAILURE);

    R_LOG(" %d parameters: \n", argc);
    for(int i = 0; i < argc; i++)
    {
        R_LOG("argv[%d]: %s\n", i, argv[i] );
    }
    
    if(strcmp(argv[1], "g") == 0)
    {
        exercise_1_18_generate_input_files();
    }
    else if(strcmp(argv[1], "t") == 0)
    {
        exercise_1_18_test_input_files_and_output();
    }
    else
    {
        R_LOG("parameters error!\n");
        return -1;
    }
    
    return 0;
}

/*
this line's length is 107:
123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345*/
