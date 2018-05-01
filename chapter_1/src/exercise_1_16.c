#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

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

/* copy 'from' to 'to'; assume to is big enough */
PRIVATE void copy(char to[], char from[])
{
    int i;
    i = 0;

    while((to[i] = from[i]) != '\0')
    {
        ++i;
    }
    
}

//print the longest input line
int get_maxline_and_length(const char *filename, char longest[])
{
    int len; //current line length
    int max = 0; //maximum length seen so far
    char line[MAX_LINE_BUFFER]; //current input line
    FILE *fp = fopen(filename, "r");
    assert(fp != NULL);
    
    while((len = getline(fp, line, MAX_LINE_BUFFER)) > 0)
    {
        if(len > max )
        {
            max = len;
            copy(longest, line);
        }
    }

    if(max > 0) //here was a line
    {
        //printf("get_maxline_and_length: %d\nget_maxline_and_length: %s\n", max, longest);
    }

    fclose(fp);
    return max;
}

typedef struct TAG_STRU_TEST_INFO
{
    char *filename;
    char *input_lines;
    char *expect_line;
    int max_length;
}STRU_TEST_INFO;

#define TEST_FILE_NAME(index) "./test_files/test_exercise_1_16_"#index".txt"
STRU_TEST_INFO test_info[] =
{
    {/* 0. input file contains zero words */
        TEST_FILE_NAME(0), 
        "",
        "",
        0
    },
    {/* 1. input file contains 1 newlines without anyother charactors */
        TEST_FILE_NAME(1), 
        "\n",
        "\n",
        1
    },
    {/* 2. input file contains 98 chars without newlines */
        TEST_FILE_NAME(2), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678",
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678",
        98
    },
    {/* 3. input file contains 98 char with newlines */
        TEST_FILE_NAME(3), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678\n",
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678\n",
        99
    },
    {/* 4. input file contains 99 char without newlines */
        TEST_FILE_NAME(4), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
        99
    },
    {/* 5. input file contains 99 char with newlines */
        TEST_FILE_NAME(5), 
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n",
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
        100
    },
    {/* 6. input file contains 100 char without newlines */
        TEST_FILE_NAME(6), 
        "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
        100
    },
    {/* 7. input file contains 100 char with newlines */
        TEST_FILE_NAME(7), 
        "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n",
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
        101
    },
    {/* 8. input file contains 101 char without newlines */
        TEST_FILE_NAME(8), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901",
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
        101
    },
    {/* 9. input file contains 101 char with newlines */
        TEST_FILE_NAME(9), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901\n",
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
        102
    },
    {/* 10. input file contains 2lines (101 chars with newlines and 100 chars without newline */
        TEST_FILE_NAME(10), 
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901\n"
        "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
        102
    },
    {/* 11. input file contains 2lines (100 chars with newlines and 101 chars without newline */
        TEST_FILE_NAME(11), 
        "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890\n"
        "12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901",
        "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789",
        101
    },
};

int generate_input_files(void)
{
    FILE *f = NULL;

    system("mkdir test_files");

    for(int i = 0; i < SIZE_OF_ARRAY(test_info); i++)
    {
        f = fopen(test_info[i].filename, "w");
    	assert(f != NULL);
        fputs(test_info[i].input_lines, f);
    	fclose(f);
    }

	return 0;
}

int test_input_files(void)
{
    int  max = 0;
    char longest[MAX_LINE_BUFFER]; //longest line saved here

    printf("*************test result:*********************\n");
    
    for(int i = 0; i < SIZE_OF_ARRAY(test_info); i++)
    {
        int result = 0;
        
        printf(" %2d:    %s\n", i, test_info[i].filename);
        max = get_maxline_and_length(test_info[i].filename, longest);
        if(max != test_info[i].max_length)
        {
            result = 1;
            printf("        max: %d, expect: %d\n", max, test_info[i].max_length);
        }
        if(memcmp(longest, test_info[i].expect_line, strlen(longest) + 1) != 0)
        {
            result = 1;
            printf("        longest: %s\n        expect : %s\n", longest, test_info[i].input_lines);
        }

        if(result == 0)
        {
            printf("        result: success!\n");
        }
    }

    return 0;
}
int main(int argc, char **argv)
{

    assert(argc == 2);
    assert(argv[1] != NULL);

    printf(" %d parameters: \n", argc);
    for(int i = 0; i < argc; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i] );
    }
    
    assert(argc == 2);

    if(strcmp(argv[1], "g") == 0)
    {
        generate_input_files();
    }
    else if(strcmp(argv[1], "t") == 0)
    {
        test_input_files();
    }
    else
    {
        perror("parameters error!\n");
        return -1;
    }
    
    return 0;
}

/*
this line's length is 107:
123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345*/
