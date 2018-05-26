
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "s_text.h"
#include "exercise.1.11.h"

#define CHECK(condition) \
    do\
    {\
        if(!(condition))\
        {\
            printf(#condition" failed!\n");\
        }\
        else\
        {\
            printf(#condition" success!\n");\
        }\
    }while(0)

int exercise_1_11_generate_input_files(void)
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

void print_prompt_info(void)
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
                CHECK(count_words("./test_files/test0.txt")==0);
                CHECK(count_words("./test_files/test1.txt")==1);
                CHECK(count_words("./test_files/test2.txt")==0);
                CHECK(count_words("./test_files/test3.txt")==0);
                CHECK(count_words("./test_files/test4.txt")==2);
                CHECK(count_words("./test_files/test5.txt")==66000);
                CHECK(count_words("./test_files/test6.txt")==66000);
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


