#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "s_defines.h"
#include "s_text.h"
#include "s_cmd.h"
#include "s_log.h"

#define MAX_LINE_BUFFER 1000 //maximum input line length



ENUM_RETURN process_lines_and_output(const char *filename, const char *filename_output, int *lines)
{
    int len; //current line length
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    
    char line[MAX_LINE_BUFFER]; //current input line
    FILE *fp = fopen(filename, "r");
    R_ASSERT(fp != NULL, RETURN_FAILURE);
    
    FILE *fpw = fopen(filename_output, "w");
    R_ASSERT_DO(fpw != NULL, RETURN_FAILURE, fclose(fp));

    R_ASSERT(lines != NULL, RETURN_FAILURE);
    *lines = 0; //maximum length seen so far
    
    while((len = getline(fp, line, MAX_LINE_BUFFER)) > 0)
    {
        ret_val = reverse(line);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
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

#define TEST_FILE_NAME(index) "./test_files/test_exercise_1_19_"#index".txt","./test_files/test_exercise_1_19_"#index"_output.txt"

STRU_TEST_INFO test_info[] =
{
    {/* 0. input file contains zero words */
        TEST_FILE_NAME(0), 
        "",
        0
    },
    {/* 1. input file contains space tab newlines without anyother charactors */
        TEST_FILE_NAME(1), 
        "\n  \t  \n  ",
        3
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
        2
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

ENUM_RETURN generate_input_files(struct TAG_STRU_VALUE *value)
{
    FILE *f = NULL;

    system("mkdir test_files");

    for(int i = 0; i < SIZE_OF_ARRAY(test_info); i++)
    {
        f = fopen(test_info[i].filename, "w");
    	R_ASSERT(f != NULL, RETURN_FAILURE);
        fputs(test_info[i].input_lines, f);
    	fclose(f);
    }

	return RETURN_SUCCESS;
}

ENUM_RETURN test_input_files_and_output(struct TAG_STRU_VALUE *value)
{
    ENUM_RETURN ret_val = RETURN_SUCCESS;
    int  lines = 0;

    R_LOG("*************test result:*********************\n");
    
    for(int i = 0; i < SIZE_OF_ARRAY(test_info); i++)
    {
        int result = 0;
        
        R_LOG(" %2d:    %s\n", i, test_info[i].filename);
        ret_val = process_lines_and_output(test_info[i].filename, test_info[i].filename_output, &lines);
        R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
        if(lines != test_info[i].expect_line_number)
        {
            result = 1;
            R_LOG("      lines: %d, expect: %d\n", lines, test_info[i].expect_line_number);
        }

        if(result == 0)
        {
            R_LOG("        result: success!\n");
        }
    }

    return 0;
}

ENUM_RETURN process_input_files_and_output(struct TAG_STRU_VALUE *value)
{
    if(value == NULL)
    {
        printf("need input and output file name\n");
        return RETURN_FAILURE;
    }

    struct TAG_STRU_VALUE *temp = value;

    char* file1 = temp->value;
    char *file2 = NULL;
    
    temp = temp->next;

    if(temp != NULL)
    {
        file2 = temp->value;
    }
    
    ENUM_RETURN ret_val; 
    int lines;
    ret_val = process_lines_and_output(file1,file2, &lines);
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    return RETURN_SUCCESS;
}

int main(int argc, char **argv)
{
    ENUM_RETURN ret_val;
    ret_val = register_introduction("this program reverses the character strings in each line of input file.");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    ret_val = register_option("-g", OPTION_TYPE_OPTIONAL, VALUE_TYPE_SWITCH, generate_input_files, "generate test files in directory[./test_files]");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option("-t", OPTION_TYPE_OPTIONAL, VALUE_TYPE_SWITCH, test_input_files_and_output, "process test files in directory[./test_files]");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);

    ret_val = register_option("-f", OPTION_TYPE_OPTIONAL, VALUE_TYPE_DATA, process_input_files_and_output, "-f file1 file2 process file1 and output result to file2");
    R_ASSERT(ret_val == RETURN_SUCCESS, RETURN_FAILURE);
    
    return process(argc, argv);
    
}

/*
this line's length is 107:
123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345*/


